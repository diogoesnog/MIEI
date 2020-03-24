package exercício.pkg3;

/**
 *
 * @author Diogo Nogueira
 */
public class Barreira {
    
    private int maximoThreads;
    private int threadsNaBarreira;
    private int contadorEtapa;
    
    public Barreira(int maximoThreads){
        this.maximoThreads = maximoThreads;
        this.threadsNaBarreira = 0;
        this.contadorEtapa = 0;
    }
    
    public synchronized void esperar() throws InterruptedException{
        
        this.threadsNaBarreira++;
        int etapaAtual = this.contadorEtapa;
        
        if(this.threadsNaBarreira == maximoThreads){
            this.notifyAll();
            System.out.println("Acabou de se acordar todas as Threads em espera.");
            this.contadorEtapa++;
            this.threadsNaBarreira = 0;
        }
        /** É necessário fazermos a contagem da etapa. Assim garantimos que 
         * 
         */
        else while(etapaAtual == this.contadorEtapa){
            this.wait();
        }
    }
}
