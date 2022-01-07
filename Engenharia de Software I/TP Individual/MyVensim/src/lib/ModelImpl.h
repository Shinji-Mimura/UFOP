#ifndef MODELIMPL_H
#define MODELIMPL_H

#include "Model.h"
#include "handleBodySemDebug.h"

class ModelBody : public Body {
protected:
    string name;
    vector<System *> systems;
    vector<Flow *> flows;

public:
    typedef vector<System *>::iterator sysIterator;
    typedef vector<Flow *>::iterator flowIterator;

    sysIterator beginSystem();

    sysIterator endSystem();

    flowIterator beginFlow();

    flowIterator endFlow();

    static ModelBody* createModel(string name = "");

    void execute(double begin = 0.0, double end = 0.0, double increment = 1.0);

    void setName(string name);

    string getName();

    void addSystem(System *system);

    void addFlow(Flow *flow);

    void removeSystem(System *system);

    void removeFlow(Flow *flow);

    System *getSystem(int index);

    Flow *getFlow(int index);

    Flow *createFlow(string name, System *input, System *output);

    System *createSystem(string name = "", double content = 0.0);

private:
/*
 * ModelImpl(const ModelImpl &model);
 * void operator=(const ModelImpl &model);
*/
};

class ModelHandle : public Model, public Handle<ModelBody> {
public:

    sysIterator beginSystem() {return pImpl_->beginSystem();}

    sysIterator endSystem() {return pImpl_->endSystem();}

    flowIterator beginFlow() {return pImpl_->beginFlow();}

    flowIterator endFlow() {return pImpl_->endFlow();}

    ModelHandle(string name) {
        pImpl_->setName(name);
    }

    void setName(string name) { pImpl_->setName(name); }

    void execute(double begin, double end, double increment) { return pImpl_->execute(begin, end, increment); }

    string getName() { return pImpl_->getName(); }

    void addSystem(System *system) { pImpl_->addSystem(system); }

    void addFlow(Flow *flow) { pImpl_->addFlow(flow); }

    void removeSystem(System *system) { pImpl_->removeSystem(system); }

    void removeFlow(Flow *flow) { pImpl_->removeFlow(flow); }

    System *getSystem(int index) { return pImpl_->getSystem(index); }

    Flow *getFlow(int index) {return pImpl_->getFlow(index); }

    Flow *createFlow(string name, System *input, System *output) {
        return pImpl_->createFlow(name, input, output);
    }

    System *createSystem(string name = "", double content = 0.0) {
        return pImpl_->createSystem(name, content);
    }

    static ModelHandle *createModel(string name = "") {
        ModelHandle* mh = new ModelHandle(name);
        return mh;
    }
};

#endif
