public class Run implements Runnable {
    
    private Counter contador;
    private int numeroIncrementos;

    public Run(Counter novoContador, int novoValor) {
        this.numeroIncrementos = novoValor;
        this.contador = novoContador;
    }

    public void run() {

        for (int i = 0; i <= numeroIncrementos; i++) {
        this.contador.increment();
        // this.contador.counter++;
        System.out.println(this.contador.getCounter());
    }
    }
}

