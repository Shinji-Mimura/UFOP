#ifndef FUNCIONARIO_H_
#define FUNCIONARIO_H_
#include <string>
#include <iostream>
using namespace std;

class Funcionario
{



public:

    int id;
    string username;
    string senha;
    string nome;

    int getId();
    string getUsername();
    string getSenha();
    string getNome();

    void setId(int id);
    void setUsername(string username);
    void setSenha(string senha);
    void setNome(string nome);

    

};


#endif /* FUNCIONARIO_H_ */