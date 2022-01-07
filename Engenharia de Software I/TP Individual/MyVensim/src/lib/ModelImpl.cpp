#include "ModelImpl.h"
#include "SystemImpl.h"

ModelHandle::sysIterator ModelBody::beginSystem(void) { return systems.begin(); }

ModelHandle::sysIterator ModelBody::endSystem(void) { return systems.end(); }

ModelHandle::flowIterator ModelBody::beginFlow(void) { return flows.begin(); }

ModelHandle::flowIterator ModelBody::endFlow(void) { return flows.end(); }

void ModelBody::execute(double begin, double end, double increment) {
    vector<double> results;
    int count;

    for (double i = begin; i < end; i += increment) {

        for (auto flow: flows) {
            results.push_back(flow->equation());
        }

        count = 0;

        for (auto flow: flows) {
            System *sysInput = flow->getInput();
            System *sysOutput = flow->getOutput();

            if (sysInput != NULL) { sysInput->setContent(sysInput->getContent() - results[count]); }

            if (sysOutput != NULL) { sysOutput->setContent(sysOutput->getContent() + results[count]); }

            count++;
        }

        for (auto f = beginFlow(); f != endFlow(); ++f) { results.pop_back(); }
    }
}

void ModelBody::setName(string name) {
    this->name = name;
}

string ModelBody::getName()  {
    return name;
}

void ModelBody::addSystem(System *system) {
    systems.push_back(system);
}

void ModelBody::addFlow(Flow *flow) {
    flows.push_back(flow);
}

void ModelBody::removeSystem(System *system) {
    auto index = beginSystem();

    for (System *sys: systems) {
        if (system == sys) {
            systems.erase(index);
            break;
        }

        ++index;
    }
}

void ModelBody::removeFlow(Flow *flow) {
    auto index = beginFlow();

    for (Flow *f: flows) {
        if (f == flow) {
            flows.erase(index);
            break;
        }

        ++index;
    }
}

System *ModelBody::getSystem(int index) {
    return systems[index];
}

Flow *ModelBody::getFlow(int index) {
    return flows[index];
}

Model* Model::createModel(string name) {
    return ModelHandle::createModel(name);
}

ModelBody *ModelBody::createModel(string name) {
    return ModelBody::createModel(name);
}

System *ModelBody::createSystem(string name, double content) {
    System *system = new SystemHandle(name, content);
    addSystem(system);
    return system;
}







