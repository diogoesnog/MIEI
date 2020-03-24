public class Cliente2 implements Runnable {

	private Banco banco;

	public Cliente2(Banco b){
		this.banco = b; 
	}

	public void run() {
		// Levantar 1000EUR da Conta 1.
		this.banco.levantaSaldo(1,1000);
		System.out.println("O Cliente " + Thread.currentThread().getName() + " acabou de levantar 1000EUR da Conta 1.");		
	} 
}