#ifndef SYSTEM_H
#define SYSTEM_H

#include <string>
#include <iostream>

using namespace std;

class System {
public:
    /**
     * @brief Default destructor of system
     * @return void
     * */
    virtual ~System() {}

    /**
     * @brief Set name of system
     * @param name name of system
     **/

    virtual void setName(string name) = 0;

    /**
     * @brief Get name of current system
     * @return string - name of current system
     */

    virtual string getName() = 0;

    /**
     * @brief Set content to current system
     * @param content content of system
     */

    virtual void setContent(double content) = 0;

    /**
     * @brief Get content of current system
     * @return double - content of the system
     */

    virtual double getContent() = 0;
};

#endif
