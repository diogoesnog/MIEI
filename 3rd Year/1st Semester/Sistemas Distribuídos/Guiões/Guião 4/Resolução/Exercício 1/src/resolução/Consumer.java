package resolução;

import java.util.logging.Level;
import java.util.logging.Logger;

/**
 *
 * @author Diogo Nogueira
 */
public class Consumer implements Runnable {

    private BoundedBuffer buffer;

    public Consumer(BoundedBuffer buffer){
	this.buffer = buffer;
    }

    @Override
    public void run() {
	for(int i=0; i<12; i++){
            try { 
                this.buffer.get();
            } catch (InterruptedException ex) {
                Logger.getLogger(Consumer.class.getName()).log(Level.SEVERE, null, ex);
            }
	}
    } 
}
