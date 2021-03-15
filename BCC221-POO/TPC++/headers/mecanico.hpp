#ifndef MECANICO_H_
#define MECANICO_H_
#include <string>
#include <iostream>
#include<map>
#include <utility>
#include<vector>
#include<string>
#include "../headers/funcionario.hpp"
#include "../headers/registros.hpp"
using namespace std;

class Mecanico: public Funcionario
{

Registros* registro;

public:
    
    Mecanico(int id, string nome, string senha, string username, Registros* registro);
    friend class Adm;

    void atendePedido();
    
    void verPedidosConcluidos();

};


#endif /* MECANICO_H_ */