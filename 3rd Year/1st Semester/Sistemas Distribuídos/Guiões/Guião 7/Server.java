import java.io.IOException;
import java.net.ServerSocket;
import java.net.Socket;

public class Server {

    private ServerSocket serverSocket;
    private int porto;
    private Banco banco;

    public Server (int porto){
        this.porto = porto;
        this.banco = new Banco();
    }

    public void iniciarServidor(){

        try{

            this.serverSocket = new ServerSocket(this.porto);

            while(true){
                Socket socket = serverSocket.accept();
                ServerWorker cliente = new ServerWorker(socket,banco);
                
                Thread clienteT = new Thread(cliente);
                clienteT.start();
            }           
        } catch(IOException e){} 
    }
}