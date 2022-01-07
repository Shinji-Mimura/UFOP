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
public class RegOrdens {
    private ArrayList<Ordem> regOrdensNaoAprovadas;
    private ArrayList<Ordem> regOrdensAprovadas;
    public ArrayList<Ordem> regOrdensConcluidas;
    
    
    public StringBuilder showONA(){
        StringBuilder total = new StringBuilder();
        
        regOrdensNaoAprovadas.forEach(action -> {
            total.append("Pedido: ");
            total.append(action.getPedOrdem());
            total.append("ID do Cliente: ");
            total.append(action.getIdCliente());
            total.append(("\n"));
        });
        
        return total;
    }
    
    public StringBuilder showOA(){
        StringBuilder total = new StringBuilder();
        
        regOrdensAprovadas.forEach(action -> {
            total.append("Pedido: ");
            total.append(action.getPedOrdem());
            total.append("ID do Cliente: ");
            total.append(action.getIdCliente());
            total.append(("\n"));
        });
        
        return total;
    }
    
    public StringBuilder showOC(){
        StringBuilder total = new StringBuilder();
        
        regOrdensConcluidas.forEach(action -> {
            total.append("Pedido: ");
            total.append(action.getPedOrdem());
            total.append("ID do Cliente: ");
            total.append(action.getIdCliente());
            total.append(("\n"));
        });
        
        return total;
    }
    
    public void addOA(Ordem OA){
        regOrdensAprovadas.add(OA);
    }
    
    public void addOC(Ordem OC){
        regOrdensConcluidas.add(OC);
    }
    
    public void ConcluiOrdem(int idCliente){ //Mecanico entrega para o Al que o vendedor acessa
        
        for (int i = 0; i < regOrdensAprovadas.size(); i++) {
            if (regOrdensAprovadas.get(i).getIdCliente() == idCliente) {
                
                
                regOrdensAprovadas.get(i).setStatusConc(true);
                regOrdensConcluidas.add(regOrdensAprovadas.get(i));
                regOrdensAprovadas.remove(i);
                
            }
        }
        
    }
    
    public void setOrca(int idCliente, double orca){
        regOrdensAprovadas.forEach(action -> {
            if (action.getIdCliente() == idCliente) {
                action.setOrca(orca);
            }
        });
    }
    
    public void setRepMec(int idCliente, String RepMec){
        regOrdensAprovadas.forEach(action -> {
            if (action.getIdCliente() == idCliente) {
                action.setRepMec(RepMec);
            }
        });
    }
    
    public Ordem getOrdemNaoAprovada(int idOrdem){
 
        for (int i = 0; i < regOrdensNaoAprovadas.size(); i++) {
            if (regOrdensAprovadas.get(i).getIdCliente() == idOrdem) {
                return regOrdensAprovadas.remove(i);
            }
        }
        
        return null;
    }

    public Ordem getOrdemAprovadas(int idOrdem){
        
        
        for (int i = 0; i < regOrdensAprovadas.size(); i++) {
            if (regOrdensAprovadas.get(i).getIdCliente() == idOrdem) {
                return regOrdensAprovadas.remove(i);
            }
        }
        return null;
    }
    
    
}
