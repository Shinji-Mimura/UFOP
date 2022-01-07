#include "Unit_System.h"

using namespace std;

void unit_system_constructor() {
    cout << "[!] Test 1 - Constructor Without Params" << endl;

    System *sys = new SystemImpl();

    assert(sys->getName() == "");
    assert(sys->getContent() == 0.0);

    cout << "[+] Test 1 - OK" << endl;

    cout << "[!] Test 2 - Constructor With Params" << endl;

    System *sys2 = new SystemImpl("System 2", 1.0);

    assert(sys2->getName() == "System 2");
    assert(sys2->getContent() == 1.0);

    cout << "[+] Test 2 - OK" << endl;

}

void UnitSystem::unit_system_copy_constructor() {
    cout << "[!] Test 3 - Copy Constructor" << endl;

    SystemImpl *sys1 = new SystemImpl("Copy System", 1.0);
    System *sys2 = new SystemImpl(*sys1);

    sys1->setName("Original System");
    sys1->setContent(100.0);

    assert(sys2->getName() == "Copy System");
    assert(sys2->getContent() == 1.0);
    assert(sys1 != sys2);

    cout << "[+] Test 3 - OK" << endl;
}

void unit_system_destructor() {
    cout << "[!] Test 4 - System Destructor" << endl;

    System *sys = new SystemImpl("System", 1.0);
    delete sys;

    cout << "[+] Test 4 - OK" << endl;
}

void unit_system_getName() {
    cout << "[!] Test 5 - System GetName" << endl;

    System *sys = new SystemImpl("System", 1.0);

    assert(sys->getName() == "System");

    cout << "[+] Test 5 - OK" << endl;
}

void unit_system_setName() {
    cout << "[!] Test 6 - System SetName" << endl;

    System *sys = new SystemImpl("System", 1.0);
    sys->setName("New System");

    assert(sys->getName() == "New System");

    cout << "[+] Test 6 - OK" << endl;
}

void unit_system_getContent() {
    cout << "[!] Test 7 - System GetContent" << endl;

    System *sys = new SystemImpl("System", 1.0);

    assert(sys->getContent() == 1.0);

    cout << "[+] Test 7 - OK" << endl;
}

void unit_system_setContent() {
    cout << "[!] Test 8 - System SetContent" << endl;

    System *sys = new SystemImpl("System", 1.0);
    sys->setContent(100.0);

    assert(sys->getContent() == 100.0);

    cout << "[+] Test 8 - OK" << endl;
}

void UnitSystem::unit_system_assignmentOperator() {
    cout << "[!] Test 9 - System Assignment Operator" << endl;

    SystemImpl *sys1 = new SystemImpl("Copy System", 1.0);
    SystemImpl *sys2 = new SystemImpl();

    *sys2 = *sys1;

    sys1->setName("Original System");
    sys1->setContent(100.0);

    assert(sys2->getName() == "Copy System");
    assert(sys2->getContent() == 1.0);

    cout << "[+] Test 9 - OK" << endl;
}

void run_unit_tests_system() {
    UnitSystem *unit_system = new UnitSystem();

    // Calling System Unit Tests
    unit_system_constructor();
    unit_system->unit_system_copy_constructor();
    unit_system_destructor();
    unit_system_getName();
    unit_system_setName();
    unit_system_getContent();
    unit_system_setContent();
    unit_system->unit_system_assignmentOperator();

    delete unit_system;
}

