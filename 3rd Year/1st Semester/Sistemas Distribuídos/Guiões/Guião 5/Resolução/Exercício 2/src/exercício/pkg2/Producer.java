package exercício.pkg2;

public class Producer implements Runnable {
		
    private Warehouse armazem;

    public Producer(Warehouse armazem){
	this.armazem = armazem;
    }
		
    @Override
    public void run() {
		
	this.armazem.supply("item1", 1);
	try {
            Thread.sleep(3000);
	} catch (InterruptedException e) {}
			
	this.armazem.supply("item2", 1);	
	try {
            Thread.sleep(3000);
	} catch (InterruptedException e) {}
			
	this.armazem.supply("item3", 1);				
    }
} 

