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
public class Admin extends Funcionario{
    
    private ArrayList<Vendedor> reg_vendedores;
    private ArrayList<Mecanico> reg_mecanicos;
    

    public Admin(int id, String nome, String username, String senha) {
        super(id, nome, username, senha);
    }
    
    
    public void addMec(Mecanico mec){
        reg_mecanicos.add(mec);
    }
    
    public void addVend(Vendedor vend){
        reg_vendedores.add(vend);
    }
    
    public void showMecs(){
        reg_mecanicos.forEach((_item) -> {
            System.out.println("--------------------------");
            System.out.println("Nome: " + _item.getNome());
            System.out.println("ID: " + _item.getId());
    });
    }
    
    public void showVends(){
        reg_vendedores.forEach((_item) -> {
            System.out.println("--------------------------");
            System.out.println("Nome: " + _item.getNome());
            System.out.println("ID: " + _item.getId());
        });
    }
    
    
    public Mecanico getMec(int idMec){

        for (int i = 0; i < reg_mecanicos.size(); i++) {
            if (reg_mecanicos.get(i).getId() == idMec) {
                return reg_mecanicos.get(i);
            }
        }
        return null;

    }
    
    public Vendedor getVend(int idVend){
        
        for (int i = 0; i < reg_vendedores.size(); i++) {
            if (reg_vendedores.get(i).getId() == idVend) {
                return reg_vendedores.get(i);
            }
        }
        return null;
    }
   
    public void setSenhaMec(int id, String novaSenha){
        
        Mecanico mec = getMec(id);
        
        if (mec != null) {
            mec.setSenha(novaSenha);
        }
        
        else {
            System.out.println("Mecânico Não Existente! Operação Falhou");
        }
        
    }
    
    public void setSenhaVend(int id, String novaSenha){
        
        Vendedor vend = getVend(id);
        
        if (vend != null) {
        vend.setSenha(novaSenha);
        }
        
        else {
            System.out.println("Vendedor Não Existente! Operação Falhou");
        }
        
    }
    
    public void setNomeMec(int id, String Nome){
        
        Mecanico mec = getMec(id);
        
        if (mec != null) {
            mec.setNome(Nome);
        }
        
        else {
            System.out.println("Mecânico Não Existente! Operação Falhou");
        }
        
    }
    
    public void setNomeVend(int id, String Nome){

        Vendedor vend = getVend(id);
        
        if (vend != null) {
            vend.setNome(Nome);
        }
        
        else {
            System.out.println("Vendedor Não Existente! Operação Falhou");
        }        
        
    }
    
    public void setUsernameMec(int id, String Username){

        Mecanico mec = getMec(id);
        
        if (mec != null) {
            mec.setUsername(Username);
        }
        
        else {
            System.out.println("Mecânico Não Existente! Operação Falhou");
        }       
  
    }
    
    public void setUsernameVend(int id, String Username){

        Vendedor vend = getVend(id);
        
        if (vend != null) {
            vend.setUsername(Username);
        }
        
        else {
            System.out.println("Vendedor Não Existente! Operação Falhou");
        }        
        
    }
    
}
