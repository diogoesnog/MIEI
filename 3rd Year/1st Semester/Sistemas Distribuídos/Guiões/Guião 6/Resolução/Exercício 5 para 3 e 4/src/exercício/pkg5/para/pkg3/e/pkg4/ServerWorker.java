package exercício.pkg5.para.pkg3.e.pkg4;

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
public class ServerWorker implements Runnable {
    
    private final Socket socket;
    private final int id;
    
    public ServerWorker(Socket socket, int id){
        this.socket = socket;
        this.id = id;
    }
    
    @Override
    public void run(){
              
    try{
        BufferedReader in = new BufferedReader(new InputStreamReader(socket.getInputStream()));
        BufferedWriter out = new BufferedWriter(new OutputStreamWriter(socket.getOutputStream()));
        
        int somaNumeros = 0;
        int mediaNumeros = 0;
        int quantidadeNumeros = 0;
        
        String line;
        
        while( (line = in.readLine()) != null ){
            
            int numeroCliente = Integer.parseInt(line);
            
            somaNumeros = somaNumeros + numeroCliente;
            quantidadeNumeros++;
            
            String somaAtual = String.valueOf(somaNumeros);
            out.write(somaAtual);
            out.newLine();
            out.flush();  
        }
        
        mediaNumeros = somaNumeros/quantidadeNumeros;
        String mediaFinal = String.valueOf(mediaNumeros);
        out.write(mediaFinal);
        out.newLine();
        out.flush();
        
        socket.shutdownInput();
        socket.shutdownOutput();
        socket.close();
        
    } catch(IOException e){}
    }
}
