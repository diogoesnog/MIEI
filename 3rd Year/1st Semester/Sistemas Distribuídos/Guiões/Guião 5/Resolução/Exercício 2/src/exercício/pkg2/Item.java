package exercício.pkg2;

import java.util.concurrent.locks.Condition;
import java.util.concurrent.locks.ReentrantLock;

public class Item {

    ReentrantLock lock;
    Condition isEmpty;

    private int quantidade;

    public Item(){
	this.quantidade = 0;
	this.lock = new ReentrantLock();
	this.isEmpty = this.lock.newCondition();
    }

    public void aumentaCapacidade(int quantidade){
	lock.lock();
        try {
            this.quantidade += quantidade;
            isEmpty.signalAll();
        } finally {
            lock.unlock();
        }
    }

    public void consomeQuantidade(){
	lock.lock();

        try {
            while(quantidade == 0){
		System.out.println("Não existem unidades para consumir. Foi feio o bloqueio.");
		isEmpty.await();
            }
	
            this.quantidade--;
            
	} catch (InterruptedException e) {}
	finally{
            lock.unlock();
	}
    }
}
