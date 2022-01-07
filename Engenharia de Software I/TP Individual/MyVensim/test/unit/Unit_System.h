#ifndef UNIT_SYSTEM_H
#define UNIT_SYSTEM_H

#include "../../src/lib/SystemImpl.h"
#include <cassert>

/**
 * @brief Class to test system methods
 */

class UnitSystem {
public:
    UnitSystem() {}

    ~UnitSystem() {}

    void unit_system_copy_constructor();

    void unit_system_assignmentOperator();
};

/**
 * @brief Test of system constructor
 * @return void
 */

void unit_system_constructor();

/**
 * @brief Test of system destructor
 * @return void
 */

void unit_system_destructor();

/**
 * @brief Test of system get name method
 * @return void
 */

void unit_system_getName();

/**
 * @brief Test of system set name method
 * @return void
 */

void unit_system_setName();

/**
 * @brief Test of system get content method
 * @return void
 */

void unit_system_getContent();

/**
 * @brief Test of system set content method
 * @return void
 */

void unit_system_setContent();

/**
 * @brief Function to run all system unit tests
 * @return void
 */

void run_unit_tests_system();

#endif
