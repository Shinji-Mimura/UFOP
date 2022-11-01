package sync;

import core.Message;
import core.MessageImpl;
import core.PubSubCommand;

import java.util.ArrayList;
import java.util.Set;
import java.util.SortedSet;

public class SyncPubCommand implements PubSubCommand {

    @Override
    public Message execute(Message m, SortedSet<Message> log, Set<String> subscribers, boolean isPrimary, ArrayList<String> backupAddrs, String primaryServerAddress, int primaryServerPort, int currentPort) {

        Message response = new MessageImpl();

        response.setLogId(m.getLogId());


        log.add(m);

        response.setContent("Message published on backup: " + m.getContent());
        response.setType("pubsync_ack");

        return response;
    }

    // @Override
    // public Message execute(Message m, SortedSet<Message> log, Set<String> subscribers, boolean isPrimary,
    //                          ArrayList<String> backupAddrs) {

    //     Message response = new MessageImpl();

    //     response.setLogId(m.getLogId());


    //     log.add(m);

    //     response.setContent("Message published on backup: " + m.getContent());
    //     response.setType("pubsync_ack");

    //     return response;
    // }

}
