package aula1;

public class Conc {
    public static void main(String[] args) throws Exception {
        Tarefa[] t = new Tarefa[10];
        Thread[] th = new Thread[t.length];

        for(int i=0;i<t.length;i++) {
            t[i] = new Tarefa();
            th[i] = new Thread(t[i]);
        }

        for(int i=0;i<t.length;i++)
            th[i].start(); // fork

        for(int i=0;i<t.length;i++)
            th[i].join(); // wait

        System.out.println("resultado = "+Tarefa.c);
    }
}
