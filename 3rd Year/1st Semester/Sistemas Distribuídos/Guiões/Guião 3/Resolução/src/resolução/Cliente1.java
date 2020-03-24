package resolução;

/**
 *
 * @author Diogo Nogueira
 */
public class Cliente1 implements Runnable {
    
    private final Banco banco;

    public Cliente1(Banco novoBanco){
        this.banco = novoBanco; 
    }

    @Override
    public void run() {
        banco.fecharConta(0);
        
    }  
}