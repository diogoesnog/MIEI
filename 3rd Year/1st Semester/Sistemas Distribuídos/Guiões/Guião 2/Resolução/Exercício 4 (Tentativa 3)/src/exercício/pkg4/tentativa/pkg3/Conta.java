package exercício.pkg4.tentativa.pkg3;

/**
 *
 * @author Diogo Nogueira
 */
public class Conta {
    
    private double total;
	
    public Conta(){
        this.total = 0;
    }

    public double consultar(){
        return this.total;
    }
	
    public void depositar(double quantia){
	this.total = this.total + quantia;
    }
	
    public void levantar(double quantia){
        this.total = this.total - quantia;
    }
    
}
