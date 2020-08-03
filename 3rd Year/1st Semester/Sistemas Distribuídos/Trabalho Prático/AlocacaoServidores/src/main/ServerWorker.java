package main;

import java.io.IOException;
import java.io.ObjectInputStream;
import java.io.ObjectOutputStream;
import java.io.Serializable;
import java.net.Socket;
import java.util.logging.Level;
import java.util.logging.Logger;



public class ServerWorker implements Runnable,Serializable {
    private Socket socket;
    private ObjectInputStream in;
    private ObjectOutputStream out;
    private Users users;
    private Servidores large;
    private Servidores normal;
    private Servidores micro;
    private Leilao leilaoLarge;
    private Leilao leilaoNormal;
    private Leilao leilaoMicro;

    
    
    public ServerWorker(Socket socket,Users users,Servidores large,Servidores normal, Servidores micro,Leilao lLarge,Leilao lNormal,Leilao lMicro){
        try {
            this.users = users;
            this.large = large;
            this.normal = normal;
            this.micro = micro;
            this.leilaoLarge = lLarge;
            this.leilaoNormal = lNormal;
            this.leilaoMicro = lMicro;
            this.socket = socket;
            this.in = new ObjectInputStream(this.socket.getInputStream());
            this.out = new ObjectOutputStream(this.socket.getOutputStream());
        } catch (IOException ex) {
            Logger.getLogger(ServerWorker.class.getName()).log(Level.SEVERE, null, ex);
        }       
    }
       
    public void close(){
        try {
            this.socket.shutdownInput();
            this.socket.shutdownOutput();
            this.socket.close();
        } catch (IOException ex) {
            Logger.getLogger(ServerWorker.class.getName()).log(Level.SEVERE, null, ex);
        }
    }
    
    public synchronized void addUser(String mail,String pass){
        this.users.addUser(mail, pass);
    }
    

    public void registar(){
        try {
            String mail = (String) in.readObject();
            boolean flag = this.users.userExists(mail);
            
            out.writeObject(flag);

            while(flag){
                mail = (String) in.readObject();
                flag = this.users.userExists(mail);
                out.writeObject(flag);
            }
            String pass = (String) in.readObject();
            addUser(mail,pass);
            this.out.flush();
        } catch (IOException | ClassNotFoundException ex) {
            Logger.getLogger(ServerWorker.class.getName()).log(Level.SEVERE, null, ex);
        }
    }
    
  

    public void login(){
        try {
            String name = (String) this.in.readObject();
            String pass = (String) this.in.readObject();
            
            boolean flag = this.users.autentification(pass,name);

            this.out.writeObject(flag);

            while(!flag){
                name = (String) this.in.readObject();
                pass = (String) this.in.readObject();
                flag = this.users.autentification(pass,name);
                this.out.writeObject(flag);
                System.out.println(flag);
            }
            this.out.flush();
        } catch (IOException | ClassNotFoundException ex) {
            Logger.getLogger(ServerWorker.class.getName()).log(Level.SEVERE, null, ex);
        }
    }
 
    
    public void depositar(){
        try {
            Double custo = (Double) this.in.readObject();
            String mail = (String) this.in.readObject();
            this.users.depositaConta(mail, custo);
        } catch (IOException | ClassNotFoundException ex) {
            Logger.getLogger(ServerWorker.class.getName()).log(Level.SEVERE, null, ex);
        }
    }
    
    public void consultar(){
        try {
            String mail = (String) in.readObject();
            double custo = this.users.getSaldo(mail);
            try {
                this.out.writeObject(custo);
                this.out.flush();
            } catch (IOException ex) {
                System.err.println("Erro método consultar, classe ServerWorker " + ex.getMessage());
            }
        } catch (IOException | ClassNotFoundException ex) {
            Logger.getLogger(ServerWorker.class.getName()).log(Level.SEVERE, null, ex);
        }
    }
    
    public void aluguer(String server){
       int id=0;
       double custo = 0;
       if (server.equals("large")){
           custo = 1;
           id = this.large.alugaServer("aluguer");
       }
       else if (server.equals("normal")){
           custo = 0.9;
           id = this.normal.alugaServer("aluguer");
       }
       else {
           custo = 0.75;
           id = this.micro.alugaServer("aluguer");
       }
        try {
            double custoTotal = 0;
            this.out.writeObject(server);
            this.out.writeObject(custo);
            String value ="ok";
            while(!value.equals("2")){
                // Supondo que é 1h
                Thread.sleep(3600);
                custoTotal+=custo;
                this.out.writeObject("");
                value = (String) this.in.readObject();
            }
            this.out.writeObject(custoTotal);
            String mail = (String) this.in.readObject();
            this.users.retiraConta(mail, custoTotal);
            if (server.equals("large")) this.large.libertaServidor(id,"aluguer");
            else if (server.equals("normal")) this.normal.libertaServidor(id,"aluguer");
            else this.micro.libertaServidor(id,"aluguer");
            this.out.flush();
        } catch (IOException | InterruptedException | ClassNotFoundException ex) {
            Logger.getLogger(ServerWorker.class.getName()).log(Level.SEVERE, null, ex);
        }
    }
    
    public void secondMenu(){
         try {
            String value ="ok";
            while(!(value.equals("6"))){
                value =(String) in.readObject();
                switch(value){
                    case "1":
                        menuAluguer();
                        break;
                    case "2":
                        menuLeilao();
                        break;
                    case "3":
                        depositar();
                        break;
                    case "4":
                        consultar();
                        break;
                    case "5":
                        String mail = (String) in.readObject();
                        this.users.setAtivo(mail,false);
                        value = "6";
                }
            }  
        } catch (IOException | ClassNotFoundException ex) {
            Logger.getLogger(ServerWorker.class.getName()).log(Level.SEVERE, null, ex);
        }
    }
       
    public void menuAluguer(){
        try {
            String value ="ok";
            while(!(value.equals("4"))){
                value =(String) in.readObject();
                switch(value){
                    case  "1":
                        aluguer("large");
                        break;
                    case "2":
                        aluguer("normal");
                        break;
                    case "3":
                        aluguer("micro");
                        break;
                }
            }     
        } catch (IOException | ClassNotFoundException ex) {
            Logger.getLogger(ServerWorker.class.getName()).log(Level.SEVERE, null, ex);
        }
    }
    
   
   
    public void leilaoLarge(){
        int id = 0;
        int alugou = -3;
        try {
            synchronized(this){
                if (this.leilaoLarge.getTerminado()){
                    id = this.large.alugaServer("leilao");
                    if(id!=-2) {
                        this.leilaoLarge.setTerminado(false);
                        Temporizador t = new Temporizador(this.leilaoLarge);
                        t.start();
                    }
                }
            }
            if (id==-2) this.out.writeObject(true);
            else {
                this.out.writeObject(false);
                String mail = (String) this.in.readObject();
                
                this.leilaoLarge.addUser(mail, out);
                // enviei msg
                this.leilaoLarge.sendingMessage("User entrou no leilao", mail,false,false);
           
                String value = "ok";
                boolean flag = this.leilaoLarge.getTerminado();
                
                while(!value.equals("quit") && !flag ){
                    flag = this.leilaoLarge.getTerminado();
                    value = (String) this.in.readObject();
                    if (!value.equals("quit")&& !flag){    
                        this.leilaoLarge.sendingMessage(value, mail,true,false);
                    }
                }
                
                mail = (String) in.readObject();
                boolean winner = this.leilaoLarge.isWinner(mail);
                double custoLeilao = this.leilaoLarge.getCusto();
                this.leilaoLarge.removeUser(mail);
                this.out.writeObject(winner);
                if (winner){
                    double custoTotal = 0;
                    this.out.writeObject("large");
                    this.out.writeObject(custoLeilao);
                    String valor ="ok";
                    while(!valor.equals("2")){
                        // Supondo que é 1h
                        Thread.sleep(3600);
                        custoTotal+=custoLeilao;
                        this.out.writeObject("");
                        valor = (String) this.in.readObject();
                    }
                    this.out.writeObject(custoTotal);
                    mail = (String) this.in.readObject();
                    this.users.retiraConta(mail, custoTotal);
                    this.large.libertaServidor(id, "leilao");
                   }
                this.out.flush();
            }
        } catch (IOException | ClassNotFoundException | InterruptedException ex) {
            Logger.getLogger(ServerWorker.class.getName()).log(Level.SEVERE, null, ex);
        }
    }
    
    public void leilaoNormal(){
        int id = 0;
        int alugou = -3;
        try {
            synchronized(this){
                if (this.leilaoNormal.getTerminado()){
                    id = this.normal.alugaServer("leilao");
                    if(id!=-2) {
                        this.leilaoNormal.setTerminado(false);
                        Temporizador t = new Temporizador(this.leilaoNormal);
                        t.start();
                    }
                }
            }
            if (id==-2) this.out.writeObject(true);
            else {
                this.out.writeObject(false);
                String mail = (String) this.in.readObject();
                
                this.leilaoNormal.addUser(mail, out);
                // enviei msg
                this.leilaoNormal.sendingMessage("User entrou no leilao", mail,false,false);
           
                String value = "ok";
                boolean flag = this.leilaoNormal.getTerminado();
                
                while(!value.equals("quit") && !flag ){
                    flag = this.leilaoNormal.getTerminado();
                    value = (String) this.in.readObject();
                    if (!value.equals("quit")&& !flag){    
                        this.leilaoNormal.sendingMessage(value, mail,true,false);
                    }
                }
                
                mail = (String) in.readObject();
                boolean winner = this.leilaoNormal.isWinner(mail);
                double custoLeilao = this.leilaoNormal.getCusto();
                this.leilaoNormal.removeUser(mail);
                this.out.writeObject(winner);
                if (winner){
                    double custoTotal = 0;
                    this.out.writeObject("normal");
                    this.out.writeObject(custoLeilao);
                    String valor ="ok";
                    while(!valor.equals("2")){
                        // Supondo que é 1h
                        Thread.sleep(3600);
                        custoTotal+=custoLeilao;
                        this.out.writeObject("");
                        valor = (String) this.in.readObject();
                    }
                    this.out.writeObject(custoTotal);
                    mail = (String) this.in.readObject();
                    this.users.retiraConta(mail, custoTotal);
                    this.normal.libertaServidor(id, "leilao");
                }
                this.out.flush();
            }
        } catch (IOException | ClassNotFoundException | InterruptedException ex) {
            Logger.getLogger(ServerWorker.class.getName()).log(Level.SEVERE, null, ex);
        }
    }
    
    
     public void leilaoMicro(){
        int id = 0;
        int alugou = -3;
        try {
            synchronized(this){
                if (this.leilaoMicro.getTerminado()){
                    id = this.micro.alugaServer("leilao");
                    if(id!=-2) {
                        this.leilaoMicro.setTerminado(false);
                        Temporizador t = new Temporizador(this.leilaoMicro);
                        t.start();
                    }
                }
            }
            if (id==-2) this.out.writeObject(true);
            else {
                this.out.writeObject(false);
                String mail = (String) this.in.readObject();
                
                this.leilaoMicro.addUser(mail, out);
                // enviei msg
                this.leilaoMicro.sendingMessage("User entrou no leilao", mail,false,false);
           
                String value = "ok";
                boolean flag = this.leilaoMicro.getTerminado();
                
                while(!value.equals("quit") && !flag ){
                    flag = this.leilaoMicro.getTerminado();
                    value = (String) this.in.readObject();
                    if (!value.equals("quit")&& !flag){    
                        this.leilaoMicro.sendingMessage(value, mail,true,false);
                    }
                }
                
                mail = (String) in.readObject();
                boolean winner = this.leilaoMicro.isWinner(mail);
                double custoLeilao = this.leilaoMicro.getCusto();
                this.leilaoMicro.removeUser(mail);
                this.out.writeObject(winner);
                if (winner){
                    this.out.writeObject("micro");
                    double custoTotal = 0;
                    this.out.writeObject(custoLeilao);
                    String valor ="ok";
                    while(!valor.equals("2")){
                        // Supondo que é 1h
                        Thread.sleep(3600);
                        custoTotal+=custoLeilao;
                        this.out.writeObject("");
                        valor = (String) this.in.readObject();
                    }
                    this.out.writeObject(custoTotal);
                    mail = (String) this.in.readObject();
                    this.users.retiraConta(mail, custoTotal);
                    this.micro.libertaServidor(id, "leilao");
                }
                this.out.flush();
            }
        } catch (IOException | ClassNotFoundException | InterruptedException ex) {
            Logger.getLogger(ServerWorker.class.getName()).log(Level.SEVERE, null, ex);
        }
    }
    
    
    public void menuLeilao(){
        try {
            String value ="ok";
            while(!(value.equals("4"))){
                value =(String) in.readObject();
                switch(value){
                    case "1":
                        leilaoLarge();
                        break;
                    case "2":
                        leilaoNormal();
                        break;
                    case "3":
                        leilaoMicro();
                        break;
                }
            }     
        } catch (IOException | ClassNotFoundException ex) {
            Logger.getLogger(ServerWorker.class.getName()).log(Level.SEVERE, null, ex);
        }
    }
    
    
    @Override
    public void run() {
        try {
            String value ="ok";
            while(!(value.equals("3"))){
                value =(String) in.readObject();
                switch(value){
                    case "1":
                        registar();
                        secondMenu();
                        break;
                    case "2":
                        login();
                        secondMenu();
                        break;
                }
            }
            close();           
        } catch (IOException | ClassNotFoundException ex) {
            Logger.getLogger(ServerWorker.class.getName()).log(Level.SEVERE, null, ex);
        }
    }   
}
