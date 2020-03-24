package exercício.pkg2;

public class Consumer implements Runnable {
	
    private Warehouse armazem;

    public Consumer(Warehouse armazem){
	this.armazem = armazem;
    }
	
    @Override
    public void run() {
	String[] items={"item1","item2","item3"};
	armazem.consume(items);
    } 
}
