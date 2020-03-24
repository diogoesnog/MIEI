import java.io.*;
import java.net.*;
import java.util.*;
import java.util.concurrent.Semaphore;

/**
 * Source-Code para a classe Cliente.
 * @author Diogo Araújo, Diogo Nogueira
 * @author Java Tutorial UDP Threads
 * @version 1.5 - Final
 */

class Cliente {

    /** Variável predefinida como o tamanho correspondente aos dados de um pacote UDP. **/
    private static final int dadosPacoteUDP = 1000;

    /** Variável para guardar o nº da janela corrente. **/
    /** Variável predefinida como o tamanho total da janela deslizante. **/
    /** Variável para guardar a lista de pacotes da janela deslizante. **/
    private int numSeqBaseJanela;
    private static final int quantMaxJanela = 5;
    private final List<byte[]> pacotesJanelaDeslizante;

    /** Variável para guardar o próximo nº de sequência. **/
    private int numeroSequenciaEnviar;

    /** A diretoria (nome do ficheiro inclusive) do ficheiro que será enviado. **/
    private final String nomeDiretoriaFicheiro;

    /** Temporizador a ser usado em caso de falha de resposta. **/
    /** Semáforo que vai dando permissão para as Threads atuarem. **/
    private Timer temporizador;
    private final Semaphore permissaoThread;

    /** Booleano final para confirmar se o ficheiro foi totalmente processado/enviado. **/
    private boolean ficheiroEnviado;

    /**
     * Construtor parametrizado para a criação do Cliente que irá fazer PUT no Servidor.
     * @param portaUDP Porta UDP que o Servidor tem aberta para receber o(s) pacote(s) UDP (7777).
     * @param portaACK Porta ACK usada para receber os pacotes ACK vindos do Servidor durante a transferência (9999).
     * @param localDisco A diretoria+nome do ficheiro a ser enviado.
     * @param enderecoIP Endereço IP do servidor a enviar o ficheiro.
     */
    Cliente(int portaUDP, int portaACK, String localDisco, String enderecoIP) {

        DatagramSocket  socketRececao, socketEnvio;

        numSeqBaseJanela = 0;
        numeroSequenciaEnviar = 0;
        pacotesJanelaDeslizante = new ArrayList<>(quantMaxJanela);

        this.nomeDiretoriaFicheiro = localDisco;

        ficheiroEnviado = false;
        permissaoThread = new Semaphore(1);

        StringBuilder estabelecimentoConexao = new StringBuilder("Conexão Cliente Estabelecida");
        estabelecimentoConexao.append("\n");
        estabelecimentoConexao.append("Porta Destino dos Dados - ");
        estabelecimentoConexao.append(portaUDP);
        estabelecimentoConexao.append("\n");
        estabelecimentoConexao.append("Ficheiro de Dados enviado - ");
        estabelecimentoConexao.append(localDisco);
        estabelecimentoConexao.append("\n");
        System.out.println(estabelecimentoConexao);
 
        try {

            // Criação dos Sockets de Rececao e Envio.
            // Cliente vai receber pacotes ACK do Servidor pelo socketRececao.
            // Cliente vai enviar pacotes UDP para o Servidor pelo socketEnvio.
            socketRececao = new DatagramSocket(portaACK);
            socketEnvio = new DatagramSocket();

            // Criação das threads que depois vão processar os dados enviados e recebidos.
            // Usam-se Threads precisamente pela concorrência/despacho em si.
            ThreadPacotesACK threadPacotesACK = new ThreadPacotesACK(socketRececao);
            ThreadPacotesUDP threadPacotesUDP = new ThreadPacotesUDP(socketEnvio, portaUDP, enderecoIP);

            // Inicialização das threads.
            threadPacotesACK.start();
            threadPacotesUDP.start();
 
        } catch (Exception e) {
            e.printStackTrace();
            System.exit(-1);
        }
    }

    /**
     * Classe interna para a criação do Temporizador e a sua execução.
     */
    class Temporizador extends TimerTask {

        /**
         * Método necessário para correr, vindo da interface Runnable do Java.
         * Com este método conseguimos dar permissão às Threads em termos de janela deslizante.
         */
        public void run() {
            try {
                permissaoThread.acquire();

                StringBuilder tempoExcedido = new StringBuilder("Cliente > Base Janela Deslizante mantida.");
                tempoExcedido.append("Tempo de espera esgotado.");
                System.out.println(tempoExcedido);

                numeroSequenciaEnviar = numSeqBaseJanela;

                permissaoThread.release();
            } catch (InterruptedException e) {
                e.printStackTrace();
            }
        }
    }

    /**
     * A classe interna para enviar os pacotes UDP para o Servidor em modo Thread.
     */
    class ThreadPacotesUDP extends Thread {
 
        private final DatagramSocket socketEnvio;
        private final int portaUDP;
        private InetAddress enderecoIP;

        /**
         * Construtor parametrizado para a criação do objeto de ThreadSaída.
         * @param socketEnvio O socket para onde irá sair os pacotes para o Servidor.
         * @param portaUDP A porta do Servidor para onde serão enviados os pacotes.
         * @param enderecoIP O endereço IP do Servidor para onde serão enviados os pacotes.
         * @throws UnknownHostException Uma exceção para quando não se conhece o endereço IP fornecido.
         */
        ThreadPacotesUDP(DatagramSocket socketEnvio, int portaUDP, String enderecoIP) throws UnknownHostException {
            this.socketEnvio = socketEnvio;
            this.portaUDP = portaUDP;
            this.enderecoIP = InetAddress.getByName(enderecoIP);
        }

        /**
         * Método (override) necessário para a Thread correr e conterá o código a ser corrido pela mesma.
         */
        public void run() {
            try {

                try(FileInputStream ficheiro = new FileInputStream(new File(nomeDiretoriaFicheiro))) {

                    do {

                        // Verificação se o pacote a enviar está dentro dos que a janela deslizante suporta.
                        if(numeroSequenciaEnviar < numSeqBaseJanela + 5000) {

                            // Dá permissão para a Thread/pacote.
                            permissaoThread.acquire();

                            if(numSeqBaseJanela == numeroSequenciaEnviar) {
                                // Cancela-se o temporizador caso não esteja ativo.
                                if(temporizador != null) temporizador.cancel();
                                // Inicialização temporizador.
                                temporizador = new Timer();
                                temporizador.schedule(new Temporizador(), 5000);
                            }

                            byte[] dadosEnviados;

                            // Espécie de flag que identifica se é o último pacote.
                            // Coloca-se a 0 quando não há mais bytes para enviar.
                            int ultimoNumSeq = -1;

                            if(numeroSequenciaEnviar < pacotesJanelaDeslizante.size()) {
                                dadosEnviados = pacotesJanelaDeslizante.get(numeroSequenciaEnviar);

                                // Envia o pacote de dados para o Servidor consoante o número de ACK que recebeu do mesmo.
                                socketEnvio.send(new DatagramPacket(dadosEnviados, dadosEnviados.length, enderecoIP, portaUDP));
                            }
                            else {

                                byte[] dataBuffer = new byte[dadosPacoteUDP];
                                int tamanhoDados = ficheiro.read(dataBuffer, 0, dadosPacoteUDP);

                                // Ainda existem dados para enviar.
                                if(tamanhoDados != -1) {
                                    byte[] dataBytes = Arrays.copyOfRange(dataBuffer, 0, tamanhoDados);
                                    dadosEnviados = PacoteUDP.gerarPacoteDados(numeroSequenciaEnviar, dataBytes);

                                    pacotesJanelaDeslizante.add(dadosEnviados);

                                    // Envia o pacote de dados para o Servidor consoante o número de ACK que recebeu do mesmo.
                                    // Número estabelecido pelo numeroSequenciaEnviar.
                                    socketEnvio.send(new DatagramPacket(dadosEnviados, dadosEnviados.length, enderecoIP, portaUDP));
                                }

                                // Não existem mais dados para enviar.
                                if(tamanhoDados == -1) {
                                    ultimoNumSeq = 0;
                                    dadosEnviados = PacoteUDP.gerarPacoteDados(numeroSequenciaEnviar, new byte[0]);

                                    pacotesJanelaDeslizante.add(dadosEnviados);

                                    // Envia o pacote de dados para o Servidor consoante o número de ACK que recebeu do mesmo.
                                    // Número estabelecido pelo numeroSequenciaEnviar.
                                    socketEnvio.send(new DatagramPacket(dadosEnviados, dadosEnviados.length, enderecoIP, portaUDP));
                                }
                            }

                            // Prints essenciais ao Cliente.
                            if(numeroSequenciaEnviar == 0) System.out.println("Pacote Inicial Enviado. Sinal dado ao Servidor.");
                            else{
                                StringBuilder pacoteEnviado = new StringBuilder("Cliente > ");
                                pacoteEnviado.append("Pacote número ");
                                pacoteEnviado.append(numeroSequenciaEnviar);
                                pacoteEnviado.append(" enviado.");
                                System.out.println(pacoteEnviado);
                            }

                            // Atualiza número de sequência caso não esteja no fim.
                            // Atualizamos a 0 quando não há mais dados a enviar.
                            if(ultimoNumSeq != 0) numeroSequenciaEnviar += 1000;

                            // Liberta permissaoThread para as outras threads/pacotes.
                            permissaoThread.release();
                        }
                    } while(ficheiroEnviado == false);

                } catch (Exception e) {
                    e.printStackTrace();
                } finally {
                    // Cancela-se um eventual temporizador caso esteja ativo.
                    if(temporizador != null) temporizador.cancel();
                    socketEnvio.close();
                    System.out.println("Cliente > Ficheiro totalmente enviado.");
                }
            } catch (Exception e) {
                e.printStackTrace();
                System.exit(-1);
            }
        }
    }

    /**
     * A classe interna para receber os pacotes de ACK enviados pelo Servidor em modo Thread.
     */
    class ThreadPacotesACK extends Thread {
 
        private final DatagramSocket socketRececao;

        /**
         * Construtor parametrizado para a criação do Thread dos Pacotes ACK.
         * @param socketRececao O socket para onde irá entrar os Pacotes ACK do Servidor.
         */
        ThreadPacotesACK(DatagramSocket socketRececao) {this.socketRececao = socketRececao;}

        /**
         * Método (override) necessário para a Thread correr e conterá o código a ser corrido pela mesma.
         */
        public void run() {
            try {

                // Preparação do pacote ACK vindo do Servidor.
                // 4 são o número de bytes do cabeçalho em si.
                byte[] recebeDados = new byte[4];

                DatagramPacket pacoteRecebido = new DatagramPacket(recebeDados, recebeDados.length);

                try {
                    do {
                        socketRececao.receive(pacoteRecebido);

                        // Obtém o número ACK do pacote que recebeu do Servidor.
                        int numACK = PacoteUDP.getACK(recebeDados);

                        // Quando o número do Pacote ACK é diferente de -5, não estamos a lidar com o último.
                        if(numACK != -5) {

                            StringBuilder pacoteACK = new StringBuilder("Cliente > ACK ");
                            pacoteACK.append(numACK);
                            System.out.println(pacoteACK);
                        }

                        // Se o pacote ACK recebido for duplicado.
                        if(numSeqBaseJanela == numACK + 1000) {

                            StringBuilder pacoteDuplicado = new StringBuilder("Cliente > ACK duplicado ");
                            pacoteDuplicado.append(numACK);
                            System.out.println(pacoteDuplicado);

                            // Bloqueia o permissaoThread para a thread/pacote.
                            permissaoThread.acquire();

                            if(temporizador != null) temporizador.cancel();

                            numeroSequenciaEnviar = numSeqBaseJanela;
                            // Liberta permissaoThread para outras threads/pacotes.
                            permissaoThread.release();
                        }

                        // Caso o pacote ACK tenha número -5.
                        // Último pacote - transferência completa.
                        if(numACK == -5) {
                            ficheiroEnviado = true;
                            System.out.println("Cliente > ACK final.");
                        }

                        else {
                            // Avanço do pacote numSeqBaseJanela da janela para o numACK + os 1000 de tamanho.
                            numSeqBaseJanela = numACK + dadosPacoteUDP;

                            // Bloqueia o permissaoThread para a thread/pacote.
                            permissaoThread.acquire();
                            if (numSeqBaseJanela == numeroSequenciaEnviar) {
                                if(temporizador != null) temporizador.cancel();
                            }

                            if (numSeqBaseJanela != numeroSequenciaEnviar){
                                if(temporizador != null) temporizador.cancel();
                                temporizador = new Timer();
                                temporizador.schedule(new Temporizador(), 5000);
                            }

                            // Liberta permissaoThread para outras threads/pacotes.
                            permissaoThread.release();
                        }

                    } while(ficheiroEnviado == false);

                } catch (Exception e) {
                    e.printStackTrace();
                } finally {
                    socketRececao.close();
                    System.out.println("Cliente > Conexão encerrada.");
                }
            } catch (Exception e) {
                e.printStackTrace();
                System.exit(-1);
            }
        }
    }
}