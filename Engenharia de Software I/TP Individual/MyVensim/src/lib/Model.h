#ifndef MODEL_H
#define MODEL_H

#include <vector>
#include "Flow.h"


using namespace std;

class Model {
public:
    typedef vector<System *>::iterator sysIterator;
    typedef vector<Flow *>::iterator flowIterator;

    friend class Flow;
    friend class System;

    /**
 * @brief Return the begin of system vector iterator
 * @return iterator of system vector
 */

    virtual sysIterator beginSystem() = 0;

    /**
     * @brief Return the end of system vector iterator
     * @return iterator of system vector
     */

    virtual sysIterator endSystem() = 0;

    /**
     * @brief Return the begin of flow vector iterator
     * @return iterator of flow vector
     */

    virtual flowIterator beginFlow() = 0;

    /**
     * @brief Return the end of flow vector iterator
     * @return iterator of flow vector
     */

    virtual flowIterator endFlow() = 0;

    virtual ~Model() {}

    /**
     * @brief Execute all flow's equation in model
     * @param begin start time
     * @param end final time
     * @param increment increment step
     */

    virtual void execute(double begin, double end, double increment) = 0;

    /**
     * @brief Set name to current model
     * @param name name to current model
     */

    virtual void setName(string name) = 0;

    /**
     * @brief Get name of current model
     * @return string - name of current model
     */

    virtual string getName() = 0;

    /**
     * @brief Add system in system's vector inside model
     * @param system
     */

    virtual void addSystem(System *system) = 0;

    /**
     * @brief Add flow in flow's vector inside model
     * @param flow
     */

    virtual void addFlow(Flow *flow) = 0;

    /**
     * @brief Remove specific system inside system's vector using his name
     * @param system
     */

    virtual void removeSystem(System *system) = 0;

    /**
     * @brief Remove specific flow inside flow's vector using his name
     * @param flow
     */

    virtual void removeFlow(Flow *flow) = 0;

    /**
     * @brief Get a specific system via vector position
     * @param index - position in vector
     * @return System*
     */

    virtual System *getSystem(int index) = 0;

    /**
     * @brief Get a specific flow via vector position
     * @param index - position in vector
     * @return Flow*
     */

    virtual Flow *getFlow(int index) = 0;

    // ----- Creators ----- //

    /**
     * @brief Create flow via model
     * @tparam f
     * @param name
     * @param input
     * @param output
     * @return Flow*
     */

    template<typename f>
    Flow *createFlow(string name, System *input, System *output) {
        Flow *flow = new f(name, input, output);
        addFlow(flow);
        return flow;
    }

    /**
     * @brief Create system via model
     * @param name
     * @param content
     * @return System*
     */

    virtual System *createSystem(string name = "", double content = 0.0) = 0;

    /**
     * @brief Create model via model
     * @param name
     * @return Model*
     */

    static Model *createModel(string name = "");

};


#endif
