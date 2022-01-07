#ifndef FLOW_H
#define FLOW_H

#include "System.h"

using namespace std;

class Flow {
public:
    
    /**
     * @brief The equation used in the flows execution
     * @return void
     */

    virtual double equation() = 0;

    /**
     * @brief Get name of current flow
     * @return string - name of current flow
     */

    virtual string getName() = 0;

    /**
     * @brief Set name of current flow
     * @param name name of current flow
     */

    virtual void setName(string name) = 0;

    /**
     * @brief Get input system in flow
     * @return System* - input system in flow
     */

    virtual System *getInput() = 0;

    /**
     * @brief Set input system in flow
     * @param input System input
     */

    virtual void setInput(System *input) = 0;

    /**
     * @brief Get output system in flow
     * @return System* - output system in flow
     */

    virtual System *getOutput() = 0;

    /**
     * @brief Set output system in flow
     * @param output - System output
     */

    virtual void setOutput(System *output) = 0;

    /**
     * @brief Set to null flow input
     * @return void
     */

    virtual void removeInput() = 0;

    /**
     * @brief Set to null flow output
     * @return void
     */

    virtual void removeOutput() = 0;
};

#endif


