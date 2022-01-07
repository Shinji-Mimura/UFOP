#include "Unit_Model.h"

using namespace std;

class ExponentialFlow : public FlowImpl {
public:
    ExponentialFlow(string name = "", System *input = NULL, System *output = NULL) : FlowImpl(name, input, output) {}

    double equation() {
        if (getInput() != NULL) {
            return (0.01 * getOutput()->getContent());
        } else {
            return 0;
        }
    }
};

void unit_model_constructor() {
    cout << "[!] Test 1 - Construtor Without Params" << endl;

    Model *model = new ModelImpl();

    assert(model->getName() == "");

    cout << "[+] Test 1 - OK" << endl;

    cout << "[!] Test 2 - Construtor With Params" << endl;

    System *sys1 = new SystemImpl("System 1");
    System *sys2 = new SystemImpl("System 2");

    vector<System *> systems;

    systems.push_back(sys1);
    systems.push_back(sys2);

    ExponentialFlow *flow = new ExponentialFlow("Flow 1");
    Model *model2 = new ModelImpl("Model 2");

    model2->addSystem(sys1);
    model2->addSystem(sys2);
    model2->addFlow(flow);
    
    assert(model2->getName() == "Model 2");
    assert((*(model2->beginFlow()))->getName() == "Flow 1");

    int counter = 0;

    for (auto system = model2->beginSystem(); system != model2->endSystem(); ++system) {
        assert((*system)->getName() == systems[counter]->getName());
        counter++;
    }

    cout << "[+] Test 2 - OK" << endl;
}

void unit_model_destructor() {
    cout << "[!] Test 3 - Model Destructor" << endl;

    System *sys1 = new SystemImpl("System 1");
    System *sys2 = new SystemImpl("System 2");

    ExponentialFlow *flow = new ExponentialFlow("Flow");

    Model *model = new ModelImpl("Model");

    model->addSystem(sys1);
    model->addSystem(sys2);
    model->addFlow(flow);

    delete model;

    cout << "[+] Test 3 - OK" << endl;
}

void unit_model_addSystem() {
    cout << "[!] Test 4 - Add System" << endl;

    System *sys = new SystemImpl("System");

    Model *model = new ModelImpl("Model");
    model->addSystem(sys);

    assert((*(model->beginSystem()))->getName() == sys->getName());

    cout << "[+] Test 4 - OK" << endl;
}

void unit_model_removeSystem() {
    cout << "[!] Test 5 - Remove System" << endl;

    System *sys = new SystemImpl("System");

    Model *model = new ModelImpl("Model");
    model->addSystem(sys);
    model->removeSystem(sys);

    assert(model->beginSystem() == model->endSystem());

    cout << "[+] Test 5 - OK" << endl;
}

void unit_model_addFlow() {
    cout << "[!] Test 6 - Add Flow" << endl;

    ExponentialFlow *flow = new ExponentialFlow("Flow");

    Model *model = new ModelImpl("Model");
    model->addFlow(flow);

    assert((*(model->beginFlow()))->getName() == flow->getName());

    cout << "[+] Test 6 - OK" << endl;
}

void unit_model_removeFlow() {
    cout << "[!] Test 7 - Remove Flow" << endl;

    ExponentialFlow *flow = new ExponentialFlow("Flow");

    Model *model = new ModelImpl("Model");
    model->addFlow(flow);
    model->removeFlow(flow);

    assert(model->beginFlow() == model->endFlow());

    cout << "[+] Test 7 - OK" << endl;
}

void unit_model_getName() {
    cout << "[!] Test 8 - Model GetName" << endl;

    Model *model = new ModelImpl("Model");

    assert(model->getName() == "Model");

    cout << "[+] Test 8 - OK" << endl;
}

void unit_model_setName() {
    cout << "[!] Test 9 - Model SetName" << endl;

    Model *model = new ModelImpl();
    model->setName("Model");

    assert(model->getName() == "Model");

    cout << "[+] Test 9 - OK" << endl;
}

void run_unit_tests_model() {
    unit_model_constructor();
    unit_model_destructor();
    unit_model_addSystem();
    unit_model_removeSystem();
    unit_model_addFlow();
    unit_model_removeFlow();
    unit_model_getName();
    unit_model_setName();
}
