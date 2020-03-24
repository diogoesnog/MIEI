import org.json.JSONObject;

import java.io.*;
import java.net.URL;
import java.nio.charset.Charset;
import java.sql.Connection;
import java.sql.SQLException;

public class JSONParseToDataBase{

    /**
     * Método que trata de ler todo o texto do ficheiro JSON.
     * @param rd Ficheiro Reader.
     * @return Uma String que contém todo o texto do ficheiro JSON.
     * @throws IOException
     */
    private static String readAll(Reader rd) throws IOException {
        StringBuilder sb = new StringBuilder();
        int cp;
        while ((cp = rd.read()) != -1) {
            sb.append((char) cp);
        }
        return sb.toString();
    }

    /**
     * Método que através do URL do ficheiro JSON, converte-o num objeto JSONObject pronto para ser feito o seu parse.
     * @param url URL do ficheiro JSON.
     * @return Objeto JSON que se quer fazer o parse.
     * @throws IOException
     */
    public static JSONObject readJsonFromUrl(String url) throws IOException {
        InputStream is = new URL(url).openStream();
        try {
            BufferedReader rd = new BufferedReader(new InputStreamReader(is, Charset.forName("UTF-8")));
            String jsonText = readAll(rd);
            JSONObject json = new JSONObject(jsonText);
            return json;
        } finally {
            is.close();
        }
    }

    /**
     * Método que faz o parse da informação relativa ao Paciente.
     * @param json Ficheiro JSON em modo JSONObject.
     * @param connection Conexão corrente da Base de Dados.
     * @throws SQLException
     */
    public static void insereDBPaciente(JSONObject json, Connection connection) throws SQLException{

        JSONObject infoPaciente = (JSONObject) json.get("patient");

        Integer idPaciente = (Integer) infoPaciente.get("patientid");
        String nomePaciente = (String) infoPaciente.get("patientname");
        String dataNascPaciente = (String) infoPaciente.get("patientbirthdate");
        Integer idadePaciente = (Integer) infoPaciente.get("patientage");

        PacienteDAO pdao = new PacienteDAO();
        pdao.insereJSON(idPaciente, nomePaciente, dataNascPaciente, idadePaciente, connection);
    }

    /**
     * Método que faz o parse da informação relativa à Medição.
     * @param json Ficheiro JSON em modo JSONObject.
     * @param connection Conexão corrente da Base de Dados.
     * @throws SQLException
     */
    public static void insereDBMedicao(JSONObject json, Connection connection) throws SQLException {

        JSONObject infoPaciente = (JSONObject) json.get("patient");
        Integer idPaciente = (Integer) infoPaciente.get("patientid");

        Integer numeroSensores = (Integer) json.get("number_of_sensors");
        Integer idSensor = (Integer) json.get("sensorid");
        Integer numSensor = (Integer) json.get("sensornum");
        String tipoSensor = (String) json.get("type_of_sensor");
        Integer tempCorporal = (Integer) json.get("bodytemp");
        Integer bpm = (Integer) json.get("bpm");
        String timeStamp = (String) json.get("timestamp");

        JSONObject infoSangue = (JSONObject) json.get("bloodpress");
        Integer systolic = (Integer) infoSangue.get("systolic");
        Integer diastolic = (Integer) infoSangue.get("diastolic");

        MedicaoDAO mdao = new MedicaoDAO();
        mdao.insereJSON(tempCorporal, timeStamp, systolic, diastolic, idSensor, numSensor, tipoSensor, idPaciente, connection);
    }

    public static void main(String[] args) throws IOException, SQLException, ClassNotFoundException, InterruptedException {

        Connection connection = ConnectBD.connect();
        StringBuilder urlFicheiro = new StringBuilder("http://nosql.hpeixoto.me/api/sensor/300");

        // Inserir primeiro os Pacientes de uma só vez.
        int numeroPacientes = 1;

        while(numeroPacientes<6){
            urlFicheiro.append(numeroPacientes);

            JSONObject json = readJsonFromUrl(urlFicheiro.toString());
            insereDBPaciente(json,connection);

            numeroPacientes++;
            urlFicheiro.deleteCharAt(39);
        }

        while(connection.isValid(10)){

            // Inserir as Medições em Tempo Real.
            int numeroSensor = 1;

            while(numeroSensor<6){
                urlFicheiro.append(numeroSensor);

                JSONObject json = readJsonFromUrl(urlFicheiro.toString());
                insereDBMedicao(json,connection);

                numeroSensor++;
                urlFicheiro.deleteCharAt(39);

                Thread.sleep(1000);
            }
        }
    }
}