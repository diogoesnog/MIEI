import java.sql.Connection;
import java.sql.PreparedStatement;
import java.sql.SQLException;

public class PacienteDAO {

    /**
     * Método que trata de preparar os fields da tabela "paciente", inserindo uma row na tabela em si.
     * @param idPaciente ID do Paciente.
     * @param nome Nome do Paciente.
     * @param dataNascimento Data de Nascimento do Paciente.
     * @param idade Idade do Paciente
     * @param connection Conexão corrente da Base de Dados.
     * @throws SQLException
     */
    public void insereJSON(int idPaciente, String nome, String dataNascimento, int idade, Connection connection) throws SQLException {

            PreparedStatement stm = connection.prepareStatement(
                    "INSERT INTO paciente VALUES(?,?,?,?)"
            );
            stm.setInt(1, idPaciente);
            stm.setString(2, nome);
            stm.setString(3, dataNascimento);
            stm.setInt(4, idade);
            stm.executeUpdate();
    }
}
