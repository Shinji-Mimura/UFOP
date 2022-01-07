//tentativa de tela de login 
using namespace std;
//includes... 
#include <iostream>
#include <vector>
#include "../headers/vendedor.hpp"
#include "../headers/mecanico.hpp"
#include "../headers/adm.hpp"
#include "../headers/funcionario.hpp"
#include "../headers/registros.hpp"

void delReg(Registros* reg_geral){

    for (int i = 0; i < reg_geral->getRegTamanho(); i++)
    {
        delete reg_geral->getCliente(i)->getVeiculo(); //Deleta veiculo do cliente
        delete reg_geral->getCliente(i)->getOrdem(); // deleta ordem de serviço do cliente
        delete reg_geral->getCliente(i); //Deleta Clientes
    }
    
    for (int i = 0; i < reg_geral->getTamPedAprovados(); i++)
    {
        delete reg_geral->getPedAprovado(i); //Deleta Ordens Aprovadas
    }

    for (int i = 0; i < reg_geral->getTamPedConcluidos(); i++)
    {
        delete reg_geral->getPedConcluido(i); //Deleta Ordens Concluidas
    }
    
    delete reg_geral; // Por fim, deleta o registro geral

}

void delAdmin(Adm* admin){
    

    for (int i = 0; i < admin->totalVend(); i++)
    {
        delete admin->retVend(i); // apaga todos os vendedores
    }

    for (int i = 0; i < admin->totalMec(); i++)
    {
        delete admin->retMec(i); // apaga todos os mecânicos
    }
    
    delete admin; // por fim apaga o admin

}


void loginMecanico(Adm* admin);
void loginVendedor(Adm* admin);
void loginAdmin(Adm* admin);
void menuLogin(Adm* admin);

void menuAdmin(Adm* admin){


    int op;

    cout << "Menu Administrador" << endl;
    cout << endl;
    cout << "1) Admin" << endl;
    cout << "2) Vendedor" << endl;
    cout << "3) Mecânico" << endl;
    cout << "4) Deslogar" << endl;
    cout << endl;
    cout << "Selecione Qual Classe Você Deseja Editar: ";
    cin >> op;

    if (op == 1)
    {
        int op2;

        string novo_nome;
        string novo_username;
        string nova_senha;

        cout << endl;
        cout << "1) Nome" << endl;
        cout << "2) Username" << endl;
        cout << "3) Senha" << endl;
        cout << endl;


        cout << "Digite a opção que deseja editar: ";
        cin >> op2;


        switch (op2)
        {
        case 1:

            cout << "Digite o novo nome: ";
            cin >> novo_nome;
            admin->setNome(novo_nome);

            break;
        
        case 2:

            cout << "Digite o novo username: ";
            cin >> novo_username;
            admin->setUsername(novo_username);
        
            break;

        case 3:

            cout << "Digite a nova senha: ";
            cin >> nova_senha;
            admin->setSenha(nova_senha);

            break;

        default:
            cout << "Opção Inválida!" << endl;
            break;
        }

    }

    else if (op == 2)
    {
        Vendedor* vend; // vendedor que vai ser alterado;

        cout << "Lista de Vendedores" << endl;
        cout << "-------------------" << endl;
        cout << endl;

        for (int i = 0; i < admin->totalVend(); i++)
        {
            vend = admin->retVend(i);
            cout << "Nome: " << vend->getNome() << " | ID: " << vend->getId() << endl;
        }

        cout << endl;
        cout << "-------------------" << endl;

        int id;
        cout << "Digite o ID do vendedor que deseja editar: ";
        cin >> id;

        for (int i = 0; i < admin->totalVend(); i++)
        {
            vend = admin->retVend(i);
            
            if (id == vend->getId())
            {
                int op3;
                string novo_nome;
                string novo_username;
                string nova_senha;

                cout << endl;
                cout << "1) Username" << endl;
                cout << "2) Senha" << endl;
                cout << endl;


                cout << "Digite a opção que deseja editar: ";
                cin >> op3;


                switch (op3)
                {
                case 1:

                    cout << "Digite o novo username: ";
                    cin >> novo_username;
                    admin->setUsernameVen(vend,novo_username);

                    break;
                
                case 2:

                    cout << "Digite a nova senha: ";
                    cin >> nova_senha;
                    admin->setSenhaVen(vend,nova_senha);
                
                    break;

                default:
                    break;
                }



            }
            

        }

        



    }
    
    else if (op == 3) 
    {

        Mecanico* mec; // vendedor que vai ser alterado;

        cout << "Lista de Mecânicos" << endl;
        cout << "-------------------" << endl;
        cout << endl;

        for (int i = 0; i < admin->totalMec(); i++)
        {
            mec = admin->retMec(i);
            cout << "Nome: " << mec->getNome() << " | ID: " << mec->getId() << endl;
        }

        cout << endl;
        cout << "-------------------" << endl;

        int id;
        cout << "Digite o ID do mecânico que deseja editar: ";
        cin >> id;

        for (int i = 0; i < admin->totalMec(); i++)
        {
            mec = admin->retMec(i);
            
            if (id == mec->getId())
            {
                int op3;
                string novo_nome;
                string novo_username;
                string nova_senha;

                cout << endl;
                cout << "1) Username" << endl;
                cout << "2) Senha" << endl;
                cout << endl;


                cout << "Digite a opção que deseja editar: ";
                cin >> op3;


                switch (op3)
                {
                case 1:

                    cout << "Digite o novo username: ";
                    cin >> novo_username;
                    admin->setUsernameMec(mec,novo_username);

                    break;
                
                case 2:

                    cout << "Digite a nova senha: ";
                    cin >> nova_senha;
                    admin->setSenhaMec(mec,nova_senha);
                
                    break;

                default:
                    break;
                }



            }
            

        }

    }

    else if (op == 4)
    {
        menuLogin(admin);
    }
    
}

void menuVendedor(Adm* admin, int indice_correto){
    Vendedor* vend;
    vend = admin->retVend(indice_correto);

    int op;


    cout << "Menu Vendedor" << endl;
    cout << endl;
    cout << "1) Cadastrar Cliente" << endl;
    cout << "2) Visualizar Ordens de Cliente" << endl;
    cout << "3) Ver Pedidos Concluidos" << endl;
    cout << "4) Ver Todos os Clientes Cadastrados" << endl;
    cout << "5) Deslogar" << endl;
    cout << endl;
    cout << "Selecione a Opção: ";
    cin >> op;

    switch (op)
    {
    case 1:
        vend->CadCliente();
        break;
    
    case 2:
        vend->ViOrdem_Cliente();
        break;
    
    case 3:
        vend->verPedidosConcluidos();
        break;

    case 4:
        vend->verTodosClientes();

    case 5:
        return menuLogin(admin);

    default:
        cout << "Opção Inválida!" << endl;
        break;
    }

}

void menuMecanico(Adm* admin, int indice_correto){
    Mecanico* mec;
    mec = admin->retMec(indice_correto);

    int op;

    cout << "Menu Mecânico" << endl;
    cout << endl;
    cout << "1) Atender Pedidos" << endl;
    cout << "2) Ver Pedidos Concluidos" << endl;
    cout << "3) Deslogar" << endl;
    cout << endl;
    cout << "Selecione a Opção: ";
    cin >> op;

    switch (op)
    {
    case 1:
        mec->atendePedido();
        break;
    
    case 2:
        mec->verPedidosConcluidos();
        break;
    
    case 3:
        return menuLogin(admin);
        break;

    default:
        cout << "Opção Inválida!" << endl;
        break;
    }

}

int main(int argc, char const *argv[])
{
    Registros* registro_geral;
    registro_geral = new Registros();

    Vendedor *vend1, *vend2;
    Mecanico *mec;
    
    vend1 = new Vendedor(0,"Lucas","OscarWilde","lucas",registro_geral);
    vend2 = new Vendedor(1,"Bárbara","StephenKing","barbara",registro_geral);
    mec = new Mecanico(0,"Guillermo","POO","guillermo",registro_geral);

    Adm *teste;
    teste = new Adm(3,"Sidarta","Gotama","sidarta");

    teste->regMec(mec);
    teste->regVen(vend1);
    teste->regVen(vend2);

    menuLogin(teste);

    delAdmin(teste); // deleta admin, vendedores e mecânicos
    delReg(registro_geral); // deleta registro geral



    return 0;
}



void menuLogin(Adm* admin)
{
    int logar;
    do
    {    
        cout << "\nTela de Login" << endl;
        cout << "-------------" << endl;
        cout << "Como deseja logar: " << endl;
        cout << "1 - Mecanico \n2 - Vendedor \n3 - Admin \n0 - Sair" << endl;
        cin >> logar;

        switch (logar) 
        {
            case 1: 
            {
                loginMecanico(admin);
                
                break;
            }
            case 2:
            {
                loginVendedor(admin);
                break;
            }
            case 3: 
            {
                loginAdmin(admin);
                break;
            }
            case 0:         
                break;
            default: 
                cout << "OPÇÃO INVÁLIDA!!";
        }
    } while (logar != 0);    

}

void loginVendedor(Adm* admin)
{
    bool test = false;
    int indice_correto;
    do 
    { 
        string login, senha;
        cout << "\nNome de Usuario: ";
        cin >> login; 
        cout << "Senha: ";
        cin >> senha;

        Vendedor* vend;


        
        

        for (int i = 0; i < admin->totalVend() ; i++)
        {
            vend = admin->retVend(i);
            if (admin->getUsernameVen(vend).compare(login) == 0 && admin->getSenhaVen(vend).compare(senha) == 0)
            {
                test = true;
                indice_correto = i;
            }
        }

        if (test == false)
        {
            cout << "Usuário ou Senha Incorretos! Tente Novamente" << endl;
        }

    } while ( test != true );

    menuVendedor(admin, indice_correto);


}

void loginMecanico(Adm* admin)
{ 
    bool test = false;
    int indice_correto;
    do 
    { 
        string login, senha;
        cout << "\nNome de Usuario: ";
        cin >> login; 
        cout << "Senha: ";
        cin >> senha;

        Mecanico* mec;

        for (int i = 0; i < admin->totalMec(); i++)
        {
            mec = admin->retMec(i);

            if (admin->getUsernameMec(mec).compare(login) == 0 && admin->getSenhaMec(mec).compare(senha) == 0){
                test = true;
                indice_correto = i;
            }
        }

        if (test == false)
        {
            cout << "Usuário ou Senha Incorretos! Tente Novamente" << endl;
        }
    } while ( test != true );

    menuMecanico(admin, indice_correto);
}

void loginAdmin(Adm* admin)
{
    bool teste = false;
    do{
        string login, senha;
        cout << "\nNome de Usuario: ";
        cin >> login; 
        cout << "Senha: ";
        cin >> senha;

        if (admin->getUsername().compare(login) == 0 && admin->getSenha().compare(senha) == 0){
            teste = true;
        }
        
        if (teste == false)
        {
            cout << "Usuário ou Senha Incorretos! Tente Novamente" << endl;
        }
        
    } while (teste != true);

    menuAdmin(admin); 
}