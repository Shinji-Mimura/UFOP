#ifndef VEICULO_H_
#define VEICULO_H_
#include <string>
#include <vector>
#include<iostream>
using namespace std;

class Veiculo
{

string placa;
float quilometragem;
vector<string> hist_ajust;


public:
    Veiculo(string placa, float quilometragem);
    ~Veiculo();

    void addHistAjust(string ajuste);
    string getPlaca();
    float getQuilometragem();
    string getHist();

    int getTamHist();

};




#endif /* VEICULO_H_ */
