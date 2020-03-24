package exercício.pkg4.tentativa.pkg2;

/**
 *
 * @author Diogo Nogueira
 */
public class Main {

    /**
     * @param args the command line arguments
     */
    public static void main(String[] args) {
        
        Banco b = new Banco(10);
        b.depositar(0, 1000);

        Thread t1=new Thread(new Cliente1(b));
        Thread t2=new Thread(new Cliente2(b));
		
        t1.start();
        t2.start();
		
        try {
            t1.join();
            t2.join();
	} catch (InterruptedException e) {}    
    }
    
}
