/*
* Trabalho realizado para DSS
 */
package configurafacil.data;

import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.SQLException;

/**
 *
 * @author Diogo Araújo
 */
public class ConnectBD {
    
    private static final String URL = "localhost:30";
    private static final String DB = "configurafacil";
    private static final String USERNAME = "root"; 
    private static final String PASSWORD = "mysql";
    
    /**
     * Estabelece ligação à base de dados
     * @return
     * @throws SQLException
     * @throws ClassNotFoundException 
     */
    public static Connection connect() throws SQLException, ClassNotFoundException {
        Class.forName("com.mysql.cj.jdbc.Driver");
        //cliente deve fechar conexão!
        Connection c = DriverManager.getConnection("jdbc:mysql://localhost:3306/configurafacil?serverTimezone=UTC", USERNAME, PASSWORD);
        return c;  
    }
    
    /**
     * Fecha a ligação à base de dados, se aberta.
     * @param c A conexão a fechar
     */
    public static void close(Connection c) {
        try {
            if(c!=null && !c.isClosed()) {
                c.close();
            }
        } catch (SQLException e) {}
    }
}