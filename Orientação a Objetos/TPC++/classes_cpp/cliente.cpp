using namespace std;

#include "../headers/cliente.hpp"



Cliente::Cliente(string nome, long int cpf, int id, Ordem* ordem, Veiculo* veiculo) {

    this->nome = nome;
    this->cpf = cpf;
    this->id = id;
    ordem_servico = ordem;
    vei_cliente = veiculo;

}

long int Cliente::getCpf(){
    return this->cpf;
}

int Cliente::getId(){
    return this->id;
}

string Cliente::getNome(){
    return this->nome;
}

Ordem* Cliente::getOrdem(){
    return this->ordem_servico;
}

Veiculo* Cliente::getVeiculo(){
    return this->vei_cliente;
}
