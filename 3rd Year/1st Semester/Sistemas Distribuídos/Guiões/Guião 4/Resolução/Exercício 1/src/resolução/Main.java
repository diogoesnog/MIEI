package resolução;

/**
 *
 * @author Diogo Nogueira
 */
public class Main {

    public static void main(String[] args) {
		
	BoundedBuffer buffer = new BoundedBuffer(10);
        
	Thread t1 = new Thread(new Producer(buffer));
	Thread t2 = new Thread(new Consumer(buffer));
		
	t1.start();
	t2.start();
	
	try {
            t1.join();
            t2.join();
	} catch (InterruptedException e) {
	}
    }
}