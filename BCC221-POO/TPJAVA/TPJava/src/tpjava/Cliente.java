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
public class Cliente {
    private String nome;
    private final double  CPF;
    private int idCliente;
    private Ordem ordemServico;
    private Veiculo veiculoCliente;

    public Cliente(String nome, double CPF, Ordem ordemServico, Veiculo veiculoCliente) {
        this.nome = nome;
        this.CPF = CPF;
        this.ordemServico = ordemServico;
        this.veiculoCliente = veiculoCliente;
    }



    public String getNome() {
        return nome;
    }

    public void setNome(String nome) {
        this.nome = nome;
    }

    public Ordem getOrdemServico() {
        return ordemServico;
    }

    public void setOrdemServico(Ordem ordemServico) {
        this.ordemServico = ordemServico;
    }

    public Veiculo getVeiculoCliente() {
        return veiculoCliente;
    }

    public void setVeiculoCliente(Veiculo veiculoCliente) {
        this.veiculoCliente = veiculoCliente;
    }
    
    public int getId(){
        return this.idCliente;
    }
    
    public void setId(int id){
        this.idCliente = id;
    }
    
    public double getCPF(){
        return this.CPF;
    }
    
    
}
