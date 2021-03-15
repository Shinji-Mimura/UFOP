/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package tpjava;

/**
 *
 * @author nicolas
 */
public class Vendedor extends Funcionario{

    public Vendedor(int id, String nome, String username, String senha) {
        super(id, nome, username, senha);
    }
    
    public RegOrdens regOrdens;
    public RegClientes regClientes;
    
    public Ordem cadastraOrdem(int indexPedido){
        return new Ordem(indexPedido);
    }
    
    public Veiculo cadastraVeiculo(String placa, double quilometragem){
        return new Veiculo(placa, quilometragem);
    }
    
    public void cadastraCliente(String nome, double CPF, Ordem ordem, Veiculo veiculo){
        Cliente novoCliente = new Cliente(nome, CPF, ordem, veiculo);
        novoCliente.setId(regClientes.totalClientes());
        novoCliente.getOrdemServico().setIdCliente(novoCliente.getId());
        regClientes.addCliente(novoCliente);
    }
    
    public void clienteJaCad(Cliente cliente, Ordem ordem){
        cliente.setOrdemServico(ordem);
    }
    

    public void ListaOrdensNaoAprovadas(){
        System.out.println(regOrdens.showONA());
    }
    
    public boolean aprovarOrdem(int idOrdem){
        Ordem aprovada = regOrdens.getOrdemNaoAprovada(idOrdem);
        
        if (aprovada != null) {
        aprovada.setStatusAprov(true);
        regOrdens.addOA(aprovada);  
        return true;
        }
        
        else {
            return false;
        }
    }
    
    public boolean entregaOrdem(int idCliente){

        int tam = regOrdens.regOrdensConcluidas.size();
        for (int i = 0; i < tam; i++) {
            if (regOrdens.regOrdensConcluidas.get(i).getIdCliente() == idCliente) {
                
                Cliente cliente = regClientes.getCliente(idCliente);
                setRepMecOnVeiculo(regOrdens.regOrdensConcluidas.get(i).getRepMec(), cliente);
                cliente.setOrdemServico(regOrdens.regOrdensConcluidas.get(i));
                regOrdens.regOrdensConcluidas.remove(i);
                System.out.println("Ordem Entregue ao Cliente");
                return true;
                
            }
            
        }
        
        return false;
    }
    
    public void displayOrdensConcluidas(){
        System.out.println(regOrdens.showOC());
    }

    public void setRepMecOnVeiculo(String RepMec, Cliente cliente){
        cliente.getVeiculoCliente().addHistorico(RepMec);
    }
}
