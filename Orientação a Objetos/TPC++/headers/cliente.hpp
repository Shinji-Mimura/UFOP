#ifndef CLIENTE_H_
#define CLIENTE_H_
#include <string>
#include <iostream>
#include "../headers/ordem.hpp"
#include "../headers/veiculo.hpp"
#include "../headers/vendedor.hpp"

using namespace std;

class Cliente
{

string nome;
long int cpf;
int id;

Ordem* ordem_servico;
Veiculo* vei_cliente;



public:
    friend class Vendedor;
    Cliente(string nome, long int cpf, int id, Ordem* ordem, Veiculo* veiculo);

    long int getCpf();
    int getId();
    string getNome();
    Ordem* getOrdem();
    Veiculo* getVeiculo();

    
    
};







#endif /* CLIENTE_H_ */