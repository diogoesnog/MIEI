package resolução;

/**
 *
 * @author Diogo Nogueira
 */
public class Main {

    public static void main(String[] args) throws InterruptedException {
        
        Banco banco = new Banco();
        
        for(int i = 0; i < 2; i++){
            banco.criarConta(100);
        }
        
        Cliente1 cliente1 = new Cliente1(banco);
        Cliente2 cliente2 = new Cliente2(banco);
        
        Thread t1 = new Thread(cliente1);
        t1.setName("Cliente 1");
        
        Thread t2 = new Thread(cliente2);
        t2.setName("Cliente 2");
        
	t1.start();
	t2.start();
		
	try {
            t1.join();
            t2.join();
	} catch (InterruptedException e) {
	}
    }
}
