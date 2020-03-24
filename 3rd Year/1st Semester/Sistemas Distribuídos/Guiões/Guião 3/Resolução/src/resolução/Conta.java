package resolução;

import java.util.concurrent.locks.ReentrantLock;

/**
 *
 * @author Diogo Nogueira
 */
class Conta {
    
    private int idConta;
    private double saldoConta;
    private ReentrantLock lockConta;
    
    public Conta() {
        this.idConta = 0;
        this.saldoConta = 0.0;
        this.lockConta = new ReentrantLock();
    }
    
    public Conta(int id){
        this.idConta = id;
	this.saldoConta = 0;
	this.lockConta = new ReentrantLock();
    }
	
    public Conta(int id, double saldo){
	this.idConta = id;
	this.saldoConta = saldo;
	this.lockConta = new ReentrantLock();
    }

    public double consultar(){
	return this.saldoConta;
    }
	
    public void depositar(double valor){
    	this.saldoConta = this.saldoConta + valor;
    }
	
    public void levantar(double valor){
	this.saldoConta = this.saldoConta - valor;
    }
	
    public int getId(){
	return this.idConta;
    }
    
    public void lock(){
        this.lockConta.lock();
    }
    
    public void unlock(){
        this.lockConta.unlock();
    }
}
