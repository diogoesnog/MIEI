/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package main;

import java.util.concurrent.locks.Condition;
import java.util.concurrent.locks.ReentrantLock;
import java.util.logging.Level;
import java.util.logging.Logger;

/**
 *
 * @author 
 */
public class Servidores {
    private Servidor[] servidores;              // Array com servidores para alugar e leiloar.
    private ReentrantLock lockServidores;       // Lock para o servidores
    private Condition occupied;                 // Condição para quando todos os servidores estiverem alugados
    private int counterA;                       // Nº de servidores alugados
    private int counterL;                       // Nº de servidores leiloados
    private int proxPos;                        // Próximo servidor a ser alugado

    
    public Servidores(int n){
        this.servidores = new Servidor[n];
        this.counterA = 0;
        this.counterL  = 0;
        this.proxPos = n-1;
        this.lockServidores = new ReentrantLock();
        this.occupied = this.lockServidores.newCondition();
    }
    
    
    // usada para povoar unicamente para povoar dai não ser um método protegido para concorrencia
    public void adicionaServidor(Servidor s){
        this.servidores[s.getId()] = s;
    }

    
    public int alugaServer(String tipoAluguer){
        this.lockServidores.lock();
        int id=-2;
        try{
            while(tipoAluguer.equals("aluguer") && ((this.counterA+this.counterL)==this.servidores.length)){
                this.occupied.await();
            }
            if (tipoAluguer.equals("leilao") && ((this.counterA+this.counterL)==this.servidores.length)) return -2;
          /*  if (tipoAluguer.equals("aluguer") &&(this.counterL > 0) && ((this.counterA+this.counterL)==this.servidores.length)){
                return -1;
            }*/
            searchPos();
            Servidor s = this.servidores[this.proxPos];
            id = s.getId();
            s.lock(tipoAluguer);
            
            if (tipoAluguer.equals("aluguer")){
                this.counterA++;
              // System.out.println("Thread: " +Thread.currentThread().getName()+" ALUGA server "+s.getId());
              // System.out.println("Nº de Alugados "+this.counterA);
                
            }
            else {
                this.counterL++;
             //   System.out.println("Thread: " +Thread.currentThread().getName()+" LEILOA server "+s.getId());
             //   System.out.println("Nº de Leiloados "+this.counterL);
            }
            return id;
        } catch (InterruptedException ex) {
           Logger.getLogger(ServerWorker.class.getName()).log(Level.SEVERE, null, ex);
        } finally{
            this.lockServidores.unlock();
        }
        return id;
    }
    
    public void libertaServidor(int i,String tipoAluguer){
        this.lockServidores.lock();
        try {
            Servidor s = this.servidores[i];
            if(tipoAluguer.equals("aluguer")){
                this.counterA--;
               // System.out.println("Counter Alugados "+this.counterA);
            }
            else {
                this.counterL--;
               // System.out.println("Counter Leiloados "+this.counterL);
            }
            s.unlock();
            //System.out.println("Thread: " +Thread.currentThread().getName()+" LIBERTA server "+s.getId());
            
            this.proxPos = i;
            this.occupied.signalAll();
        } finally {
            this.lockServidores.unlock();
        }
    }
    
    
    public synchronized Servidor getServidor(int id){
        if (id>=0 && id<this.servidores.length) return this.servidores[id];
        else return null;
    }
    
    

    public synchronized boolean searchPos(){    
        boolean flag = false;
        if(!(this.servidores[this.proxPos].isLocked())) flag = true;
        int i =0;
        while(i<this.servidores.length && !flag){
            if(!(this.servidores[this.proxPos].isLocked())) flag = true;
            else if (this.proxPos==0) this.proxPos = this.servidores.length-1 ;
            else this.proxPos--;
            i++;
        }
        return flag;
    }
    
    public void cancelaLeilao(){
       boolean flag = searchLeiloados();
       libertaServidor(this.proxPos,"leilao");
    }
    
    public synchronized boolean searchLeiloados(){
        int i;
        boolean flag = false;
        int pos=-1;
        for(i=0;i<this.servidores.length && !flag ;i++){
            if(this.servidores[this.proxPos].getTipoAluguer().equals("leilao")) flag = true;
            else if(this.proxPos==0) this.proxPos = this.servidores.length-1 ;
            else this.proxPos--;
        }
        return flag;
    }
    
    @Override
    public String toString(){
        StringBuilder s = new StringBuilder("##Servidores###\n");
        
        for(Servidor s1 : this.servidores){
            s.append(s1+"\n");
        }
        return s.toString();
    }
}
