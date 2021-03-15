#ifndef ADM_H_
#define ADM_H_
#include <string>
#include <iostream>
#include "../headers/funcionario.hpp"
#include "../headers/mecanico.hpp"
#include "../headers/vendedor.hpp"

using namespace std;

class Adm: public Funcionario // Adm herda funcionario
{

vector<Vendedor*> reg_vendedores;
vector<Mecanico*> reg_mecanicos;


public:

    Adm(int id, string nome, string senha, string username);

    void regMec(Mecanico* mec);
    void regVen(Vendedor* ven);

    int getIdMec(Mecanico* mec);
    string getUsernameMec(Mecanico* mec);
    string getSenhaMec(Mecanico* mec);

    int getIdVen(Vendedor* ven);
    string getUsernameVen(Vendedor* ven);
    string getSenhaVen(Vendedor* ven);

    void setIdMec(Mecanico* mec, int id);
    void setUsernameMec(Mecanico* mec, string username);
    void setSenhaMec(Mecanico* mec, string senha);

    void setIdVen(Vendedor* ven, int id);
    void setUsernameVen(Vendedor* ven, string username);
    void setSenhaVen(Vendedor* ven, string senha);

    void menuAdmin();

    Vendedor* retVend(int index);
    Mecanico* retMec(int index);

    int totalVend();
    int totalMec();



};


#endif /* ADM_H_ */