package sub;

import core.Message;
import core.MessageImpl;
import core.PubSubCommand;
import core.client.Client;

import java.util.ArrayList;
import java.util.Set;
import java.util.SortedSet;

public class UnsubCommand implements PubSubCommand {

    @Override
    public Message execute(Message m, SortedSet<Message> log, Set<String> subscribers, boolean isPrimary, ArrayList<String> backupAddrs, String primaryServerAddress, int primaryServerPort, int currentPort) {

        Message response = new MessageImpl();


        if (!subscribers.contains(m.getContent()))
            response.setContent("subscriber does not exist: " + m.getContent());
        else {
            int logId = m.getLogId();
            logId++;

            response.setLogId(logId);
            m.setLogId(logId);

            try {
                //sincronizar com o broker backup
                Message syncUnsubMsg = new MessageImpl();
                syncUnsubMsg.setBrokerId(m.getBrokerId());
                syncUnsubMsg.setContent(m.getContent());
                syncUnsubMsg.setLogId(m.getLogId());
                syncUnsubMsg.setType("syncUnsub");

                String sencondaryServerAddress;
                int secondaryServerPort;

                for (int i = 0; i < backupAddrs.size(); i++) {
                    sencondaryServerAddress = backupAddrs.get(i).split(":")[0];
                    secondaryServerPort = Integer.parseInt(backupAddrs.get(i).split(":")[1]);

                    if (sencondaryServerAddress != primaryServerAddress && secondaryServerPort != primaryServerPort && secondaryServerPort != currentPort) {
                        Client clientBackup = new Client(sencondaryServerAddress, secondaryServerPort);
                        syncUnsubMsg = clientBackup.sendReceive(syncUnsubMsg);
                        System.out.println(syncUnsubMsg.getContent());
                    }
                }

            } catch (Exception e) {
                System.out.println("Cannot sync with backup - unsubscribe service");
            }

            subscribers.remove(m.getContent());

            response.setContent("Subscriber removed: " + m.getContent());

        }

        response.setType("unsub_ack");

        return response;

    }

}
