package exercício.pkg4.tentativa.pkg2;

/**
 *
 * @author Diogo Nogueira
 */
public class Cliente2 implements Runnable {
    
    private Banco banco;

    public Cliente2(Banco novoBanco){
        this.banco = novoBanco; 
    }
	
    public void run() {
        // Transferir da Conta 1 para a Conta 0 o valor de 1000EUR.
        this.banco.transferir(1,0,1000);
        System.out.println("Acabou de ser transferido o valor de 1000EUR da Conta 1 para a Conta 0.");
    } 
    
}