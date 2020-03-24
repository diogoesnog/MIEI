package aula1;

public class Tarefa implements Runnable {
    public static long c;

    public void run() {
        System.out.println("Antes "+this);
        // faz de conta...
        for(int i=0; i<1000000000; i++)
            c++;
        System.out.println("Depois "+this);
    }
}
