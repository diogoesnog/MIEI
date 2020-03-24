package exercício.pkg4.tentativa.pkg1;

/**
 *
 * @author Diogo Nogueira
 */
public class Conta {
    
    private double total;
	
    Conta(){
        this.total = 0;
    }

    // A ideia nesta primeira tentativa é fazer o Lock ao nível das Contas individuais.
    // Surge o problema dos Deadlocks. 
    // No nosso código temos que o Cliente1 transfere da Conta0 para a Conta1 o valor de 1000EUR.
    // O Cliente2 consulta o saldo da Conta1.
    
    // Estamos a dar o lock nas Contas. O método transferir é composto pelo levantar e depositar.
    // Inicialmente é dado o Lock da Conta0 e levanta-se da Conta0 os 1000EUR.
    // Depois o Cliente2 pode dar o lock da Conta1 e consultar e neste momento ainda não foi feito o depósito na Conta1.
    // Ou seja, teria de ter exisitido o depóisito na Conta1 dos 1000EUR que foram retirado da Conta0.
    // Isto surge porque o método transferir que engloba o levantar e depositar não é synchronized.
    // Ou seja, as Threads podem não têm uma ordem para exectuar esses dois métodos individualmente.
    
    
    public synchronized double consultar(){
        return this.total;
    }
	
    public synchronized void depositar(double quantia){
	this.total = this.total + quantia;
    }
	
    public synchronized void levantar(double quantia){
        this.total = this.total - quantia;
    }
    
}
