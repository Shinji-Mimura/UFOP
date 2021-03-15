using namespace std;

#include "../headers/ordem.hpp"


Ordem::Ordem(string PedCliente, int id_cliente) {
    this->PedCliente = PedCliente;
    this->RepMec = "";
    this->orca = 0.0;
    this->status = false;
    this->id_cliente = id_cliente;

}

string Ordem::getPed(){
    return this->PedCliente;
}

string Ordem::getRepMec(){
    return this->RepMec;
}

string Ordem::getStatus(){

    if (this->status == true)
    {
        return "Aprovado";
    }

    else
    {
        return "Pendente";
    }
    
    
}

float Ordem::getOrca(){
    return this->orca;
}

void Ordem::setStatus(bool value){
    this->status = value;
}

void Ordem::setOrca(float value){
    this->orca = value;
}

void Ordem::setRepMec(string resposta){
    this->RepMec = resposta;
}

int Ordem::getIdCliente(){
    return this->id_cliente;
}