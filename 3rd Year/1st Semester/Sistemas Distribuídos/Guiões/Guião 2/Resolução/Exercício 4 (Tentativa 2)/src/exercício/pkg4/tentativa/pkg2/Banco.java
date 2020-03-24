package exercício.pkg4.tentativa.pkg2;

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
	
    public synchronized double consultar(int numeroConta){
        return this.contasBancarias[numeroConta].consultar();
    }
	
    public synchronized void levantar(int nr_conta, double valor){
        this.contasBancarias[nr_conta].levantar(valor);
    }
	
    public synchronized void depositar(int numeroConta, double quantia){
        this.contasBancarias[numeroConta].depositar(quantia);
    }
    
    // Nesta segunda tentativa a ideia é fazer o synchronized ao nível dos métodos do Banco.
    // Continua com Deadlocks.
    // Cliente1 - Transferir da Conta0 (contaOrigem) para a Conta1 (contaDestino) o valor de 1000EUR.
    // Cliente2 - Transferir da Conta1 (contaOrigem) para a Conta2 (contaDestino) o valor de 1000EUR.
    // Adquirimos o lock da Conta0 (Origem Cliente1)
    // Entra o Cliente2 e adquirimos o lock da Conta1 (Origem Cliente2)
    // Continua o Cliente1 e pretende adquirir o lock da Conta1 (Destino Cliente1) - ERRO.
    // O lock da Conta1 já foi adquirido pelo Cliente2.
    
    public void transferir(int contaOrigem, int contaDestino, double quantia){
	
        synchronized(this.contasBancarias[contaOrigem]){
            synchronized(this.contasBancarias[contaDestino]) {
                this.contasBancarias[contaOrigem].levantar(quantia);		
                this.contasBancarias[contaDestino].depositar(quantia);
            }
        }
    }
}
