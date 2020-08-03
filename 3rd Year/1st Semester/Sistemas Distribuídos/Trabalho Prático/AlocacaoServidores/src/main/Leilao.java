/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package main;

import java.io.IOException;
import java.io.ObjectOutputStream;
import java.io.Serializable;
import java.util.HashMap;
import java.util.logging.Level;
import java.util.logging.Logger;

/**
 *
 * @author SarahTifanySilva
 */
public class Leilao implements Serializable {
    private HashMap<String,ObjectOutputStream> usersWriters;
    private Servidor servidor;
    private String mailUser;
    private double custoMaior;
    private boolean terminado;              //Se for true posso comecar um novo leilao! Inicio timer


    
    public Leilao(){
        this.custoMaior = 0;
        this.mailUser ="";
        this.usersWriters = new HashMap<>();
        this.terminado = true;
        this.servidor = null;
    }
    
    public synchronized void setTerminado(boolean flag){
        this.terminado=flag;
    }
    
    public synchronized void setServidor(Servidor s){
        this.servidor = s;
    }
    
    public synchronized Servidor getIdServer(){
        return this.servidor;
    }
    
    public synchronized boolean getTerminado(){
        return this.terminado;
    }  
       
    public synchronized boolean getCanceladoServer(){
        return this.servidor.getCancelado();
    }
    public synchronized void addUser(String mail, ObjectOutputStream out){
        this.usersWriters.put(mail,out);
    }
    

    public synchronized void removeUser(String mail){
        this.usersWriters.remove(mail);
        if (this.usersWriters.isEmpty()){
            this.terminado = true;
        }
    }
    
    public synchronized boolean isWinner(String mail){
        return this.mailUser.equals(mail);
    }
    
    public double getCusto(){
        return this.custoMaior;
    }
    
    /**
     * Eniva mensagens de texto para todos os users da rede
     * @param value 
     */
    public synchronized void multicastWinner(){
        String value = "Parabéns! Conseguiu alugar o servidor por "+this.custoMaior+"€/hora\nDigite quit";
	try {
            ObjectOutputStream bw = this.usersWriters.get(mailUser);
            bw.writeObject(value);
            bw.writeObject(false);
            bw.flush();
        } catch (IOException e) {
            Logger.getLogger(Leilao.class.getName()).log(Level.SEVERE, null, e);  
        }
    }   
    
    public synchronized void sendingMessage(String value,String mail,boolean flag,boolean flagTerminado){
        ObjectOutputStream bw;
        if (flag){
            double custoU = Double.parseDouble(value);
            if(custoU>this.custoMaior){
                this.custoMaior = custoU;
                this.mailUser = mail;
            }
        }
        try {
            for(String user : this.usersWriters.keySet()) {
                if(!user.equals(mail)){
                    bw = this.usersWriters.get(user);
                    bw.writeObject(value);
                    bw.writeObject(flagTerminado);
                    bw.flush();
                }
            }
        } catch (IOException ex) {
            Logger.getLogger(Leilao.class.getName()).log(Level.SEVERE, null, ex);   
        }
    }
    
    public synchronized void sendingMessage2(String value,boolean flagTerminado){
        ObjectOutputStream bw;

        try {
            for(String user : this.usersWriters.keySet()) {

                    bw = this.usersWriters.get(user);
                    bw.writeObject(value);
                    bw.writeObject(flagTerminado);
                    bw.flush();
            }
        } catch (IOException ex) {
            Logger.getLogger(Leilao.class.getName()).log(Level.SEVERE, null, ex);   
        }
    }      
    
       
    public void terminaLeilao(){
        if(!(this.usersWriters.isEmpty())){
            multicastWinner();
            this.sendingMessage("Leilão terminado! Não conseguiu alugar o servidor\nDigite quit!", mailUser, false,false);
            this.sendingMessage2("quit",true);
        }
    }
    
    public String toString(){
        StringBuilder s = new StringBuilder("### LEILAO ###\n");
        s.append("Custo maior "+this.custoMaior+"\n");
        s.append("Mail do user "+this.mailUser+"\n");
        s.append("Terminado ?"+this.terminado+"\n");
        if (this.usersWriters.isEmpty()) s.append("Está vazio\n");
        else s.append("Está cheio!");
        return s.toString();
    }
}
