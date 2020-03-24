/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package exercício.pkg5.para.pkg1.e.pkg2;

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
public class ServerWorker implements Runnable{
    
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
        
        String line;
        
        while( (line = in.readLine()) != null ){
            out.write(line);
            out.newLine();
            out.flush();
        }
	
        socket.shutdownOutput();
	socket.shutdownInput();
	socket.close();
    } catch(IOException e){}
    }
}
