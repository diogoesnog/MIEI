package exercício.pkg4.tentativa.pkg2;

/**
 *
 * @author Diogo Nogueira
 */
public class Cliente1 implements Runnable {
    
    private Banco banco;

    public Cliente1(Banco novoBanco){
        this.banco = novoBanco; 
    }
	
    public void run() {
        // Transferir da Conta 0 para a Conta 1 o valor de 1000EUR.
        this.banco.transferir(0,1,1000);
        System.out.println("Acabou de ser transferido o valor de 1000EUR da Conta 0 para a Conta1.");
    } 
    
}