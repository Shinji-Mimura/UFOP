#include "Unit_Flow.h"
#include <cmath>

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

void unit_flow_constructor() {
    cout << "[!] Test 1 - Constructor Without Params" << endl;

    ExponentialFlow *flow = new ExponentialFlow;

    assert(flow->getName() == "");
    assert(flow->getInput() == NULL);
    assert(flow->getOutput() == NULL);

    cout << "[+] Test 1 - OK" << endl;

    cout << "[!] Test 2 - Constructor With Params" << endl;

    System *s1 = new SystemImpl();
    System *s2 = new SystemImpl();

    ExponentialFlow *flow2 = new ExponentialFlow("Flow Two", s1, s2);

    assert(flow2->getName() == "Flow Two");
    assert(flow2->getInput() == s1);
    assert(flow2->getOutput() == s2);

    cout << "[+] Test 2 - OK" << endl;
}

void UnitFlow::unit_flow_copy_constructor() {
    cout << "[!] Test 3 - Copy Constructor" << endl;

    System *sys1 = new SystemImpl("input", 1.0);
    System *sys2 = new SystemImpl("output", 2.0);

    ExponentialFlow *flow = new ExponentialFlow("Flow Copy");
    Flow *flow2 = new ExponentialFlow(*flow);

    flow->setName("Original Flow");
    flow->setInput(sys1);
    flow->setOutput(sys2);

    assert(flow2->getName() == "Flow Copy");
    assert(flow2->getInput() == NULL);
    assert(flow2->getOutput() == NULL);

    cout << "[+] Test 3 - OK" << endl;
}

void unit_flow_destructor() {
    cout << "[!] Test 4 - Flow Destructor" << endl;

    ExponentialFlow *flow = new ExponentialFlow("Flow");
    delete flow;

    cout << "[+] Test 4 - OK" << endl;
}

void unit_flow_getName() {
    cout << "[!] Test 5 - Flow GetName" << endl;

    ExponentialFlow *flow = new ExponentialFlow("Flow");

    assert(flow->getName() == "Flow");

    cout << "[+] Test 5 - OK" << endl;
}

void unit_flow_setName() {
    cout << "[!] Test 6 - Flow SetName" << endl;

    ExponentialFlow *flow = new ExponentialFlow("Flow");
    flow->setName("Flow Two");

    assert(flow->getName() == "Flow Two");

    cout << "[+] Test 6 - OK" << endl;
}

void unit_flow_getInput() {
    cout << "[!] Test 7 - Flow GetInput" << endl;

    System *sys = new SystemImpl();
    ExponentialFlow *flow = new ExponentialFlow("Flow", sys);

    assert(flow->getInput() == sys);

    cout << "[+] Test 7 - OK" << endl;
}

void unit_flow_setInput() {
    cout << "[!] Test 8 - Flow SetInput" << endl;

    System *sys = new SystemImpl();
    ExponentialFlow *flow = new ExponentialFlow("Flow");
    flow->setInput(sys);

    assert(flow->getInput() == sys);

    cout << "[+] Test 8 - OK" << endl;
}

void unit_flow_getOutput() {
    cout << "[!] Test 9 - Flow GetOutput" << endl;

    System *sys = new SystemImpl();
    ExponentialFlow *flow = new ExponentialFlow("Flow", NULL, sys);

    assert(flow->getOutput() == sys);

    cout << "[+] Test 9 - OK" << endl;
}

void unit_flow_setOutput() {
    cout << "[!] Test 10 - Flow SetOutput" << endl;

    System *sys = new SystemImpl();
    ExponentialFlow *flow = new ExponentialFlow("Flow");
    flow->setOutput(sys);

    assert(flow->getOutput() == sys);

    cout << "[+] Test 10 - OK" << endl;
}

void unit_flow_removeInput() {
    cout << "[!] Test 11 - Flow RemoveInput" << endl;

    System *sys = new SystemImpl();
    ExponentialFlow *flow = new ExponentialFlow("Flow");
    flow->setInput(sys);
    flow->removeInput();

    assert(flow->getInput() == NULL);

    cout << "[+] Test 11 - OK" << endl;
}

void unit_flow_removeOutput() {
    cout << "[!] Test 12 - Flow RemoveOutput" << endl;

    System *sys = new SystemImpl();
    ExponentialFlow *flow = new ExponentialFlow("Flow");
    flow->setOutput(sys);
    flow->removeOutput();

    assert(flow->getOutput() == NULL);

    cout << "[+] Test 12 - OK" << endl;
}

void UnitFlow::unit_flow_assignmentOperator() {
    cout << "[!] Test 13 - Flow Assignment Operator" << endl;

    System *sys1 = new SystemImpl("input", 1.0);
    System *sys2 = new SystemImpl("output", 2.0);

    ExponentialFlow *flow = new ExponentialFlow("Flow Copy");
    ExponentialFlow *flow2 = new ExponentialFlow();
    *flow2 = *flow;

    flow->setName("Original Flow");
    flow->setInput(sys1);
    flow->setOutput(sys2);

    assert(flow2->getName() == "Flow Copy");
    assert(flow2->getInput() == NULL);
    assert(flow2->getOutput() == NULL);

    cout << "[+] Test 13 - OK" << endl;
}

void unit_flow_equation() {
    cout << "[!] Test 14 - Flow Equation" << endl;

    System *sys1 = new SystemImpl("input", 1.0);
    System *sys2 = new SystemImpl("output", 2.0);

    ExponentialFlow *flow = new ExponentialFlow("Flow", sys1, sys2);

    sys2->setContent(flow->equation());

    assert(fabs(flow->getOutput()->getContent() - 0.01) < 0.1);

    cout << "[+] Test 14 - OK" << endl;
}

void run_unit_tests_flow() {
    UnitFlow *unit_flow = new UnitFlow();

    unit_flow_constructor();
    unit_flow->unit_flow_copy_constructor();
    unit_flow_destructor();
    unit_flow_getName();
    unit_flow_setName();
    unit_flow_getInput();
    unit_flow_setInput();
    unit_flow_getOutput();
    unit_flow_setOutput();
    unit_flow_removeInput();
    unit_flow_removeOutput();
    unit_flow->unit_flow_assignmentOperator();
    unit_flow_equation();

    delete unit_flow;
}


