package resolução;

/**
 *
 * @author Diogo Nogueira
 */
public class BoundedBuffer {
    
    private int[] valores;
    private int posicaoEscrever;
    
    public BoundedBuffer(int tamanhoBuffer){
        this.valores = new int[tamanhoBuffer];
        this.posicaoEscrever = 0;
    }
    
    public synchronized void put(int valor) throws InterruptedException{
        
        while(this.valores.length == this.posicaoEscrever){
            System.out.println("Buffer cheio. Esperar até existir espaço novamente.");
            this.wait();
        }
        
        this.valores[posicaoEscrever] = valor;
        System.out.println("Valor colocado com sucesso.");
        posicaoEscrever++;
        
        this.notifyAll();
    }
    
    public synchronized int get() throws InterruptedException{
        
        while(this.posicaoEscrever == 0){
            System.out.println("Buffer vazio. Espere até ter elementos.");
            this.wait();
        }
        
        int resultado = this.valores[posicaoEscrever-1];
        this.posicaoEscrever--;
        System.out.println("Valor retirado com sucesso.");
        
        this.notifyAll();
        
        return resultado;        
    }
}
