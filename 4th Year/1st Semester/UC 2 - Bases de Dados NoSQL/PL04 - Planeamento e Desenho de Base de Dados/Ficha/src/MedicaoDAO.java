import java.sql.Connection;
import java.sql.PreparedStatement;
import java.sql.SQLException;

public class MedicaoDAO {

        /**
        * Método que trata de preparar os fields da tabela "medicao", inserindo uma row na tabela em si.
        * @param tempCorporal Dados da Temperatura Corporal do Paciente.
        * @param timeStamp Informação do TimeStamp relativo ao registo da medição.
        * @param systolic Dados do systolic.
        * @param diastolic Dados do diastolic.
        * @param idSensor ID do Sensor.
        * @param numSensor Número do Sensor.
        * @param tipoSensor Tipo do Sensor.
        * @param idPaciente ID do Paciente a que corresponde a medição em causa.
        * @param connection Conexão corrente da Base de Dados.
        * @throws SQLException
        */
        public void insereJSON(int tempCorporal, String timeStamp, int systolic, int diastolic, int idSensor, int numSensor, String tipoSensor, int idPaciente, Connection connection) throws SQLException {

            PreparedStatement stm = connection.prepareStatement(
                    "INSERT INTO medicao(tempCorporal, timeStamp, systolic, diastolic, idSensor, numSensor, tipoSensor, Paciente_idPaciente)\n" +
                            "VALUES (?,?,?,?,?,?,?,?)"
            );
            stm.setInt(1, tempCorporal);
            stm.setString(2, timeStamp);
            stm.setInt(3, systolic);
            stm.setInt(4, diastolic);
            stm.setInt(5, idSensor);
            stm.setInt(6, numSensor);
            stm.setString(7, tipoSensor);
            stm.setInt(8, idPaciente);
            stm.executeUpdate();
        }
}
