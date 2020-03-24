import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.SQLException;

public class ConnectBD {

    private static final String USERNAME = "root";
    private static final String PASSWORD = "root";

    /**
     * Método que estabelece ligação à base de dados
     * @return A conexão em si.
     * @throws SQLException
     * @throws ClassNotFoundException
     */
    public static Connection connect() throws SQLException, ClassNotFoundException {
        Class.forName("com.mysql.cj.jdbc.Driver");

        Connection c = DriverManager.getConnection("jdbc:mysql://localhost:3306/ficha4?serverTimezone=UTC", USERNAME, PASSWORD);
        return c;
    }

    /**
     * Método que fecha a ligação à base de dados, se aberta.
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
