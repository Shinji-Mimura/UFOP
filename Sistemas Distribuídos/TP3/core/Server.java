package core;

import core.client.Client;

import java.io.IOException;
import java.net.ServerSocket;
import java.net.Socket;
import java.util.ArrayList;
import java.util.Arrays;
import java.util.List;


// This server represents the producer in a producer/consumer strategy
// it receives a client socket and inserts it into a resource
public class Server {
    protected GenericConsumer<Socket> consumer;
    protected GenericResource<Socket> resource;
    protected int port;
    protected ServerSocket serverSocket;
    protected boolean isPrimary;

    protected boolean isClient; // When constructor Server(port) is called, gets true as value and false otherwise
    protected ArrayList<String> brokers;
    protected String primaryServer;
    protected int primaryPort;

    public Server(int port) {
        this.port = port;
        this.isPrimary = true;

        this.primaryServer = null;
        this.primaryPort = -1;
        this.isClient = true;

        this.resource = new GenericResource<Socket>();
    }

    public Server(int port, boolean isPrimary, String primaryServer, int primaryPort) {
        this.port = port;
        this.isPrimary = isPrimary;

        this.primaryServer = primaryServer;
        this.primaryPort = primaryPort;
        this.isClient = false;
        this.brokers = null;

        this.resource = new GenericResource<Socket>();
    }

    public Server(int port, boolean isPrimary, ArrayList<String> list, String primaryServer, int primaryPort) {
        this.port = port;
        this.isPrimary = isPrimary;

        this.primaryServer = primaryServer;
        this.primaryPort = primaryPort;
        this.isClient = false;
        this.brokers = list;

        this.resource = new GenericResource<Socket>();
    }

    /**
     * Request a list of backups to addr:port and insert current location to the list
     *
     * @param addr - The broker address. The addr must be of a broker with the current list
     * @param port - The broker port. The port must be of a broker with the current list
     * @return The list of backups in format "addr:port"
     */
    public ArrayList<String> requestList(String addr, int port) {

        String[] responseList = {};

        // Connection ACK message
        Message msg = new MessageImpl();
        msg.setBrokerId(port);
        msg.setType("syncConnection");
        msg.setContent("localhost:" + this.port);

        // Create a new Client with the cluster in order to get the current backup list
        try {
            Client clusterConn = new Client(addr, port);
            Message response = clusterConn.sendReceive(msg);

            if (response == null) {
                throw (new Exception("Unable to receive a response from " + addr + ":" + port));

            } else {
                responseList = response.getContent().split("-");
            }

        } catch (Exception e) {
            System.out.println(e);
        }

        return new ArrayList<String>(Arrays.asList(responseList));

    }

    public void begin() {
        try {

            // Getting updated backup list after connection 
            if (!this.isClient && this.brokers == null && !this.isPrimary)
                this.brokers = requestList(this.primaryServer, this.primaryPort);

            // Just one consumer to guarantee a single
            // log write mechanism
            this.consumer = new PubSubConsumer<Socket>(this.resource, this.isPrimary, this.brokers, this.primaryServer, this.primaryPort);

            this.consumer.start();
            openServerSocket();

            //start listening
            listen();

        } catch (Exception e) {
            e.printStackTrace();
        }
    }

    protected void listen() {
        while (!this.resource.isStopped()) {

            try {
                Socket clientSocket = this.serverSocket.accept();
                this.resource.putRegister(clientSocket);

                this.primaryServer = this.consumer.getPrimaryAddress();
                this.primaryPort = this.consumer.getPrimaryPort();
                this.isPrimary = this.consumer.getIsPrimary();
            } catch (IOException e) {

                if (this.resource.isStopped()) {
                    return;
                }
                throw new RuntimeException("Error accepting connection", e);
            }

        }

        System.out.println("Stopped: " + port);
    }

    private void openServerSocket() {
        try {
            this.serverSocket = new ServerSocket(this.port);
            System.out.println("\nListening on port: " + this.port);

        } catch (IOException e) {
            throw new RuntimeException("Cannot open port " + port, e);
        }
    }

    public void stop() {
        this.resource.stopServer();
        listen();

        this.consumer.stopConsumer();
        this.resource.setFinished();

        try {
            this.serverSocket.close();
        } catch (IOException e) {
            e.printStackTrace();
        }
    }

    public List<Message> getLogMessages() {
        try {
            return ((PubSubConsumer<Socket>) this.consumer).getMessages();
        } catch (Exception e) {
            return null;
        }
    }

}
