package sync;

import core.Message;
import core.MessageImpl;
import core.PubSubCommand;

import java.util.ArrayList;
import java.util.Set;
import java.util.SortedSet;

public class SyncUnsubCommand implements PubSubCommand {

    @Override
    public Message execute(Message m, SortedSet<Message> log, Set<String> subscribers, boolean isPrimary, ArrayList<String> backupAddrs, String primaryServerAddress, int primaryServerPort, int currentPort) {

        Message response = new MessageImpl();

        if (!subscribers.contains(m.getContent()))
            response.setContent("subscriber does not exist: " + m.getContent());
        else {

            response.setLogId(m.getLogId());

            subscribers.remove(m.getContent());

            response.setContent("Subscriber removed from backup: " + m.getContent());

        }

        response.setType("unsubsync_ack");

        return response;

    }

    // @Override
    // public Message execute(Message m, SortedSet<Message> log, Set<String> subscribers, boolean isPrimary,
    // (Message m, SortedSet<Message> log, Set<String> subscribers, boolean isPrimary,
    // //                         ArrayList<String> backupAddrs) {) {

    //     Message response = new MessageImpl();

    //     if (!subscribers.contains(m.getContent()))
    //         response.setContent("subscriber does not exist: " + m.getContent());
    //     else {

    //         response.setLogId(m.getLogId());

    //         subscribers.remove(m.getContent());

    //         response.setContent("Subscriber removed from backup: " + m.getContent());

    //     }

    //     response.setType("unsubsync_ack");

    //     return response;

    // }
}
