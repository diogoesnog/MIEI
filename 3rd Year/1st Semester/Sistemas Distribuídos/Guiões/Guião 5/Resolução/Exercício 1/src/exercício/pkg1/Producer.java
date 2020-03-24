package exercício.pkg1;

import java.util.logging.Level;
import java.util.logging.Logger;

/**
 *
 * @author Diogo Nogueira
 */
public class Producer implements Runnable {

    private BoundedBuffer buffer;

    public Producer(BoundedBuffer buffer){
	this.buffer = buffer;
    }

    @Override
    public void run() {
	for(int i=0; i<10; i++){
            try {	
                this.buffer.put(i);
            } catch (InterruptedException ex) {
                Logger.getLogger(Producer.class.getName()).log(Level.SEVERE, null, ex);
            }
	}				
    } 
}

