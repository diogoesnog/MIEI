package main;

import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.io.ObjectInputStream;
import java.io.ObjectOutputStream;
import java.io.Serializable;
import java.net.Socket;
import java.net.SocketException;
import java.util.logging.Level;
import java.util.logging.Logger;
import static main.Menus.*;


public class Client implements Serializable{
    private Thread listener;
    private Socket socket;
    private final String hostname;
    private final int porto;
    private ObjectInputStream in;
    private ObjectOutputStream out;
    private BufferedReader systemIn;
    private User user;


    
    public Client(String hostname,int porto){
        this.hostname = hostname;
        this.porto = porto;
    }
    
    public void inicializing(){
        try {
            this.user = new User();
            this.socket = new Socket(this.hostname,this.porto);
            this.out = new ObjectOutputStream(socket.getOutputStream());
            this.in = new ObjectInputStream(socket.getInputStream());
            this.systemIn = new BufferedReader(new InputStreamReader(System.in));
        } catch (IOException ex) {
            Logger.getLogger(Client.class.getName()).log(Level.SEVERE, null, ex);
        }
    }
    
   


    public void registar(){
        try {
            System.out.println("### SIGN_IN ###");
            System.out.print("Insira o seu mail\n> ");
            
            String mail = this.systemIn.readLine();
            
            this.out.writeObject(mail);
            
            boolean flag = (Boolean) in.readObject();
            
            while(flag){
                System.out.print("O user com mail " +mail+ " já existe! Insira outro mail\n> ");
                mail = this.systemIn.readLine();
                out.writeObject(mail);
                flag =(Boolean) in.readObject();
            }
            System.out.print("Insira password\n> ");
            String pass = this.systemIn.readLine();
            out.writeObject(pass);
            this.user = new User(mail,pass,0);
            System.out.println("### User inserido com sucesso ###");
            this.out.flush();
        } catch (IOException| ClassNotFoundException ex) {
            Logger.getLogger(Client.class.getName()).log(Level.SEVERE, null, ex);
        }
    }
    

    public void login(){
        try {
            System.out.println("### LOGIN ###");
           
            System.out.print("Mail :\n> ");
            String name = this.systemIn.readLine();
            this.out.writeObject(name);
            
            System.out.print("Password:\n> ");
            String pass = this.systemIn.readLine();
            this.out.writeObject(pass);
            
            boolean flag = (Boolean) this.in.readObject();

            while(!flag){
                System.out.println("Credenciais de acesso erradas ou User já fez login\nTente novamente");
                System.out.print("Mail:\n> ");
                name = this.systemIn.readLine();
                this.out.writeObject(name);
                System.out.print("Password:\n> ");
                pass = this.systemIn.readLine();
                this.out.writeObject(pass);
                flag = (Boolean) this.in.readObject();
            }
            if (flag) System.out.println("Login efetuado com sucesso!");
            else System.out.println("Login não efetuado com sucesso");
            this.out.flush();
        } catch (IOException | ClassNotFoundException ex) {
            Logger.getLogger(Client.class.getName()).log(Level.SEVERE, null, ex);
        }             
    }
    
    public void depositar(){
        try {
            System.out.print("Valor a depositar : ");
            String value = this.systemIn.readLine();
            double valor = Double.parseDouble(value);
            this.out.writeObject(valor);
            String mail = this.user.getMail();
            this.out.writeObject(mail);
            this.user.depositaSaldo(valor);
            System.out.println("Saldo depositado com sucesso!");
            this.out.flush();
        } catch (IOException ex) {
            Logger.getLogger(Client.class.getName()).log(Level.SEVERE, null, ex);
        }
    }
    
    public void consultar(){
        try {
            String mail = this.user.getMail();
            this.out.writeObject(mail);
            double custo = (Double) this.in.readObject();
            System.out.println("Saldo atual "+custo+"€");
        } catch (IOException | ClassNotFoundException ex) {
            Logger.getLogger(Client.class.getName()).log(Level.SEVERE, null, ex);
        }
    }
    
    public void aluguer(){
        double custo;
        String server;
        try {
            server = (String) in.readObject();
            custo = (Double) in.readObject();
            System.out.println("Custo do server do tipo "+server+ " é: "+custo+ "€/hora ");
            String value = "ok";
            while(!value.equals("2")){
                String s = (String) this.in.readObject();
                System.out.println("Deseja continuar com o aluguer do servidor?");
                System.out.println("1.Sim");
                System.out.println("2.Não");
                System.out.print(">");
                value = (String) systemIn.readLine();
                this.out.writeObject(value);
            }
            double custoTotal = (Double) this.in.readObject();
            this.user.retiraSaldo(custoTotal);
            this.out.writeObject(user.getMail());
            this.out.flush();
        } catch (IOException | ClassNotFoundException ex) {
           Logger.getLogger(Client.class.getName()).log(Level.SEVERE, null, ex);
        }
    }
    
    
    public void clientSecondMenu(){
        try {
            System.out.println("### Reserva de servidores ###");
        
            String value ="hello";
            while(!(value.equals("6"))){
                secondMenu();
                System.out.print("> ");
                value = (String) this.systemIn.readLine();
                this.out.writeObject(value);
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
                        this.out.writeObject(user.getMail());
                        value = "6";
                        break;
                }
            }
            this.out.flush();
        } catch (IOException ex) {
           Logger.getLogger(Client.class.getName()).log(Level.SEVERE, null, ex);
        }
    }
    
    public void menuAluguer(){
        try {       
            String value ="ok";
            while(!(value.equals("4"))){
                presentigServers();
                System.out.print("> ");
                value = (String) this.systemIn.readLine();
                this.out.writeObject(value);
                
                if (!(value.equals("4"))) aluguer();
            }
        } catch (IOException ex) {
           Logger.getLogger(Client.class.getName()).log(Level.SEVERE, null, ex);
        }
    }
    
    public void leilao(){
        try {
            boolean flag = (Boolean) this.in.readObject();
            if (flag==true){
                System.out.println("Os servidores encontram-se todos ocupados!\n Tente novamente mais tarde!");
            }
            else {
                this.out.writeObject(this.user.getMail());
                this.listener = new Thread(new ClientListener());  
                this.listener.setDaemon(true);
                listener.start();
                String msg;
                String value = "ok";
                System.out.println("Entrou no leilao");
            
                while(!value.equals("quit")){
                    System.out.print("> ");
                    value = this.systemIn.readLine();
                    this.out.writeObject(value);
                }

                this.out.writeObject(this.user.getMail());
                boolean winner = (Boolean) this.in.readObject();
                
                if (winner){
                    aluguer();
                }
            }
            this.out.flush();
        } catch (IOException | ClassNotFoundException ex ) {
            Logger.getLogger(Client.class.getName()).log(Level.SEVERE, null, ex);
        }
    }
    
    public void menuLeilao(){
        try {           
            String value ="ok";
            while(!(value.equals("4"))){
                presentigServers();
                System.out.print("> ");
                value = (String) this.systemIn.readLine();
                this.out.writeObject(value);
                if(!(value.equals("4"))) leilao();
            }
            this.out.flush();
        } catch (IOException ex) {
          Logger.getLogger(Client.class.getName()).log(Level.SEVERE, null, ex);
        }
    }
    

    public void clientStart(){
        try {
            System.out.println("### CLIENT ###");
            inicializing();
            String value = "hello";
            while(!(value.equals("3"))){
                mainMenu();
                System.out.print("> ");
                value = (String) this.systemIn.readLine();
                this.out.writeObject(value);
                switch(value){
                    case "1":
                        registar();
                        clientSecondMenu();
                        break;
                    case "2":
                        login();
                        clientSecondMenu();
                        break;
                }
            }
            this.out.flush();
            close();
        } catch (IOException ex) {
            Logger.getLogger(Client.class.getName()).log(Level.SEVERE, null, ex);
        }
    }
    
    
    
    public void close() {
        try {
            this.socket.shutdownInput();
            this.socket.shutdownOutput();
            this.socket.close();
            this.systemIn.close();
        } catch (IOException ex) {
           Logger.getLogger(Client.class.getName()).log(Level.SEVERE, null, ex);
        }    
    }
    
    public static void main(String[] args){
        Client c = new Client("127.0.0.1",12345);
        c.clientStart();
    }
    
    public class ClientListener implements Runnable {
        private boolean terminado;
	public ClientListener(){}
	
        public synchronized void leilaoTerminado(){
            while(terminado){
                try {
                    this.wait();
                } catch (InterruptedException ex) {
                    Logger.getLogger(Client.class.getName()).log(Level.SEVERE, null, ex);
                }
            }
        }
        
        public synchronized void leilaoIniciado(){
            System.out.println("Acordou!");
            this.notify();
        }
        
        @Override
	public void run(){
            String message;
            
            try {
                while(true){
                    while(((message = (String) in.readObject())!= "quit") && !(terminado = (Boolean) in.readObject())){
                        System.out.println("");
                        System.out.println(message);
                        System.out.print("> ");
                    }
                    leilaoTerminado();
                }
            }
            catch (SocketException e) {}
            catch (IOException | ClassNotFoundException e) {
                Logger.getLogger(Client.class.getName()).log(Level.SEVERE, null, e);
            }
	}
    }

}
