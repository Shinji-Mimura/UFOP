#include "../headers/veiculo.hpp"

using namespace std;

Veiculo::~Veiculo() {}

Veiculo::Veiculo(string placa, float quilometragem){
    this->placa = placa;
    this->quilometragem = quilometragem;
}

void Veiculo::addHistAjust(string ajuste){
    this->hist_ajust.push_back(ajuste);
}

string Veiculo::getPlaca(){
    return this->placa;
}

float Veiculo::getQuilometragem(){
    return this->quilometragem;
}

string Veiculo::getHist(){
    string todas_respostas = "";

    for (int i = 0; i < this->hist_ajust.size(); i++)
    {
        todas_respostas = todas_respostas + this->hist_ajust[i] + "\n";
    }
    
    return todas_respostas;
}

int Veiculo::getTamHist(){
    return this->hist_ajust.size();
}