#include "FuncionalTests.h"
#include <cmath>

class LogisticalFlow : public FlowHandle {
public:
    LogisticalFlow(string name, System *input, System *output) : FlowHandle(name, input, output) {}

    double equation() {
        if (getOutput() != NULL) {
            return 0.01 * (getOutput()->getContent()) * (1 - (getOutput()->getContent()) / 70);
        } else {
            return 0;
        }
    }
};

class ExponentialFlow : public FlowHandle {
public:
    ExponentialFlow(string name, System *input, System *output) : FlowHandle(name, input, output) {}

    double equation() {

        if (getInput() != NULL) {
            return 0.01 * (getInput()->getContent());
        } else {
            return 0;
        }
    }
};

class ComplexFlow : public FlowHandle {
public:
    ComplexFlow(string name, System *input, System *output) : FlowHandle(name, input, output) {}

    double equation() {

        if (getInput() != NULL) {
            return 0.01 * (getInput()->getContent());
        } else {
            return 0;
        }
    }
};

void exponentialFuncionalTest() {

    Model *expModel = Model::createModel("Exponential Model");

    System *pop1 = expModel->createSystem("pop1", 100);
    System *pop2 = expModel->createSystem("pop2", 0);

    Flow *expFlow = expModel->createFlow<ExponentialFlow>("exponential", pop1, pop2);

    expModel->execute(0, 100, 1);

    assert(fabs(pop1->getContent()) - 36.6032 < 0.0001);
    assert(fabs(pop2->getContent()) - 63.3968 < 0.0001);

    delete expModel;

    cout << "[+] Teste Exponencial Executado com Sucesso!" << endl;

}

void logisticalFuncionalTest() {

    Model *logModel = Model::createModel("LogisticalModelImpl");

    System *s1 = logModel->createSystem("s1", 100);
    System *s2 = logModel->createSystem("s2", 10);

    Flow *log = logModel->createFlow<LogisticalFlow>("logistical", s1, s2);


    logModel->execute(0, 100, 1);

    assert(fabs(s1->getContent()) - 88.2167 < 0.0001);
    assert(fabs(s2->getContent()) - 21.7833 < 0.0001);

    delete logModel;

    cout << "[+] Teste Logistico Executado com Sucesso!" << endl;
}

void complexFuncionalTest() {

    // SystemImpls
    Model *model = Model::createModel("Modelo complexo");

    System *q1 = model->createSystem("P1", 100.0);
    System *q2 = model->createSystem("P2", 0.0);
    System *q3 = model->createSystem("P3", 100.0);
    System *q4 = model->createSystem("P4", 0.0);
    System *q5 = model->createSystem("P5", 0.0);

    Flow *f = model->createFlow<ComplexFlow>("f", q1, q2);
    Flow *g = model->createFlow<ComplexFlow>("g", q1, q3);
    Flow *r = model->createFlow<ComplexFlow>("r", q2, q5);
    Flow *t = model->createFlow<ComplexFlow>("t", q2, q3);
    Flow *u = model->createFlow<ComplexFlow>("u", q3, q4);
    Flow *v = model->createFlow<ComplexFlow>("v", q4, q1);


    model->execute(0, 100, 1);

    //asserts
    assert(abs((q1->getContent() - 31.8513)) < 0.0001);
    assert(abs((q2->getContent() - 18.4003)) < 0.0001);
    assert(abs((q3->getContent() - 77.1143)) < 0.0001);
    assert(abs((q4->getContent() - 56.1728)) < 0.0001);
    assert(abs((q5->getContent() - 16.4612)) < 0.0001);

    //delete
    delete model;
    cout << "[+] Teste Complexo Executado com Sucesso!" << endl;
}

