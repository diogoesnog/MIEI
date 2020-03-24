
import java.io.BufferedReader;
import java.io.BufferedWriter;
import java.io.IOException;
import java.io.ObjectInputStream;
import java.io.ObjectOutputStream;
import java.net.Socket;

public class Cliente {

    private Socket socket;
    private BufferedReader in;
    private BufferedWriter out;

    public Cliente(String hostname, int porto){
        this.socket = new Socket(hostname,porto);
        this.in = new BufferedReader(new ObjectInputStream(socket.getInputStream()));
        this.out = new BufferedWriter(new ObjectOutputStream(socket.getOutputStream()));
    }

    public int criarConta(double saldoConta){
        
        int idConta = 0;

        out.write("Criar Conta");
        out.writeDouble(saldoConta);
        out.flush();

        idConta = in.readInt();

        return idConta;
    }

    public int fecharConta(int idConta){

        int idContaResultado = 0;

        out.write("Fechar Conta");
        out.writeInt(idConta);
        out.flush();

        idContaResultado = in.readInt();

        return idContaResultado;
    }

    public double consultar(int idConta){

        double saldoConta;

        out.write("Consultar Saldo");
        out.writeInt(idConta);
        out.flush();

        saldoConta = in.readDouble();

        return saldoConta;
    } 

    public void levantar(int idConta, double quantia){

        out.write("Levantar");
        out.writeInt(idConta);
        out.writeDouble(quantia);
        out.flush();
    }

    public void depositar(int idConta, double quantia){
        
        out.write("Depositar");
        out.writeInt(idConta);
        out.writeDouble(quantia);
        out.flush();  
    }

    public void transferir(int idContaOrigem, int idContaDestino, double quantia){

        out.write("Transferir");
        out.writeInt(idContaOrigem);
        out.writeInt(idContaDestino);
        out.writeDouble(quantia);
        out.flush();          
    }

    public void closeSocket(){
        socket.shutdownInput();
        socket.shutdownOutput();
        socket.close();
    }
}