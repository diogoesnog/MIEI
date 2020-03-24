public class Main {
    
    public static void main(String args[]) {

        // Estamos a definir que existirão 3 Threads e que cada uma vai escrever até ao número 5 no ecrã.
        int numeroThreads = 3;
        int maximo = 5;

        // Estamos a definir que existirá um conjunto (array) de Threads.
        Thread threads[] = new Thread[numeroThreads];

        // Estamos a criar as 3 Threads e a executar cada uma delas (start).
        // Uma Thread tem de receber o objeto da Classe que tem implementado o método run.
        for (int th = 0; th < numeroThreads; th++) {
            threads[th] = new Thread(new Run(maximo));
            threads[th].start();
        }
        
        // Também é preciso fechar a execução de cada uma das Threads (join).
        for (int th = 0; th < numeroThreads; th++) {
            try {
                threads[th].join();
            } catch (InterruptedException e) {}
        }
    }
}
