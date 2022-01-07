#include "FuncionalTests.h"

int main() {

    cout << endl;

    cout << "+--------------------------------+" << endl;
    cout << "| Iniciando Testes Funcionais... |" << endl;
    cout << "+--------------------------------+" << endl << endl;

    exponentialFuncionalTest();
    logisticalFuncionalTest();
    complexFuncionalTest();

    cout << endl;

    cout << "+---------------------------------+" << endl;
    cout << "| Testes Funcionais Finalizados ! |" << endl;
    cout << "+---------------------------------+" << endl << endl;

    return 0;
}
