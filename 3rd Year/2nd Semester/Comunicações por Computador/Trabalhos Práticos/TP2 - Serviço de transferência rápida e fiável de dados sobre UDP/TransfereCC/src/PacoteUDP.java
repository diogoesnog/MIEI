import java.nio.ByteBuffer;
import java.util.Arrays;


/**
 * Classe para as funções principais da criação do pacote de dados ou apenas de ACK.
 * @author Diogo Araújo, Diogo Nogueira
 * @version 2.0
 */
class PacoteUDP {

    /** A variável final a indicar o "cabeçalho" do pacote a utilizar **/
    private static final int headerPDU = 4;

    /**
     * Cria o pacote com numero de sequência e os dados em bytes.
     * @param numSeq O nº de sequência do pacote a ser criado.
     * @param dadosByte O array de dados a ser enviado neste pacote.
     * @return O array do pacote já alocado e pronto a ser enviado pelo Socket.
     */
    static byte[] gerarPacoteDados(int numSeq, byte[] dadosByte) {
        return ByteBuffer.allocate(headerPDU + dadosByte.length).putInt(numSeq).put(dadosByte).array();
    }

    /**
     * Cria o pacote ACK com o numero pedido.
     * @param numACK O nº ACK do pacote a ser criado.
     * @return O array do pacote já alocado e pronto a ser enviado pelo Socket.
     */
    static byte[] gerarPacoteACK(int numACK) {
        return ByteBuffer.allocate(headerPDU).putInt(numACK).array();
    }

    /**
     * Função para obter o nº ACK do pacote em questão.
     * @param pacote O pacote para o qual se quer obter o ACK.
     * @return O ACK do pacote.
     */
    static int getACK(byte[] pacote) {
        return ByteBuffer.wrap(Arrays.copyOfRange(pacote,0,headerPDU)).getInt();
    }
}
