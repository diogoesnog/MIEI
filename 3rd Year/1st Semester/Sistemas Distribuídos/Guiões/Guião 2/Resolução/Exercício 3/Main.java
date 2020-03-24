public class Main {

	public static void main(String[] args) {
		
		Banco b = new Banco(5);
		
		Thread t1 = new Thread(new Cliente1(b));
		Thread t2 = new Thread(new Cliente2(b));
		
		t1.start();
		t2.start();
		
		try {
			t1.join();
			t2.join();
		} catch (InterruptedException e) {
			e.printStackTrace();
		}
	
		System.out.println("Valor Conta 0 é: " + b.consultaSaldo(0));
		System.out.println("Valor Conta 1 é: " + b.consultaSaldo(1));
	}

}
