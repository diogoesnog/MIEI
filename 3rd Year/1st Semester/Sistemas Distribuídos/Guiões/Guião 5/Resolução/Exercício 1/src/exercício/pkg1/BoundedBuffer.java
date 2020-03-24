package exercício.pkg1;

import java.util.concurrent.locks.Condition;
import java.util.concurrent.locks.ReentrantLock;

/**
 *
 * @author Diogo Nogueira
 */
public class BoundedBuffer {
    
    private int[] valores;
    private int posicaoEscrever;
    ReentrantLock lock;
    Condition estaVazio;
    Condition estaCheio;
    
    public BoundedBuffer(int tamanhoBuffer){
        this.valores = new int[tamanhoBuffer];
        this.posicaoEscrever = 0;
        this.lock = new ReentrantLock();
        this.estaVazio = this.lock.newCondition();
        this.estaCheio = this.lock.newCondition();
    }
    
    public synchronized void put(int valor) throws InterruptedException{
        
        this.lock.lock();
        try {
            while(this.valores.length == this.posicaoEscrever){
                System.out.println("Buffer cheio. Esperar até existir espaço novamente.");
                this.estaCheio.await();
            }
            
            this.valores[posicaoEscrever] = valor;
            System.out.println("Valor colocado com sucesso.");
            posicaoEscrever++;
            
            this.estaVazio.signal();
        } finally {
            this.lock.unlock();
        }
    }
    
    public synchronized int get() throws InterruptedException{
        
        this.lock.lock();
        int resultado;
        
        try {
            while(this.posicaoEscrever == 0){
                System.out.println("Buffer vazio. Espere até ter elementos.");
                this.estaVazio.await();
            }
            
            resultado = this.valores[posicaoEscrever-1];
            this.posicaoEscrever--;
            System.out.println("Valor retirado com sucesso.");
            
            this.estaCheio.signal();
        } finally {
            this.lock.unlock();
        }
        
        return resultado;        
    }
}
