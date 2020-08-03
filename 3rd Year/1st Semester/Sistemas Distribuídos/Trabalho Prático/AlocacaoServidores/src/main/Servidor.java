package main;

import java.io.Serializable;


public class Servidor implements Serializable {
   
    private String nome;
    private String tipoAluguer;
    private double custoHora;
    private int id;
    private boolean lock;
    private boolean cancelado;
    

    public Servidor() {
        this.nome="";
        this.custoHora=0;
        this.id =0;
        this.lock = false;
        this.cancelado = false;
    }
    
    public Servidor(String nome, double custoHora,int id){
        this.lock = false;
        this.nome = nome;
        this.custoHora= custoHora;
        this.id = id;
        this.tipoAluguer="";
    }
    
    public String getTipoAluguer(){
        return this.tipoAluguer;
    }
    
    public String getName() {
        return this.nome;
    }
    
    public double getCusto(){
        return this.custoHora;
    }
    
    public int getId(){
        return this.id;
    }
    
    public void setId(int i){
        this.id=i;
    }
    
    public void setTipoAluguer(String tipo){
        this.tipoAluguer=tipo;
    }
    
    public void lock(String tipo){
        this.tipoAluguer = tipo;
        this.lock = true;
    }
    
   public void unlock(){
        this.tipoAluguer ="";
        this.lock = false;
    }
   
    public boolean isLocked(){
        return (this.lock);
    }
    
    public void cancelaServer(){
        this.cancelado = true;
    }
    
    public void setCancelado(boolean cancelado){
        this.cancelado = cancelado;
    }
    
    public boolean getCancelado(){
        return this.cancelado;
    }
    
    public String toString(){
        StringBuilder s = new StringBuilder("### SERVIDOR ###\n");
        s.append("Nome: " +this.nome+"\n");
        s.append("Custo por hora: " +this.custoHora+"€\n");
        s.append("Id: " +this.id+"\n");
        if(this.isLocked()) s.append("Locked\n");
        else s.append("Unlocked\n");
        return s.toString();
    }
}
