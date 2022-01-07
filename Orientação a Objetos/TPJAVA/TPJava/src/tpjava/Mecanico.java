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
public class Mecanico extends Funcionario{
    
    public RegOrdens regOrdens;
    public Pedido listaPedidos;
    
    public Mecanico(int id, String nome, String username, String senha) {
        super(id, nome, username, senha);
    }
    
    
    public boolean ConcluirPedido(int idOrdem){
        Ordem concluida = regOrdens.getOrdemAprovadas(idOrdem);
        if (concluida != null) {
            concluida.setOrca(valorFinalOrca(concluida.getIdPedido()));
            concluida.setRepMec(listaPedidos.getNomeProduto(concluida.getIdPedido()));
            concluida.setStatusConc(true);
            regOrdens.addOC(concluida);
            return true;
        }
        
        else {
            return false;
        }
    }
    
    public double valorFinalOrca(int idPedido){
        if (idPedido == 0 || idPedido == 1) {
            return listaPedidos.getValorProduto(idPedido);
        }
        
        else {
            double resultado = (listaPedidos.getValorProduto(idPedido) * 0.10)  + listaPedidos.getValorProduto(idPedido);
            return resultado;
        }
    }
    
}
