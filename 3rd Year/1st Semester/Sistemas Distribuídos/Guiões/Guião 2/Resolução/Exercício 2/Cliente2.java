public class Cliente2 implements Runnable {
	
	private Banco banco;

	public Cliente2 (Banco bancoCliente) {
		this.banco= bancoCliente; 
	}
	
	public void run() {
		int i;

		// Levanta 5 euros da conta 0.
		for(i=0; i<5; i++){
			this.banco.levantaSaldo(0,1);
			System.out.println(Thread.currentThread().getName() + ": Foi levantado 1 EUR da sua conta. O saldo atual é: " + banco.consultaSaldo(0) + "\n");
		}	
	} 

}