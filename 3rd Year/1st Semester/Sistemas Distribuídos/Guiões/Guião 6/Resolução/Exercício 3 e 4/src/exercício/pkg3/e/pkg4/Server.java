package exercício.pkg3.e.pkg4;

import java.io.BufferedReader;
import java.io.BufferedWriter;
import java.io.IOException;
import java.io.InputStreamReader;
import java.io.OutputStreamWriter;
import java.net.ServerSocket;
import java.net.Socket;

/**
 *
 * @author Diogo Nogueira
 */
public class Server {

    private ServerSocket serverSocket;
    private int porto;
    
    public Server(int porto){
        this.porto = porto;
    }
    
    public void iniciarServidor() throws IOException{
        
        this.serverSocket = new ServerSocket(this.porto);
        
        while(true){
            
            Socket socket = this.serverSocket.accept();
            
            BufferedReader in = new BufferedReader(new InputStreamReader(socket.getInputStream()));
            BufferedWriter out = new BufferedWriter(new OutputStreamWriter(socket.getOutputStream()));
            
            int somaNumeros = 0;
            int totalNumerosRecebidos = 0;
            String line;
            
            // Enquanto recebermos informação por parte do Cliente.
            while((line = in.readLine()) != null){
                somaNumeros = somaNumeros + Integer.parseInt(line);
                totalNumerosRecebidos++;
                out.write(String.valueOf(somaNumeros));
                out.newLine();
                out.flush();
            }
            
            // Depois de receber toda a informação para aquele Cliente.
            
            double media = somaNumeros/totalNumerosRecebidos;
            out.write(String.valueOf(media));
            out.newLine();
            out.flush();
            
            // Depois de fornecer a média pedida, fechamos o canal.
            socket.shutdownInput();
            socket.shutdownOutput();
            socket.close();
        }
    }
      
    public static void main(String[] args) throws IOException {
	Server servidor = new Server(12345);
	servidor.iniciarServidor();
    }
}
