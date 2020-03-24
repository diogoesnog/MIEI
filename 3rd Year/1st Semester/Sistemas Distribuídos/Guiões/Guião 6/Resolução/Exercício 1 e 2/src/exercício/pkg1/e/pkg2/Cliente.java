package exercício.pkg1.e.pkg2;

import java.io.BufferedReader;
import java.io.BufferedWriter;
import java.io.IOException;
import java.io.InputStreamReader;
import java.io.OutputStreamWriter;
import java.net.Socket;

/**
 *
 * @author Diogo Nogueira
 */
public class Cliente {
    
    private final String hostname;
    private final int porto;
    private Socket socket;
    
    public Cliente(String hostname, int porto){
        this.hostname = hostname;
        this.porto = porto;
    }
    
    public void iniciarCliente() throws IOException{
        
        socket = new Socket(this.hostname,this.porto);
        
        BufferedReader in = new BufferedReader(new InputStreamReader(socket.getInputStream()));
        BufferedWriter out = new BufferedWriter(new OutputStreamWriter(socket.getOutputStream()));
        
	BufferedReader systemIn = new BufferedReader(new InputStreamReader(System.in));
        
        String inputCliente;
        String outputServidor;
        
        while((inputCliente = systemIn.readLine())!= null && !inputCliente.equals("quit")){
            
            out.write(inputCliente);
            out.newLine();
            out.flush();
            
            outputServidor = in.readLine();         
        }
                
        // Fechar socket e respetivos canais.
        socket.shutdownOutput();
        socket.shutdownInput();
        socket.close();
    }
    
    public static void main(String[] args) throws IOException{
        Cliente cliente = new Cliente("127.0.0.1",12345);
        cliente.iniciarCliente();
    }
}
