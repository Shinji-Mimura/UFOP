package appl;

import core.Server;

import java.util.ArrayList;
import java.util.Scanner;

public class Broker {

    public Broker() {

        Scanner reader = new Scanner(System.in);
        String primaryAddress = "localhost";
        int primaryPort = 8080;
        boolean respBool = false;
        Server s = null;
        ArrayList<String> brokers = new ArrayList<String>();

        System.out.print("Is the broker primary (Y/N)? ");
        String respYN = reader.next();

        System.out.print("Enter the Broker port number: ");
        int port = reader.nextInt();

        if (respYN.equalsIgnoreCase("Y")) {
            respBool = true;
            primaryPort = port;
            brokers.add(primaryAddress + ":" + primaryPort);

            System.out.print("How many backups do you want to add? ");
            int nBrokers = reader.nextInt();

            for (int i = 0; i < nBrokers; i++) {
                System.out.print("Enter the backup in the format 'address:port': ");
                brokers.add(reader.next());
            }

            s = new Server(port, respBool, brokers, primaryAddress, primaryPort);

        } else {
            
            primaryAddress = "localhost";

            System.out.print("Enter the Primary Broker port: ");
            primaryPort = reader.nextInt();

            s = new Server(port, respBool, primaryAddress, primaryPort);
        }

        ThreadWrapper brokerThread = new ThreadWrapper(s);
        brokerThread.start(); // Chama ThreadWrapper.run();

        System.out.print("Shutdown the broker (Y|N)?: ");
        String resp = reader.next();

        if (resp.equals("Y") || resp.equals("y")) {
            System.out.println("Broker stopped...");
            s.stop();
            brokerThread.interrupt();
        }

        //once finished
        reader.close();
    }

    public static void main(String[] args) {
        new Broker();
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
