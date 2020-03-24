public class Cliente1 implements Runnable {

	private Banco banco;

	public Cliente1(Banco b){
		this.banco = b; 
	}

	public void run() {
		// Transferir 1000EUR da Conta 0 para a Conta 1.
		this.banco.depositaSaldo(0,1000);
		System.out.println("O Cliente " + Thread.currentThread().getName() + " acabou depositar 1000EUR na Conta 0.");
		this.banco.transfereSaldo(0,1,1000);
		System.out.println("O Cliente " + Thread.currentThread().getName() + " acaboy de transferir 1000EUR para a Conta 1.");	
	} 

}
