#ifndef UNIT_FLOW_H
#define UNIT_FLOW_H

#include "../../src/lib/SystemImpl.h"
#include "../../src/lib/FlowImpl.h"
#include <cassert>

/**
 * @brief Class to test flow methods
 */

class UnitFlow {
public:
    UnitFlow() {}

    ~UnitFlow() {}

    void unit_flow_copy_constructor();

    void unit_flow_assignmentOperator();
};

/**
 * @brief Test of flow constructor
 * return void
 */

void unit_flow_constructor();

/**
 * @brief Test of flow destructor
 * return void
 */

void unit_flow_destructor();

/**
 * @brief Test of flow get name method
 * return void
 */

void unit_flow_getName();

/**
 * @brief Test of flow set name method
 * return void
 */

void unit_flow_setName();

/**
 * @brief Test of flow get input method
 * return void
 */

void unit_flow_getInput();

/**
 * @brief Test of flow set input method
 * return void
 */

void unit_flow_setInput();

/**
 * @brief Test of flow get output method
 * return void
 */

void unit_flow_getOutput();

/**
 * @brief Test of flow set output method
 * return void
 */

void unit_flow_setOutput();

/**
 * @brief Test of flow remove input method
 * return void
 */

void unit_flow_removeInput();

/**
 * @brief Test of flow remove output method
 * return void
 */

void unit_flow_removeOutput();

/**
 * @brief Test of flow equation method
 * return void
 */

void unit_flow_equation();

/**
 * @brief Function to run all flows unit tests
 * return void
 */

void run_unit_tests_flow();

#endif
