using namespace std;

#include "../headers/vendedor.hpp"


typedef const pair<std::string, float> produtos;

std::map<produtos, int> reg_produtos = {
    {make_pair("Alinhamento", 150.80), 1}, 
    {make_pair("Balanceamento", 110.70), 2},
    {make_pair("Motor", 220.80), 3},
    {make_pair("Pneu", 190.60), 4},
    {make_pair("Carburador", 140.10), 5},
    {make_pair("Retrovisor", 50.20), 6},
    {make_pair("Freio", 250.30), 7}
};

Vendedor::Vendedor(int id, string nome, string senha, string username, Registros* registro) {
    this->id = id;
    this->nome = nome;
    this->senha = senha;
    this->username = username;
    this->registro = registro;
}

bool Vendedor::CadCliente(){

    long int cpf;


    cout << "Digite o CPF do Cliente: ";

    std::cin >> cpf;

    for (int i = 0; i < this->registro->getRegTamanho(); i++)
    {
        if ( this->registro->getCpfCliente(i) == cpf)
        {
            cout << "Cliente já cadastrado!" << endl;
            cout << "Nome do Cliente: " << this->registro->getNomeCliente(i) << " |ID: " << this->registro->getIdCliente(i) << endl;
            this->HistVeiCliente(this->registro->getIdCliente(i));
        
            return false;
        }
        
    }

    string nome;
    float cpf_novo;
    int id;

    string placa;
    float quilometragem;

    cout << endl;
    cout << "Cliente Não Cadastrado! Iniciando Processo de Cadastramento..." << endl;
    cout << endl;

    cout << "Cadastro de cliente" << endl;
    cout << "-------------------" << endl;
    cout << "Nome: ";
    cin >> nome;
    cout << "CPF: ";
    cin >> cpf_novo;
    id = rand() % 10000;

    cout << "Cadastro do Veiculo do cliente: " << nome << endl;
    cout << "-------------------" << endl;
    cout << "Placa: ";
    cin >> placa;
    cout << "Quilometragem: ";
    cin >> quilometragem;

    Veiculo* veiculo_novo = new Veiculo(placa,quilometragem);

    Ordem* ord_nova = GenOrdem(id);

    Cliente* cliente_novo = new Cliente(nome, cpf, id, ord_nova, veiculo_novo);



    this->registro->reg_clientes.push_back(cliente_novo);

    cout << "Cliente Cadastrado com Sucesso! " << endl;

    return true;
    

}

Ordem* Vendedor::GenOrdem(int id_cliente){

    cout << endl;
    cout << "Gerador de Ordem de Serviço" << endl;

    string pedCliente = this->menuProdutos();

    cout << "O pedido selecionado foi: " << pedCliente << endl;

    Ordem* ord = new Ordem(pedCliente, id_cliente);

    return ord;

}

void Vendedor::ViOrdem_Cliente(){

    cout << "Lista de Clientes" << endl;
    cout << "-----------------" << endl;

    for (int i = 0; i < this->registro->reg_clientes.size(); i++)
    {
        cout << "ID: " << this->registro->getIdCliente(i) << " | " << "Nome: " <<  this->registro->getNomeCliente(i) << " | " << "CPF: " <<  this->registro->getCpfCliente(i) << " | Status da Ordem: " << this->registro->getOrdemCliente(i)->getStatus() << endl;

    }

    int id;

    cout << "Digite o ID do cliente: ";
    std::cin >> id;

    for (int i = 0; i < this->registro->reg_clientes.size(); i++)
    {
        if (id == this->registro->getIdCliente(i))
        {
            cout << "Ordem do Cliente " << this->registro->getNomeCliente(i) << endl;
            cout << "----------------" << endl;
            cout << "Pedido: " << this->registro->getOrdemCliente(i)->getPed() << endl;
            cout << "Status: " << this->registro->getOrdemCliente(i)->getStatus() << endl;

            int op;

            cout << "Deseja Aprovar Este Pedido? 1 SIM | 2 NÃO " << endl;
            std::cin >> op;

            switch (op)
            {
            case 1:
                cout << AprovarPedido(i) << endl;
                break;
            
            case 2:
                cout << "Pedido Não Aprovado! Saindo..." << endl;
                break;

            default:
                cout << "Inválido!" << endl;
                break;
            }


        }
        
    }

    //this->registro->mostraPedAprovados();
    
    

}

string Vendedor::AprovarPedido(int i){

    this->registro->getOrdemCliente(i)->setStatus(true);

    this->registro->setPedAprovados(this->registro->getOrdemCliente(i));


    return "Pedido Aprovado! O mecânico irá recebê-lo em breve!";
}

string Vendedor::menuProdutos(){

    cout << endl;
    cout << "Menu de Produtos da Oficina" << endl;
    cout << endl;

    for (const auto &entry: reg_produtos)
    {
        auto key_pair = entry.first;
        cout << endl;
        cout << "Produto: " << key_pair.first << " | Preço: "<< key_pair.second << " | ID: " << entry.second << endl;
        cout << "-----------------------------------------------------------------------------" << endl; 
    }


    while(true) {
        int id;
        cout << "Digite o ID do produto desejado: ";
        cin >> id;

        for (const auto &entry: reg_produtos)
        {
            auto key_pair = entry.first;
            
            if (entry.second == id)
            {
                return key_pair.first;
            }
            
        }
        
        cout << "ID Inválido!" << endl;
    }
        
    
}

void Vendedor::verPedidosConcluidos(){
    this->registro->mostraPedConcluidos();

    int id;

    cout << "Digite o ID do Pedido que deseja entregar: ";

    cin >>id;

    this->entregarPedido(id);

}
void Vendedor::entregarPedido(int index){
    this->registro->remPedConcluido(index); //Remove Pedido (simula a entrega ao cliente)
}

void Vendedor::HistVeiCliente(int id_cliente){
    Cliente* cliente = this->registro->getCliente(id_cliente);
    Veiculo* vei_cliente = cliente->getVeiculo();

    cout << "Veiculo Do Cliente: " << cliente->getNome() << endl;
    cout << "Placa: " << vei_cliente->getPlaca() << endl;
    cout << "Quilometragem: " << vei_cliente->getQuilometragem() << endl;

    cout << "Histórico de Ajustes do Véiculo: " << endl;
    cout << "-------------------------------" << endl;
    cout << vei_cliente->getHist() << endl;

}

void Vendedor::verTodosClientes(){
    
    cout << endl;
    cout << "Lista de Clientes Registrados" << endl;
    cout << endl;

    for (int i = 0; i < this->registro->reg_clientes.size(); i++)
    {
        cout << "----------------------------------------" << endl;
        cout << "ID: " << this->registro->reg_clientes[i]->getId() << endl;
        cout << "Nome: " << this->registro->reg_clientes[i]->getNome() << endl;
        cout << "CPF: " << this->registro->reg_clientes[i]->getCpf() << endl;
        cout << endl;
        cout << "Informações sobre o veículo: " << endl;
        cout << "Placa: " << this->registro->reg_clientes[i]->vei_cliente[0].getPlaca() << endl;
        cout << "Quilometragem: " << this->registro->reg_clientes[i]->vei_cliente[0].getQuilometragem() << endl;
        cout << endl;
        cout << "Histórico de ajuste  do veículo: " << endl;
        cout << this->registro->reg_clientes[i]->vei_cliente->getHist() << endl;
        cout << "----------------------------------------" << endl;

    }
    

}