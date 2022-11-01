package appl;

import core.Message;
import core.MessageImpl;
import core.Server;
import core.client.Client;

import java.util.*;

public class PubSubClient {

    private Server observer;
    private ThreadWrapper clientThread;

    private String clientAddress;
    private int clientPort;

    private ArrayList<String> brokers; // address:port of all brokers

    public PubSubClient() {
        //this constructor must be called only when the method
        //startConsole is used
        //otherwise the other constructor must be called
    }

    public PubSubClient(String clientAddress, int clientPort) {
        this.clientAddress = clientAddress;
        this.clientPort = clientPort;
        this.brokers = new ArrayList<String>(); // lista de brokers
        this.observer = new Server(clientPort);
        this.clientThread = new ThreadWrapper(observer);
        this.clientThread.start();
    }

    /**
     * For a given broker, send a message of type syncConnection in order to get a list
     * containing each backup address:port.
     *
     * @param address - The broker address.
     * @param port    - The broker port.
     */
    public void syncConnection(String address, int port) {

        // Connection ACK message
        Message msg = new MessageImpl();
        msg.setBrokerId(port);
        msg.setType("syncConnection");
        msg.setContent("Connection stablished by: " + this.clientAddress + ":" + this.clientPort);

        // Create a new Client with the cluster in order to get the current backup list
        try {
            Client clusterConn = new Client(address, port);
            Message response = clusterConn.sendReceive(msg);

            if (response == null) {
                throw (new Exception("Unable to receive a response from " + address + ":" + port));

            } else {

                this.brokers = parseResponseList(response.getContent());
            }

        } catch (Exception e) {
            System.out.println(e);
        }

    }

    /**
     * Parse the broker's response list.
     *
     * @param 'list' - A string in the format "Address1:Port1-Address2:Port2"
     * @return The list of string with each backup broker address. Format: "Address:Port"
     */
    public ArrayList<String> parseResponseList(String stringList) {
        return new ArrayList<String>(Arrays.asList(stringList.split("-")));
    }

    /**
     * For a given broker, send a message of type sub in order to subscribe to that broker
     * if the broker is a backup, it will delegate the subscription to the primary broker
     *
     * @param brokerAddress - The broker address.
     * @param brokerPort    - The broker port.
     */
    public void subscribe(String brokerAddress, int brokerPort) {

        Message msgBroker = new MessageImpl();
        msgBroker.setBrokerId(brokerPort);
        msgBroker.setType("sub");
        msgBroker.setContent(clientAddress + ":" + clientPort);
        Client subscriber = null;
        Message response = null;

        subscriber = new Client(brokerAddress, brokerPort);

        try {
            response = subscriber.sendReceive(msgBroker);
            syncConnection(brokerAddress, brokerPort);

        } catch (Exception e) {
            // Print an error to find out which backup is failing
            System.out.println("Error on broker (" + brokerAddress + ":" + brokerPort + ")" + e);
        }

        try {
            // Verifying if the broker passed is a backup, if true, the action will be delegated
            if (response != null && response.getType().equals("backup")) {
                brokerAddress = response.getContent().split(":")[0];
                brokerPort = Integer.parseInt(response.getContent().split(":")[1]);

                subscriber = new Client(brokerAddress, brokerPort);
                subscriber.sendReceive(msgBroker);

                syncConnection(brokerAddress, brokerPort);
            }

        } catch (Exception e) {

            // Warns a backup in the list to start the election
            if (this.brokers != null) {
                Random random = new Random();
                int index;
                String starter;

                // Ponto de melhora -> Aplicar controle de concorrência na eleição
                int randomInterval = random.nextInt((this.brokers.size() - 1) * 1000);
                try {
                    Thread.sleep(randomInterval);
                } catch (Exception ignored) {
                }
                ///////////////////////////////////////////////////////////////////

                Message msgElection = new MessageImpl();
                Message responseElection = new MessageImpl();

                do {
                    random = new Random();
                    index = random.nextInt(this.brokers.size());
                    starter = this.brokers.get(index);
                    brokerAddress = starter.split(":")[0];
                    brokerPort = Integer.parseInt(starter.split(":")[1]);

                    msgElection.setBrokerId(brokerPort);
                    msgElection.setType("syncPolling");

                    subscriber = new Client(brokerAddress, brokerPort);
                    responseElection = subscriber.sendReceive(msgElection);
                } while (responseElection == null);

                String primaryAddress = "";
                int primaryPort = 0;
                if (responseElection.getType().equals("primarySynced")) {
                    int count = 0;

                    primaryAddress = responseElection.getContent().split(":")[0];
                    primaryPort = Integer.parseInt(responseElection.getContent().split(":")[1]);

                    try {
                        msgElection.setType("electNewPrimary");
                        msgElection.setContent(responseElection.getContent());
                        subscriber = new Client(primaryAddress, primaryPort);
                        responseElection = subscriber.sendReceive(msgElection);

                        if (responseElection != null) {
                            // Avisa toda a lista menos o novo primário
                            for (count = 0; count < this.brokers.size(); count++) {

                                if (this.brokers.get(count).split(":")[0] != primaryAddress && (Integer.parseInt(this.brokers.get(count).split(":")[1])) != primaryPort) {
                                    try {
                                        msgElection.setType("electNewPrimary");
                                        msgElection.setContent(responseElection.getContent());
                                        subscriber = new Client(this.brokers.get(count).split(":")[0], (Integer.parseInt(this.brokers.get(count).split(":")[1])));
                                        responseElection = subscriber.sendReceive(msgElection);
                                    } catch (Exception error) {
                                        continue;
                                    }
                                }

                            }

                            subscriber = new Client(primaryAddress, primaryPort);
                            msgBroker.setBrokerId(primaryPort);
                            subscriber.sendReceive(msgBroker);

                            // Espera um pouco e chama subscribe dnv
                            System.out.println("======================================================");
                            System.out.println("Elected a new primary (SUB)");
                            System.out.println("Primary: " + primaryAddress + ":" + primaryPort);
                            System.out.println("======================================================");

                        }

                    } catch (Exception err) {
                        System.out.println("Exception error -> call SUB again");
                        subscribe(brokerAddress, brokerPort);
                    }
                }

            }
        }
    }

    /**
     * For a given broker, send a message of type unsub in order to unsubscribe to that broker
     * if the broker is a backup, it will delegate the unsubscription to the primary broker
     *
     * @param brokerAddress - The broker address.
     * @param brokerPort    - The broker port.
     */
    public void unsubscribe(String brokerAddress, int brokerPort) {

        Message msgBroker = new MessageImpl();
        msgBroker.setBrokerId(brokerPort);
        msgBroker.setType("unsub");
        msgBroker.setContent(clientAddress + ":" + clientPort);
        Client subscriber = new Client(brokerAddress, brokerPort);
        Message response = subscriber.sendReceive(msgBroker);

        // Verifying if the broker passed is a backup, if true, the action will be delegated
        if (response != null && response.getType().equals("backup")) {
            brokerAddress = response.getContent().split(":")[0];
            brokerPort = Integer.parseInt(response.getContent().split(":")[1]);
            subscriber = new Client(brokerAddress, brokerPort);
            subscriber.sendReceive(msgBroker);
        }

    }

    /**
     * For a given broker, send a message of type pub in order to publish into that broker
     * if the broker is a backup, it will delegate the publish to the primary broker
     *
     * @param message       - The message to be published
     * @param brokerAddress - The broker address.
     * @param brokerPort    - The broker port.
     */
    public void publish(String message, String brokerAddress, int brokerPort) {
        Message msgPub = new MessageImpl();
        msgPub.setBrokerId(brokerPort);
        msgPub.setType("pub");
        msgPub.setContent(message);
        Client publisher = null;
        Message response = null;

        publisher = new Client(brokerAddress, brokerPort);

        try {
            response = publisher.sendReceive(msgPub);
            syncConnection(brokerAddress, brokerPort);

        } catch (Exception e) {
            // Print an error to find out which backup is failing
            System.out.println("Error on broker (" + brokerAddress + ":" + brokerPort + ")" + e);
        }

        // Verifying if the broker passed is a backup, if true, the action will be delegated
        try {
            if (response.getType().equals("backup")) {
                brokerAddress = response.getContent().split(":")[0];
                brokerPort = Integer.parseInt(response.getContent().split(":")[1]);

                publisher = new Client(brokerAddress, brokerPort);
                publisher.sendReceive(msgPub);

                syncConnection(brokerAddress, brokerPort);
            }

        } catch (Exception e) {
            // Warns a backup in the list to start the election
            if (this.brokers != null) {
                Random random = new Random();
                String starter;
                int index;

                // TODO: Aplicar controle de concorrência na eleição
                int randomInterval = random.nextInt((this.brokers.size() - 1) * 1000);
                try {
                    Thread.sleep(randomInterval);
                } catch (Exception ignored) {
                    System.out.println("Error");
                }

                Message msgElection = new MessageImpl();
                Message responseElection = new MessageImpl();

                do {
                    random = new Random();
                    index = random.nextInt(this.brokers.size());

                    starter = this.brokers.get(index);
                    brokerAddress = starter.split(":")[0];
                    brokerPort = Integer.parseInt(starter.split(":")[1]);

                    msgElection.setBrokerId(brokerPort);
                    msgElection.setType("syncPolling");

                    publisher = new Client(brokerAddress, brokerPort);
                    responseElection = publisher.sendReceive(msgElection);

                } while (responseElection == null);

                String primaryAddress = "";
                int primaryPort = 0;

                if (responseElection.getType().equals("primarySynced")) {
                    int count = 0;

                    primaryAddress = responseElection.getContent().split(":")[0];
                    primaryPort = Integer.parseInt(responseElection.getContent().split(":")[1]);

                    try {
                        msgElection.setType("electNewPrimary");
                        msgElection.setContent(responseElection.getContent());
                        publisher = new Client(primaryAddress, primaryPort);
                        responseElection = publisher.sendReceive(msgElection);

                        if (responseElection != null) {

                            // Avisa toda a lista menos o novo primário
                            for (count = 0; count < this.brokers.size(); count++) {

                                if (this.brokers.get(count).split(":")[0] != primaryAddress && (Integer.parseInt(this.brokers.get(count).split(":")[1])) != primaryPort) {
                                    try {
                                        msgElection.setType("electNewPrimary");
                                        msgElection.setContent(responseElection.getContent());
                                        publisher = new Client(this.brokers.get(count).split(":")[0], (Integer.parseInt(this.brokers.get(count).split(":")[1])));
                                        responseElection = publisher.sendReceive(msgElection);
                                    } catch (Exception error) {
                                        continue;
                                    }
                                }

                            }

                            publisher = new Client(primaryAddress, primaryPort);
                            msgPub.setBrokerId(primaryPort);
                            publisher.sendReceive(msgPub);

                            // Espera um pouco e chama subscribe dnv
                            System.out.println("======================================================");
                            System.out.println("Elected a new primary (PUB)");
                            System.out.println("Primary: " + primaryAddress + ":" + primaryPort);
                            System.out.println("======================================================");

                        }

                    } catch (Exception err) {
                        System.out.println("Exception err -> call PUB again");

                        publish(message, brokerAddress, brokerPort);
                    }
                }
            }
        }
    }

    public List<Message> getLogMessages() {
        return observer.getLogMessages();
    }

    public void stopPubSubClient() {
        System.out.println("Client stopped...");
        observer.stop();
        clientThread.interrupt();
    }

    public void startConsole() {
        Scanner reader = new Scanner(System.in);  // Reading from System.in

        System.out.print("Enter the client port (ex.8080): ");
        int clientPort = reader.nextInt();
        System.out.println("Now you need to inform the broker credentials...");
        System.out.print("Enter the broker address (ex. localhost): ");
        String brokerAddress = reader.next();
        System.out.print("Enter the broker port (ex.8080): ");
        int brokerPort = reader.nextInt();

        observer = new Server(clientPort);
        clientThread = new ThreadWrapper(observer);
        clientThread.start();

        subscribe(brokerAddress, brokerPort);

        System.out.println("Do you want to subscribe for more brokers? (Y|N)");
        String resp = reader.next();

        if (resp.equals("Y") || resp.equals("y")) {
            String message = "";

            while (!message.equals("exit")) {
                System.out.println("You must inform the broker credentials...");
                System.out.print("Enter the broker address (ex. localhost): ");
                brokerAddress = reader.next();
                System.out.print("Enter the broker port (ex.8080): ");
                brokerPort = reader.nextInt();
                subscribe(brokerAddress, brokerPort);
                System.out.println(" Write exit to finish...");
                message = reader.next();
            }
        }

        System.out.println("Do you want to publish messages? (Y|N)");
        resp = reader.next();
        if (resp.equals("Y") || resp.equals("y")) {
            String message = "";

            while (!message.equals("exit")) {
                System.out.println("Enter a message (exit to finish submissions): ");
                message = reader.next();

                System.out.println("You must inform the broker credentials...");
                System.out.print("Enter the broker address (ex. localhost): ");
                brokerAddress = reader.next();
                System.out.print("Enter the broker port (ex.8080): ");
                brokerPort = reader.nextInt();

                publish(message, brokerAddress, brokerPort);

                List<Message> log = observer.getLogMessages();

                Iterator<Message> it = log.iterator();
                System.out.print("Log itens: ");
                while (it.hasNext()) {
                    Message aux = it.next();
                    System.out.print(aux.getContent() + aux.getLogId() + " | ");
                }
                System.out.println();

            }
        }

        System.out.print("Shutdown the client (Y|N)?: ");
        resp = reader.next();
        if (resp.equals("Y") || resp.equals("y")) {
            System.out.println("Client stopped...");
            observer.stop();
            clientThread.interrupt();
        }

        //once finished
        reader.close();
    }

    class ThreadWrapper extends Thread {
        Server s;

        public ThreadWrapper(Server s) {
            this.s = s;
        }

        public void run() {
            s.begin();
        }
    }

}
