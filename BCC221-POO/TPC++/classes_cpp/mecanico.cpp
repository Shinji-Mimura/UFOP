using namespace std;

#include "../headers/mecanico.hpp"

typedef const pair<std::string, float> produtos;

std::map<produtos, int> reg_produtos2 = {
    {make_pair("Alinhamento", 150.80), 1}, 
    {make_pair("Balanceamento", 110.70), 2},
    {make_pair("Motor", 220.80), 3},
    {make_pair("Pneu", 190.60), 4},
    {make_pair("Carburador", 140.10), 5},
    {make_pair("Retrovisor", 50.20), 6},
    {make_pair("Freio", 250.30), 7}
};

Mecanico::Mecanico(int id, string nome, string senha, string username, Registros* registro) {
    this->id = id;
    this->nome = nome;
    this->senha = senha;
    this->username = username;
    this->registro = registro;
}

void Mecanico::atendePedido(){

    this->registro->mostraPedAprovados();

    float mao_obra = 0.1; // 10% do valor da peça
    string msg_padrao = "O pedido foi atendido! "; // Resposta Padrão do Mecânico

    int id;
    cout << "Selecione o ID do pedido que deseja atender: ";
    cin >> id;

    Ordem* ordem_recebida = this->registro->getOrdemCliente(id);
    Cliente* cliente_ordem_recebida = this->registro->getCliente(ordem_recebida->getIdCliente()); //Retorna Ponteiro de Cliente para que mecânico acesse seu veiculo
    
    Veiculo* veiculo_cliente_ordem_recebida = cliente_ordem_recebida->getVeiculo(); //Veiculo do Cliente

    string pedido = ordem_recebida->getPed();

    string resposta;

    for (const auto &entry: reg_produtos2)
    {
        auto key_pair = entry.first;
            
        if (pedido.compare(key_pair.first) == 0)
        {
            if (pedido.compare("Alinhamento") == 0 || pedido.compare("Balanceamento") == 0)
            {
                ordem_recebida->setOrca(key_pair.second);

                string prod_preco = "Pedido Solicitado: " + key_pair.first + " | Orçamento Final: " +  to_string(key_pair.second) + "\n";

                resposta = msg_padrao + prod_preco;

                ordem_recebida->setRepMec(resposta);

                this->registro->setPedConcluidos(ordem_recebida);

                veiculo_cliente_ordem_recebida->addHistAjust(resposta);
                
            }

            else {

                float valor_com_peca = (key_pair.second * mao_obra) + key_pair.second;

                ordem_recebida->setOrca(valor_com_peca);

                string prod_preco = "Pedido Solicitado: " + key_pair.first + " | Orçamento Final: " +  to_string(valor_com_peca) + "\n";

                resposta = msg_padrao + prod_preco;

                ordem_recebida->setRepMec(resposta);

                this->registro->setPedConcluidos(ordem_recebida);

                veiculo_cliente_ordem_recebida->addHistAjust(resposta);

            }
                
        }
            
    }

}

void Mecanico::verPedidosConcluidos(){
    this->registro->mostraPedConcluidos();
}
