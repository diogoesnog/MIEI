public class Main {

public static void main (String[] args) {

    // Estamos a definir que existirão 3 Threads e que cada uma vai incrementar I vezes um certo contador
    // que será um objeto de uma classe Counter.
    int numeroThreads = 5;
    int numeroIncrementos = 20;

    Thread[] arrayThreads = new Thread[numeroThreads];

    Counter contador = new Counter();
    Run programa = new Run(contador,numeroIncrementos);

    for (int i = 0; i < numeroThreads; i++) {
        arrayThreads[i] = new Thread(programa);
        arrayThreads[i].start();
    }

    for (int i = 0; i < numeroThreads; i++) {
        try {
            arrayThreads[i].join();
        }
        catch (InterruptedException e) {}
    }

}
}



