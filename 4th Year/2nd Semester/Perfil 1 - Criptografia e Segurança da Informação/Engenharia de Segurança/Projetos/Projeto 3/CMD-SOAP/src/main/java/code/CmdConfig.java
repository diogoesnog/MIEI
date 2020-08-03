package code;

/**
 * Classe usada para configurar o URL do WSDL a usar e do Application ID Fornecido pela AMA
 * @author Diogo Araújo
 * @author Diogo Nogueira
 * @version 1.0
 */
public class CmdConfig {

    // ApplicationId da Entidade. Fornecida pela AMA
    final String applicationId  = "b826359c-06f8-425e-8ec3-50a97a418916";

    /**
     * Método que retorna o Application Id fornecido pela AMA
     * @return Application Id fornecido pela AMA
     */
    public byte[] getApplicationId() {
        return applicationId.getBytes();
    }

}
