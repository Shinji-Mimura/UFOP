#include "Unit_System.h"
#include "Unit_Flow.h"
#include "Unit_Model.h"

int main() {

    cout << endl << "Initializing Unit Tests" << endl << endl;

    cout << "+---------------------+" << endl;
    cout << "| Unit Tests:  System |" << endl;
    cout << "+---------------------+" << endl << endl;

    run_unit_tests_system();

    cout << endl;

    cout << "+-------------------+" << endl;
    cout << "| Unit Tests:  Flow |" << endl;
    cout << "+-------------------+" << endl << endl;

    run_unit_tests_flow();

    cout << endl;

    cout << "+--------------------+" << endl;
    cout << "| Unit Tests:  Model |" << endl;
    cout << "+--------------------+" << endl << endl;

    run_unit_tests_model();

    cout << endl << "Finalizing Unit Tests" << endl;

    return 0;
}
