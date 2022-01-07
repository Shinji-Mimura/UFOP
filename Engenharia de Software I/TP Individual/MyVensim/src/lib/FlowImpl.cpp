#include "FlowImpl.h"

string FlowBody::getName() const {
    return name;
}

void FlowBody::setName(string name) {
    this->name = name;
}

System *FlowBody::getInput() const {
    return input;
}

void FlowBody::setInput(System *input) {
    this->input = input;
}

System *FlowBody::getOutput() const {
    return output;
}

void FlowBody::setOutput(System *output) {
    this->output = output;
}

void FlowBody::removeInput() {
    this->input = NULL;
}

void FlowBody::removeOutput() {
    this->output = NULL;
}








