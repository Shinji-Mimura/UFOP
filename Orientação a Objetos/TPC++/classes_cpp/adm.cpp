using namespace std;

#include "../headers/adm.hpp"


Adm::Adm(int id, string nome, string senha, string username) {
    this->setId(id);
    this->setNome(nome);
    this->setUsername(username);
    this->setSenha(senha);
}

void Adm::regMec(Mecanico* mec){
    this->reg_mecanicos.push_back(mec);
}

void Adm::regVen(Vendedor* ven){
    this->reg_vendedores.push_back(ven);
}

// Mecânico ///////////////////////

int Adm::getIdMec(Mecanico* mec) {
    return mec->getId();
}

string Adm::getSenhaMec(Mecanico* mec){
    return mec->getSenha();
}

string Adm::getUsernameMec(Mecanico* mec){
    return mec->getUsername();
}

void Adm::setIdMec(Mecanico* mec, int id){
    mec->setId(id);
}

void Adm::setSenhaMec(Mecanico* mec, string senha){
    mec->setSenha(senha);
}

void Adm::setUsernameMec(Mecanico* mec, string username){
    mec->setUsername(username);
}

// Vendedor ///////////////////////

int Adm::getIdVen(Vendedor* ven){
    return ven->getId();
}

string Adm::getSenhaVen(Vendedor* ven){
    return ven->getSenha();
}

string Adm::getUsernameVen(Vendedor* ven){
    return ven->getUsername();
}

void Adm::setIdVen(Vendedor* ven, int id){
    ven->setId(id);
}

void Adm::setSenhaVen(Vendedor* ven, string senha){
    ven->setSenha(senha);
}

void Adm::setUsernameVen(Vendedor* ven, string username){
    ven->setUsername(username);
}

// Menu ///////////////////

void Adm::menuAdmin()
{
    int op;
    cout << "Qual deseja editar?" << endl;
    cout << "1 ADM | 2 Vendedores | 3  Mecânico: "; 
    std::cin >> op;

    if (op == 1)
    {

            cout << "Edição Admin" << endl;

            cout << "Nome: " << this->getNome() << endl;

            int opcao;

            string username, senha;

            cout << "Digite opção que deseja editar" << endl;
            cout << "1 Username | 2 Senha: ";
            std::cin >> opcao;

            switch (opcao)
            {
            case 1:
                    
                cout << "Digite seu novo username: ";
                std::cin >> username;
                this->setUsername(username);

                break;
                
            case 2:

                cout << "Digite sua nova senha: ";
                std::cin >> senha;
                this->setSenha(senha);
            default:
                cout << "Inválido!" << endl;
                break;
                }

    }
    


    if (op == 2)
    {
        cout << "Lista De Vendedores" << endl;

        for (int i = 0; i < this->reg_vendedores.size(); i++)
        {
            cout << "ID: " << this->reg_vendedores[i]->getId() << " " << "Nome: " << this->reg_vendedores[i]->getNome() << " " << "Username: " << this->reg_vendedores[i]->getUsername() << endl;
        }

        int id;
        cout << "Digite o ID do Vendedor que deseja editar: " << endl;
        std::cin >> id;

        for (int i = 0; i < this->reg_vendedores.size(); i++)
        {
            if (id == this->reg_vendedores[i]->getId())
            {   
                int opcao;

                string username, senha;

                cout << "Digite opção que deseja editar" << endl;
                cout << "1 Username | 2 Senha: ";
                std::cin >> opcao;

                switch (opcao)
                {
                case 1:
                    
                    cout << "Digite seu novo username: ";
                    std::cin >> username;
                    this->reg_vendedores[i]->setUsername(username);

                    break;
                
                case 2:

                    cout << "Digite sua nova senha: ";
                    std::cin >> senha;
                    this->reg_vendedores[i]->setSenha(senha);

                    break;

                default:
                    cout << "Inválido!" << endl;
                    break;
                }

            }
            
            
        }
      
        
    }
    
    
    if (op == 3)
    {
        cout << "Lista De Mecânicos" << endl;

        for (int i = 0; i < this->reg_mecanicos.size(); i++)
        {
            cout << "ID: " << this->reg_mecanicos[i]->getId() << " " << "Nome: " << this->reg_mecanicos[i]->getNome() << " " << "Username: " << this->reg_mecanicos[i]->getUsername() << endl;
        }

        int id;
        cout << "Digite o ID do Vendedor que deseja editar: ";
        std::cin >> id;

        for (int i = 0; i < this->reg_mecanicos.size(); i++)
        {
            if (id == this->reg_mecanicos[i]->getId())
            {   
                int opcao;

                string username, senha;

                cout << "Digite opção que deseja editar" << endl;
                cout << "1 Username | 2 Senha: ";
                std::cin >> opcao;

                switch (opcao)
                {
                case 1:
                    
                    cout << "Digite seu novo username: ";
                    std::cin >> username;
                    this->reg_mecanicos[i]->setUsername(username);

                    break;
                
                case 2:

                    cout << "Digite sua nova senha: ";
                    std::cin >> senha;
                    this->reg_mecanicos[i]->setSenha(senha);

                    break;

                default:
                    cout << "Inválido!" << endl;
                    break;
                }

            }
            
        }
        
        
    }
    
}

int Adm::totalVend(){
    return this->reg_vendedores.size();
}

int Adm::totalMec(){
    return this->reg_mecanicos.size();
}

Vendedor* Adm::retVend(int index){
    return this->reg_vendedores[index];
}

Mecanico* Adm::retMec(int index){
    return this->reg_mecanicos[index];
}