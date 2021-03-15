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
public class Ordem {
    private String PedOrdem; //V
    private String RepMec; //M
    private boolean statusAprov; //V
    private boolean statusConc; //M
    private double orca; //M
    private int idCliente; //V
    private int idPedido;
    private Pedido ListaPedidos;

    public Ordem(int indexPedido) {
        this.PedOrdem = ListaPedidos.getNomeProduto(indexPedido);
        this.idPedido = indexPedido;
        this.statusAprov = false;
        this.statusConc = false;
    }

    public String getPedOrdem() {
        return PedOrdem;
    }

    public void setPedOrdem(String PedOrdem) {
        this.PedOrdem = PedOrdem;
    }

    public String getRepMec() {
        return RepMec;
    }

    public void setRepMec(String RepMec) {
        this.RepMec = RepMec;
    }

    public boolean isStatusAprov() {
        return statusAprov;
    }

    public void setStatusAprov(boolean statusAprov) {
        this.statusAprov = statusAprov;
    }

    public boolean isStatusConc() {
        return statusConc;
    }

    public void setStatusConc(boolean statusConc) {
        this.statusConc = statusConc;
    }

    public double getOrca() {
        return orca;
    }

    public void setOrca(double orca) {
        this.orca = orca;
    }

    public int getIdCliente() {
        return idCliente;
    }

    public void setIdCliente(int idCliente) {
        this.idCliente = idCliente;
    }
    
    public int getIdPedido(){
        return this.idPedido;
    }
    
}
