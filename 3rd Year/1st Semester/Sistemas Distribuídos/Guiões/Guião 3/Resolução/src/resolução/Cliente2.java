package resolução;

/**
 *
 * @author Diogo Nogueira
 */
public class Cliente2 implements Runnable {

    private final Banco banco;

    public Cliente2(Banco novoBanco){
	this.banco = novoBanco; 
    }

    @Override
    public void run() {
        banco.depositar(0,100);
    }

}
