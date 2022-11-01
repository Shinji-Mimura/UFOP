package core.client;

import core.Message;

import java.io.*;
import java.net.Socket;

public class Client {

    private Socket s;

    public Client(String ip, int port) {
        try {
            s = new Socket(ip, port);
        } catch (Exception e) {
            System.out.println("Client cannot connect with " + ip + " on port: " + port);
        }
    }

    public Message sendReceive(Message msg) {

        try {
            ObjectOutputStream out = new ObjectOutputStream(new BufferedOutputStream(s.getOutputStream()));
            out.writeObject(msg);
            out.flush();

            InputStream stream = s.getInputStream();
            BufferedInputStream buffer = new BufferedInputStream(stream);
            ObjectInputStream in = new ObjectInputStream(buffer);
            Message response = (Message) in.readObject();

            in.close();
            out.close();
            s.close();

            return response;
        } catch (Exception e) {
            return null;
        }
    }

}
