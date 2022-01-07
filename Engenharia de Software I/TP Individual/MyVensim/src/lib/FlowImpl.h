#ifndef FLOWIMPL_H
#define FLOWIMPL_H

#include "Flow.h"
#include "handleBodySemDebug.h"

class FlowBody : public Body {
protected:
    string name;
    System *input;
    System *output;

public:

    ~FlowBody() {}

    string getName() const;

    void setName(string name);

    System *getInput() const;

    void setInput(System *input);

    System *getOutput() const;

    void setOutput(System *output);

    void removeInput();

    void removeOutput();
};

class FlowHandle : public Flow, public Handle<FlowBody> {

public:
    FlowHandle(string name, System* input, System* output) {
        pImpl_->setName(name);
        pImpl_->setInput(input);
        pImpl_->setOutput(output);
    }

    ~FlowHandle() {}

    virtual double equation() = 0;

    string getName() { return pImpl_->getName(); }

    void setName(string name) { pImpl_->setName(name); }

    System *getInput() { return pImpl_->getInput(); }

    void setInput(System *input) { pImpl_->setInput(input); }

    System *getOutput() {return pImpl_->getOutput(); }

    void setOutput(System *output) { pImpl_->setOutput(output); }

    void removeInput() { pImpl_->removeInput(); }

    void removeOutput() { pImpl_->removeOutput(); }

};

#endif
