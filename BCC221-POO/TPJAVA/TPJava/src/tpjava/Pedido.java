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
public class Pedido {
    private String[] NomeProduto = {"Alinhamento", "Balanceamento", "Motor", "Pneu", "Carburador", "Retrovisor", "Freio"};
    private double[] ValorProduto = {100, 250, 300, 450.80, 600.90, 15.80, 11.35};
    
    public String getNomeProduto(int index){
        return NomeProduto[index];
    }
    
    public double  getValorProduto(int index){
        return ValorProduto[index];
    }
    
}

    