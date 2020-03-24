package exercício.pkg4.tentativa.pkg1;

/**
 *
 * @author Diogo Nogueira
 */
public class Banco {
    
    private Conta[] contasBancarias;
	
    public Banco(int n){    
        contasBancarias = new Conta[n];
       
        for(int i=0; i<n; i++)
        contasBancarias[i] = new Conta();	
    }
	
    public double consultar(int numeroConta){
        return this.contasBancarias[numeroConta].consultar();
    }
	
    public void levantar(int nr_conta, double valor){
        this.contasBancarias[nr_conta].levantar(valor);
    }
	
    public void depositar(int numeroConta, double quantia){
        this.contasBancarias[numeroConta].depositar(quantia);
    }
	
    public void transferir(int contaOrigem, int contaDestino, double quantia){
		
        this.contasBancarias[contaOrigem].levantar(quantia);
		
	// Sleep para simular período de tempo entre aquisição dos dois locks.
	try{ Thread.sleep(100);}catch (InterruptedException e) {}
		
	this.contasBancarias[contaDestino].depositar(quantia);
    }
    
}
