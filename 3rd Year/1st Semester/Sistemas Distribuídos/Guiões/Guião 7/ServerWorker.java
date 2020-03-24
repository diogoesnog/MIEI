
import java.io.BufferedReader;
import java.io.BufferedWriter;
import java.io.IOException;
import java.io.ObjectInputStream;
import java.io.ObjectOutputStream;
import java.net.Socket;

import aula7ex1.Banco;

public class ServerWorker implements Runnable{

    private Socket socket;
    private Banco bancoCliente;

    public ServerWoker(Socket socket, Banco banco){
        this.socket = socket;
        this.bancoCliente = banco;
    }

    public void run(){

        try{

            BufferedReader in = BufferedReader(new ObjectInputStream(socket.getInputStream()));
            BufferedWriter out = BufferedWriter(new ObjectInputStream(socket.getOutputStream()));

            String opcao;

            while(true){

                double saldoConta = 0;
                int idConta = 0;
                double quantia = 0;

                opcao = in.readLine();

                switch(opcao){

                    case ("Criar Conta"):
                        saldoConta = in.readDouble();
                        idConta = bancoCliente.criarConta(saldoConta);
                        out.write(String.valueOf(idConta));
                        out.flush();
                        break;
                    
                    case ("Fechar Conta"):
                        idConta = in.readInt();
                        saldoConta = bancoCliente.fecharConta(idConta);
                        out.write(String.valueOf(idConta));
                        out.flush();
                        break;

                    case ("Consultar Saldo"):
                        idConta = in.readInt();
                        saldo = bancoCliente.consultar(idConta);
                        out.writeDouble(saldo);
                        out.flush();
                        break;

                    case ("Levantar"):
                        idConta = in.readInt();
                        quantia = in.readDouble();
                        bancoCliente.levantar(idConta, quantia);
                        out.write("Levantamento efetuado com sucesso.");
                        out.flush();
                        break;

                    case ("Depositar"):
                        idConta = in.readInt();
                        quantia = in.readDouble();
                        bancoCliente.depositar(idConta, quantia);
                        out.write("Depósito efetuado com sucesso.");
                        out.flush();
                        break;

                    case ("Transferir"): 
                        idConta = in.readInt();
                        int idContaDestino = in.readInt();
                        quantia = in.readDouble();
                        bancoCliente.transferir(idConta, idContaDestino, quantia);
                        out.write("Transferência efetuada com sucesso.");
                        out.flush();
                        break;
                    
                    default:
                        out.write("Opção Inválida.");
                        out.flush();

                }
            }

            socket.shutdownInput();
            socket.shutdownOutput();
            socket.close();
            
        } catch(IOException e){}
    }
}