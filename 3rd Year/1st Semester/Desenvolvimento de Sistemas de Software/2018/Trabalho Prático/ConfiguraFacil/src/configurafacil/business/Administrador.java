package configurafacil.business;

import java.io.Serializable;

/**
 *
 * @author Todos
 */
public class Administrador implements Serializable {
    
    private String userName;
    private String pass;
    
    public Administrador() {
        userName = "admin";
        pass = "password";
    }

    public Administrador(String userName, String pass) {
        this.userName = userName;
        this.pass = pass;
    }

    public String getUserName() {
        return userName;
    }

    public void setUserName(String userName) {
        this.userName = userName;
    }

    public String getPass() {
        return pass;
    }

    public void setPass(String pass) {
        this.pass = pass;
    }
}
