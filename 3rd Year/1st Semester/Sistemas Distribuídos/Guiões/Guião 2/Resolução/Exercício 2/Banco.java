public class Banco {

	// Um Banco possui então um array do conjunto das suas contas bancárias.
	private double[] contasBancarias;
	
	// Este método possibilita que na Main ao passarmos o número de contas (fixo) se criem todas 
	// elas com um saldo inicial de 0.
	public Banco (int numContas) {

		contasBancarias = new double[numContas];

		for(int i = 0; i < numContas; i++) {
			contasBancarias[i] = 0;
		}
	}	
	
	// Para consultar o saldo não é necessário existir uma sincronização.
	public double consultaSaldo(int numConta) {
		return this.contasBancarias[numConta];
	}
	
	// Apesar de neste exercício não ser assim tão necessário, coloca-se o método como sendo synchronized.
	public synchronized void levantaSaldo(int numConta, double valor) {
		this.contasBancarias[numConta] = this.contasBancarias[numConta] - valor;
	}	
	
	// Apesar de neste exercício não ser assim tão necessário, coloca-se o método como sendo synchronized.
	public synchronized void depositaSaldo(int numConta, double valor) {
		this.contasBancarias[numConta] = this.contasBancarias[numConta] + valor;
	}
}
