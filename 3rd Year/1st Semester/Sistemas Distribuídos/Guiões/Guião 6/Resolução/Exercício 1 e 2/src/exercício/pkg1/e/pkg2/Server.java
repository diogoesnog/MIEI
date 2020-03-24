package exercício.pkg1.e.pkg2;

/**
 *
 * @author Diogo Nogueira
 */
import java.io.BufferedReader;
import java.io.BufferedWriter;
import java.io.IOException;
import java.io.InputStreamReader;
import java.io.OutputStreamWriter;
import java.net.ServerSocket;
import java.net.Socket;

public class Server {

    private ServerSocket serverSocket;
    private final int porto;

    public Server (int porto){
	this.porto = porto;
    }

    public void iniciarServidor() throws IOException{

        // Cria um novo ServerSocket num dado porto.
        this.serverSocket = new ServerSocket(this.porto);

	// Aceita conexões indefinidamente.
	while(true){
		
            System.out.println("Servidor está à espera de conexões.");
            Socket socket = serverSocket.accept();
            System.out.println("Conexão estabelecida.");
				

            // Criação dos canais de escrita e leitura nesse Socket.
            BufferedReader in = new BufferedReader(new InputStreamReader(socket.getInputStream()));
            BufferedWriter out = new BufferedWriter(new OutputStreamWriter(socket.getOutputStream()));

            // String para ler linhas do Cliente.
            String line;
			
            // Le dos canais de entrada e escreve nos canais de saida.
            while((line = in.readLine()) != null){
		out.write(line);
		out.newLine();
		out.flush();
            }
				
            // Fechar socket e respetivos canais.
            socket.shutdownOutput();
            socket.shutdownInput();
            socket.close();
	}
    }
    
    public static void main(String[] args) throws IOException{
        Server servidor = new Server(12345);
        servidor.iniciarServidor();
    }
}
