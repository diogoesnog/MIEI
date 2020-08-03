
package main;

import java.util.HashMap;


public class Users {
    
    private HashMap<String,User> users;
    
    public Users(){
        this.users = new HashMap<>();
    }
    
    /**
     * Método que regista um User-
     * @param u User que pretende se registar.
     */
    public synchronized void addUser(String mail, String pass) {
        User u = new User(mail,pass,0);
        this.users.put(u.getMail(), u);
    }
    
    /**
     * Método que retira o montante de uma conta
     * @param u 
     */
    public synchronized void retiraConta(String mail, double montante){
        User u1 = this.users.get(mail);
        u1.retiraSaldo(montante);
    }
    
    public synchronized void depositaConta(String mail, double custo){
        User u = this.users.get(mail);
        u.depositaSaldo(custo);
    }
    
    public synchronized double getSaldo(String mail){
        User u = this.getUser(mail);
        return u.getSaldo();
    }
    
    public synchronized boolean userExists(String mail){
         return(this.users.containsKey(mail));
    }
    
    public synchronized void setAtivo(String mail,boolean flag){
        User u = this.users.get(mail);
        u.setAtivo(flag);
    }
    
    
    public synchronized boolean isAtivo(String mail){
        User u = this.getUser(mail);
        return u.getAtivo();
    }
    
    public synchronized boolean autentification(String pass, String mail) {
        if((this.users.containsKey(mail))){
            User u = this.users.get(mail);
            if (!u.getAtivo()){
                u.setAtivo(true);
                return(u.autentification(pass));
            }
        }
        return false;
    }
    
    public synchronized User getUser(String mail){
        User u =this.users.get(mail);
        return u;
    }
    
    public String toString(){
        StringBuilder s = new StringBuilder("Clientes:\n");
        for(User u: this.users.values()){
            s.append(u);
        }
        return s.toString();
    }
}
