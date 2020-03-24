package exercício.pkg4.tentativa.pkg1;

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
        System.out.println("O saldo da Conta 1 é " + this.banco.consultar(1));		
    }
    
}
