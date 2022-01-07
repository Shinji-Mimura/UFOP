/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package tpjava;
import java.util.ArrayList;

/**
 *
 * @author nicolas
 */
public class RegClientes {
    private ArrayList<Cliente> regClientes;
    
    public StringBuilder showClientes(){
        StringBuilder total = new StringBuilder();
        
        regClientes.forEach((_item)-> {
            total.append("Nome: ");
            total.append(_item.getNome());
            total.append("ID: ");
            total.append(_item.getId());
            total.append("CPF: ");
            total.append(_item.getCPF());
            total.append("\n");
            total.append("Veiculo Do Cliente");
            total.append("\n");
            total.append("Placa: ");
            total.append(_item.getVeiculoCliente().getPlaca());
            total.append("Quilometragem: ");
            total.append(_item.getVeiculoCliente().getQuilometragem());
            total.append("\n");
            total.append("Ordem do Cliente");
            total.append("\n");
            total.append("Pedido: ");
            total.append(_item.getOrdemServico().getPedOrdem());
            total.append("\n");
            total.append("------------------------------------------");
            total.append("\n");
        });
        
        return total;
    }
    
    public void addCliente(Cliente clienteNovo){
        regClientes.add(clienteNovo);
    }
    
    public Cliente getCliente(int id){

        for(Cliente cliente: regClientes){
            if (cliente.getId() == id) {
                return cliente;
            }
        }
        return null;
    }
    
    public int totalClientes(){
        return regClientes.size();
    }
    
}

    
