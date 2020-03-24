import java.io.*;
import java.net.*;
import java.nio.ByteBuffer;

/**
 * Código-fonte para a Classe Servidor, que tem metade do código, concretamente da parte de receber os dados (GET).
 * @author Diogo Araújo, Diogo Nogueira
 * @version 2.5 - Final
 */
class Servidor {

    /** Variável predefinida como o tamanho total total do pacote. **/
    private static final int pacoteTotalUDP = 1000 + 4;

    /**
     * Construtor parametrizado para a criação do Servidor (GET).
     * @param portaUDP Porta UDP usada para receber o(s) pacote(s) UDP (7777).
     * @param portaACK Porta ACK usada para enviar os pacotes ACK durante a transferência (9999).
     * @param localDisco A diretoria para onde o ficheiro a ser recebido irá ser colocado.
     */
    public Servidor(int portaUDP, int portaACK, String localDisco) {

        DatagramSocket socketRececao, socketEnvio;

        int numeroSequencia = -1000;
        int proximoACK = 0;

        boolean ficheiroRecebido = false;

        try {

            // Criação dos Sockets de Rececao e Envio.
            // Servidor vai receber pacotes UDP do Cliente pelo socketRececao.
            // Servidor vai mandar pacotes ACK do Cliente pelo socketEnvio.
            socketRececao = new DatagramSocket(portaUDP);
            socketEnvio = new DatagramSocket();

            StringBuilder estabelecimentoConexao = new StringBuilder("Conexão Servidor Estabelecida");
            estabelecimentoConexao.append("\n");
            estabelecimentoConexao.append("Porta Entrada dos Dados - ");
            estabelecimentoConexao.append(portaUDP);
            estabelecimentoConexao.append("\n");
            System.out.println(estabelecimentoConexao);

            try {
                // Preparação do pacote de dados vindo do Cliente.
                byte[] dadosRecebidos = new byte[pacoteTotalUDP];
                DatagramPacket pacoteRecebido = new DatagramPacket(dadosRecebidos, dadosRecebidos.length);

                // Iniciar o ficheiro que vai ser criado ao longo do ciclo de receção.
                FileOutputStream fileStream = null;

                // Ciclo que é executado até ficheiro estar totalmente recebido.
                do {
                    // Recebe o pacote vindo do Cliente.
                    socketRececao.receive(pacoteRecebido);
                    InetAddress ipAddress = pacoteRecebido.getAddress();

                    // Retira o número de sequência do pacote recebido.
                    // Obtém esse número retirando apenas a parte do cabeçalho do pacote (0 a 4 bytes).
                    int numSeqPacoteRecebido = ByteBuffer.wrap(dadosRecebidos, 0, 4).getInt();

                    // Prints essenciais ao Servidor.
                    // Caso seja o "primeiro pacote" sabe-se que a conexão em si foi estabelecida.
                    // Cliente envia 0 para o Servidor saber que deve começar os seus pedidos ACK.
                    if(numSeqPacoteRecebido==0) System.out.println("Pacote Inicial Recebido. Servidor pode começar o seu pedido.");
                    else{
                        StringBuilder stringPacote = new StringBuilder("Servidor > ");
                        stringPacote.append("Pacote número ");
                        stringPacote.append(numSeqPacoteRecebido);
                        stringPacote.append(" recebido.");
                        System.out.println(stringPacote);
                    }

                    // Não se trata de um pacote recebido fora de hora.
                    if(numSeqPacoteRecebido == proximoACK) {

                        // Se pacote é o primerio de toda a sequência.
                        // Cria-se o ficheiro em si.
                        if(numSeqPacoteRecebido == 0 && numeroSequencia == -1000) fileStream = new FileOutputStream(new File(localDisco));

                        // Se pacote é o último (só possui o cabeçalho).
                        if(pacoteRecebido.getLength() == 4) {

                            // Pacote enviado vai definir o final da conexão dado que o ficheiro está totalmente recebido.
                            byte[] pacoteFinal = PacoteUDP.gerarPacoteACK(-5);
                            socketEnvio.send(new DatagramPacket(pacoteFinal, pacoteFinal.length, ipAddress, portaACK));

                            System.out.println("Servidor > ACK final.");

                            // Atualiza-se a flag que passa a declarar que o ficheiro foi totalmente recebido.
                            ficheiroRecebido = true;

                            System.out.println("Servidor > Ficheiro totalmente recebido.");
                        }

                        // Se pacote nem é o último nem o primeiro (intermediários).
                        else {

                            // Atualiza-se o próximo número de ACK a enviar à base do tamanho do pacote.
                            // Reparar que vamos recebendo de 1000 em 1000 bytes.
                            proximoACK = numSeqPacoteRecebido + 1000;

                            // Envia o ACK para avisar que recebeu aquele número de sequência.
                            byte[] pacoteACK = PacoteUDP.gerarPacoteACK(proximoACK);
                            socketEnvio.send(new DatagramPacket(pacoteACK, pacoteACK.length, ipAddress, portaACK));

                            StringBuilder pacoteUDP = new StringBuilder("Servidor > ACK ");
                            pacoteUDP.append(proximoACK);
                            System.out.println(pacoteUDP);
                        }

                        // Escreve os dados no ficheiro.
                        // Escrevemos só a parte dos dados, daí ser dos 4 aos 1000 bytes (4 correspondem ao cabeçalho).
                        fileStream.write(dadosRecebidos, 4, 1000);

                        numeroSequencia = numSeqPacoteRecebido;
                    }

                    // Se pacote não foi recebido quando era suposto.
                    // Tem de se enviar o pacote ACK de novo (duplicado).
                    // Assim o Cliente sabe que o Servidor em si não recebeu aquilo que pediu.
                    else {

                        byte[] pacoteAck = PacoteUDP.gerarPacoteACK(numeroSequencia);
                        socketEnvio.send(new DatagramPacket(pacoteAck, pacoteAck.length, ipAddress, portaACK));

                        StringBuilder pacoteDuplicado = new StringBuilder("Servidor > ACK duplicado ");
                        pacoteDuplicado.append(numeroSequencia);
                        System.out.println(pacoteDuplicado);
                    }
                } while(ficheiroRecebido == false);

                fileStream.close();

            } catch (Exception e) {
                e.printStackTrace();
                System.exit(-1);
            } finally {
                socketRececao.close();
                socketEnvio.close();
                System.out.println("Servidor > Conexão encerrada.");
            }
        } catch (SocketException e1) {
            e1.printStackTrace();
            System.exit(-1);
        }
    }
}