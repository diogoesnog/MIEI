/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package exercício.pkg3.e.pkg4;

import java.io.BufferedReader;
import java.io.BufferedWriter;
import java.io.IOException;
import java.io.InputStreamReader;
import java.io.OutputStreamWriter;
import java.net.Socket;
import java.util.logging.Level;
import java.util.logging.Logger;

/**
 *
 * @author Diogo Nogueira
 */
public class Cliente {
    
    private String hostname;
    private int porto;
    private Socket socket;
    
    public Cliente(String hostname, int porto){
        this.hostname = hostname;
        this.porto = porto;
    }
    
    public void iniciarCliente() throws IOException{
        
        // Criar o Socket para aquele porto.
        this.socket = new Socket(this.hostname,this.porto);
        
        // Criar canais de entrada e saída desse socket criado acima.
        BufferedReader in = new BufferedReader(new InputStreamReader(socket.getInputStream()));
        BufferedWriter out = new BufferedWriter(new OutputStreamWriter(socket.getOutputStream()));
        
        // Canal para ler do Cliente o que ele escrever.
        BufferedReader systemIn = new BufferedReader(new InputStreamReader(System.in));
        
        String inputCliente;
        String outputServer;
        
        // Enquanto o Cliente fornecer dados e não for igual a quit.
        while((inputCliente = systemIn.readLine()) != null && !inputCliente.equals("quit")){
            
            // Enviamos para o canal de saída do Cliente esse valor. 
            // O canal de entrada do Servidor vai ler.
            int valor = Integer.valueOf(inputCliente);
            out.write(valor);
            out.newLine();
            out.flush();
            
            // Vai buscar a resposta do Servidor que será a soma dos números.
            outputServer = in.readLine(); 
        }  
           // Assim que o Cliente pretende encerrar a conexão fecha o canal de saida dele mesmo.
           // Recebe então a sua média e fecha o canal de entrada também.
           socket.shutdownOutput();
           outputServer = in.readLine();
           socket.shutdownInput();
           socket.close();          
    }
    

    public static void main(String[] args) {
	Cliente cliente = new Cliente("127.0.0.1",12345);
        try {
            cliente.iniciarCliente();
        } catch (IOException ex) {
            Logger.getLogger(Cliente.class.getName()).log(Level.SEVERE, null, ex);
        }
    }
}
