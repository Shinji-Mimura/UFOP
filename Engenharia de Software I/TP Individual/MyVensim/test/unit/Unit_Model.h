#ifndef UNIT_MODEL_H
#define UNIT_MODEL_H

#include "../../src/lib/ModelImpl.h"
#include "Unit_Flow.h"

/**
 * @brief Test of model constructor
 * @return void
 */

void unit_model_constructor();

/**
 * @brief Test of model destructor
 * @return void
 */

void unit_model_destructor();

/**
 * @brief Test of model add system method
 * @return void
 */

void unit_model_addSystem();

/**
 * @brief Test of model remove system method
 * @return void
 */

void unit_model_removeSystem();

/**
 * @brief Test of model add flow method
 * @return void
 */

void unit_model_addFlow();

/**
 * @brief Test of model remove flow method
 * @return void
 */

void unit_model_removeFlow();

/**
 * @brief Test of model get name method
 * @return void
 */

void unit_model_getName();

/**
 * @brief Test of model set name method
 * @return void
 */

void unit_model_setName();

/**
 * @brief Function to run all models unit tests
 * @return void
 */

void run_unit_tests_model();

#endif
