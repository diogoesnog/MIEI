public class Banco {

	private double[] contasBancarias;
	
	Banco(int numContas) {

		contasBancarias = new double[numContas];
		
		for(int i = 0; i < numContas; i++){
			contasBancarias[i] = 0;
		}	
	}
	
	public double consultaSaldo(int numConta){
		return this.contasBancarias[numConta];
	}
	
	public synchronized void levantaSaldo(int numConta, double valor) {
		this.contasBancarias[numConta] = this.contasBancarias[numConta] - valor;
	}	
	
	public synchronized void depositaSaldo(int numConta, double valor) {
		this.contasBancarias[numConta] = this.contasBancarias[numConta] + valor;
	}
	
	public synchronized void transfereSaldo(int contaOrigem, int contaDestino, double valor){
		this.levantaSaldo(contaOrigem,valor);
		this.depositaSaldo(contaDestino,valor);
	}
}
