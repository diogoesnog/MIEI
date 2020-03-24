package exercício.pkg4.tentativa.pkg3;

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
    
    // Ao colocarmos esta restrição de contaNumeroMenor e contaNumeroMaior conseguimos evitar Deadlocks.
    // Garantimos ordem a nível das contas.
    // Cliente1 - Transferir da Conta0 (contaOrigem) para a Conta1 (contaDestino) o valor de 1000EUR.
    // Cliente2 - Transferir da Conta1 (contaOrigem) para a Conta2 (contaDestino) o valor de 1000EUR.
    // FUNCIONAMENTO
    // Cliente1 - Adquire lock Conta0 (contaNumeroMenor).
    // Cliente2 - Adquire lock Conta0 (contaNumeroMenor) - NAO CONSEGUE, LOGO A THREAD CLIENTE1 CONTINUA.
    // Cliente1 - Adquire lock Conta1 (contaNumeroMaior).
    // Cliente1 - Consegue terminar o seu trabalho e o Cliente2 prossegue com o seu.
        
    public void transferir(int contaOrigem, int contaDestino, double quantia){
        
        int contaNumeroMenor = Math.min(contaOrigem, contaDestino);
        int contaNumeroMaior = Math.max(contaOrigem, contaDestino);
	
        synchronized(this.contasBancarias[contaNumeroMenor]){
            synchronized(this.contasBancarias[contaNumeroMaior]) {
                this.contasBancarias[contaOrigem].levantar(quantia);		
                this.contasBancarias[contaDestino].depositar(quantia);
            }
        }
    }
    
}
