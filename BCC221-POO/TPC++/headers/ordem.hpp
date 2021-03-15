#ifndef ORDEM_H_
#define ORDEM_H_
#include <string>
#include <iostream>
#include "../headers/cliente.hpp"

using namespace std;

class Ordem
{ 

string PedCliente;
string RepMec;
bool status;
float orca;
int id_cliente; // será usada para que o mêcanico registre no veiculo de determinado cliente as mudanças no histórico

public:
    friend class Cliente;
    Ordem(string PedCliente, int id_cliente);

    string getPed();
    string getRepMec();
    string getStatus();
    float getOrca();

    void setOrca(float value);

    void setRepMec(string resposta);

    void setStatus(bool value);

    int getIdCliente();
    

};





#endif /* ORDEM_H_ */