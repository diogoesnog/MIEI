public class Cliente1 implements Runnable {
	
	private Banco banco;

	public Cliente1 (Banco bancoCliente) {
		this.banco = bancoCliente; 
	}
	
	public void run() {
		int i;
		
		// Deposita 5 euros na conta 0.
		for(i=0; i<5; i++){
			this.banco.depositaSaldo(0,1);
			System.out.println(Thread.currentThread().getName() + ": Foi depositado 1 EUR na sua conta. O saldo atual é: " + banco.consultaSaldo(0) + "\n");
		}
	}
	 
}
