public class Main {

	public static void main(String[] args) {

		int numContas = 2;

		// Cada Cliente tem apenas 2 contas (valor fixo como dito no enunciado).
		Banco b = new Banco(numContas);
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
		
		// Prints aleatórios.
		System.out.println("Valor final da Conta 0 é: " + b.consultaSaldo(0));
	}
}
