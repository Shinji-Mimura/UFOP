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
public class Veiculo {
    private String placa;
    private double quilometragem;
    private ArrayList<String> historicoAjuste;

    public Veiculo(String placa, double quilometragem) {
        this.placa = placa;
        this.quilometragem = quilometragem;
    }

    public String getPlaca() {
        return placa;
    }

    public void setPlaca(String placa) {
        this.placa = placa;
    }

    public double getQuilometragem() {
        return quilometragem;
    }

    public void setQuilometragem(double quilometragem) {
        this.quilometragem = quilometragem;
    }

    public void addHistorico(String historico){
        this.historicoAjuste.add(historico);
    }
    
    public void getHistorico(int index){
        this.historicoAjuste.get(index);
    }
    
    public void showHistorico(){
        historicoAjuste.forEach((_item) -> {
            System.out.println("Resposta do Mecânico: " + _item);
        });
    }
    
}
