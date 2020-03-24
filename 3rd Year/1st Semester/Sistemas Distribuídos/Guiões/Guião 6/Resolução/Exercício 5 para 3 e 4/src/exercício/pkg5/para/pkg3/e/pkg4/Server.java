package exercício.pkg5.para.pkg3.e.pkg4;

/**
 *
 * @author Diogo Nogueira
 */
import java.io.IOException;
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
        int contadorClientes = 1;

	// Aceita conexões indefinidamente.
	while(true){
		
            System.out.println("Servidor está à espera de conexões.");
            Socket socket = serverSocket.accept();
            System.out.println("Conexão estabelecida.");
				
            ServerWorker cliente = new ServerWorker(socket,contadorClientes);
            contadorClientes++;
            
            Thread novoCliente = new Thread(cliente);
            novoCliente.start();
	}
    }
}