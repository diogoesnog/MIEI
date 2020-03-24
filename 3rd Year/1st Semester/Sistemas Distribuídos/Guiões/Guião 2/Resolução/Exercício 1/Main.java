public class Main {

public static void main (String[] args) {

    Counter contador = new Counter();
    Run programa = new Run(contador,3);

    // Estamos apenas a criar 2 Threads para perceber e simplificar a execução do programa.
    Thread thread1 = new Thread(programa);
    Thread thread2 = new Thread(programa);

    thread1.start();
    thread2.start();

    try {
        thread1.join();
        thread2.join();
    }
    catch (InterruptedException e) {}

    System.out.println("O contador tem o valor: " + contador.getCounter());

}
}



