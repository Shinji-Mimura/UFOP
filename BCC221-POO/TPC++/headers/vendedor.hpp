#ifndef VENDEDOR_H_
#define VENDEDOR_H_
#include <string>
#include <iostream>
#include <cstdlib>
#include <vector>
#include<map>
#include <utility>
#include "../headers/funcionario.hpp"
#include "../headers/cliente.hpp"
#include "../headers/ordem.hpp"
#include "../headers/registros.hpp"
using namespace std;

class Cliente;
class Ordem;
class Registros;

class Vendedor: public Funcionario
{

Registros* registro;


public:
    
    friend class Adm;
    Vendedor(int id, string nome, string senha, string username, Registros* registro);
    bool CadCliente();
    Ordem* GenOrdem(int id_cliente);


    void ViOrdem_Cliente();

    string AprovarPedido(int i);

    string menuProdutos();

    void verPedidosConcluidos();
    
    void entregarPedido(int index);

    void HistVeiCliente(int id_cliente);

    void verTodosClientes();

     

};


#endif /* VENDEDOR_H_ */