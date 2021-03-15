#ifndef REGISTROS_H_
#define REGISTROS_H_
#include <string>
#include <vector>
#include<iostream>
#include "../headers/cliente.hpp"
#include "../headers/vendedor.hpp"
#include "../headers/ordem.hpp"
#include "../headers/veiculo.hpp"

using namespace std;

class Cliente;
class Ordem;

class Registros
{

private:

vector<Cliente *> reg_clientes;
vector<Ordem *> ped_aprovados;
vector<Ordem *> ped_concluidos;

public:

    
    friend class Vendedor;
    
    long int getCpfCliente(int index);
    string getNomeCliente(int index);
    int getIdCliente(int index);
    Ordem* getOrdemCliente(int index);
    Veiculo* getVeiculoCliente(int index);

    int getRegTamanho();


    void setPedAprovados(Ordem* ped_aprovado);

    void mostraPedAprovados();

    void setPedConcluidos(Ordem* ped_concluido);

    void mostraPedConcluidos();

    void remPedConcluido(int index);

    Cliente* getCliente(int id_cliente);
    
    int getTamPedAprovados();
    int getTamPedConcluidos();

    Ordem* getPedAprovado(int index);
    Ordem* getPedConcluido(int index);

    Registros();
    ~Registros();
};




#endif /* REGISTROS_H_ */
