/**
 *
 */
package core;

import java.io.Serializable;


public interface Message extends Serializable {

    String getType();

    void setType(String type);

    int getLogId();

    void setLogId(int id);

    String getContent();

    void setContent(String content);

    int getBrokerId();

    void setBrokerId(int id);

}
