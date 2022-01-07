#include "../headers/registros.hpp"

using namespace std;

Registros::~Registros() {}

Registros::Registros(){
    
}

long int Registros::getCpfCliente(int index){
    return this->reg_clientes[index]->getCpf();
    
}

int Registros::getIdCliente(int index){
    return this->reg_clientes[index]->getId();
}

string Registros::getNomeCliente(int index){
    return this->reg_clientes[index]->getNome();
}

Ordem* Registros::getOrdemCliente(int index){
    return this->reg_clientes[index]->getOrdem();
}

Veiculo* Registros::getVeiculoCliente(int index){
    return this->reg_clientes[index]->getVeiculo();
}

int Registros::getRegTamanho(){
    return this->reg_clientes.size();
}

void Registros::setPedAprovados(Ordem* ped_aprovado){
    this->ped_aprovados.push_back(ped_aprovado);
}

void Registros::mostraPedAprovados(){
    
    cout << "Pedidos Aprovados" << endl;
    cout << "-----------------" << endl;

    for (int i = 0; i < this->ped_aprovados.size(); i++)
    {
        cout << "ID: " << i << " | Produto: " << this->ped_aprovados[i]->getPed()  << " | Status: " << this->ped_aprovados[i]->getStatus() << endl;
    }
    
}

void Registros::setPedConcluidos(Ordem* ped_concluido) {
    this->ped_concluidos.push_back(ped_concluido);
}

void Registros::mostraPedConcluidos(){

    cout << "Pedidos Concluídos" << endl;
    cout << "------------------" << endl;

    for (int i = 0; i < this->ped_concluidos.size(); i++)
    {
        cout << "ID: " << i << " | Produto: " << this->ped_concluidos[i]->getPed()  << " | Resposta do Mecânico: " << this->ped_concluidos[i]->getRepMec() << endl;
    }
    
}

void Registros::remPedConcluido(int index){
    this->ped_concluidos.erase(this->ped_concluidos.begin() + index);
    cout << "Pedido Entregue ao Cliente" << endl;
}

Cliente* Registros::getCliente(int id_cliente){
    
    for (int i = 0; i < this->reg_clientes.size(); i++)
    {
        if (id_cliente == this->reg_clientes[i]->getId())
        {
            return this->reg_clientes[i];
        }
        
    }

    return nullptr;

}

int Registros::getTamPedAprovados(){
    return this->ped_aprovados.size();
}

int Registros::getTamPedConcluidos(){
    return this->ped_concluidos.size();
}

Ordem* Registros::getPedAprovado(int index){
    return this->ped_aprovados[index];
}

Ordem* Registros::getPedConcluido(int index){
    return this->ped_concluidos[index];
}