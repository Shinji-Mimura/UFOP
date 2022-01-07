using namespace std;

#include "../headers/funcionario.hpp"


//Getters

int Funcionario::getId(){
    return this->id;
}

string Funcionario::getNome(){
    return this->nome;
}

string Funcionario::getSenha(){
    return this->senha;
}

string Funcionario::getUsername(){
    return this->username;
}

//Setters

void Funcionario::setId(int id){
    this->id = id;
}

void Funcionario::setNome(string nome){
    this->nome = nome;
}

void Funcionario::setSenha(string senha){
    this->senha = senha;
}

void Funcionario::setUsername(string username){
    this->username = username;
}