package core;

import java.util.ArrayList;
import java.util.Set;
import java.util.SortedSet;

public interface PubSubCommand {

    Message execute(Message m, SortedSet<Message> log, Set<String> subscribers, boolean isPrimary, ArrayList<String> brokers, String primaryServerAddress, int primaryServerPort, int currentPort);

}
