package aula1;

public class Seq {

    public static void main(String[] args) throws Exception {
        Tarefa[] t = new Tarefa[10];
        for(int i=0;i<t.length;i++)
            t[i] = new Tarefa();

        for(int i=0;i<t.length;i++)
            t[i].run();

        System.out.println("resultado = "+Tarefa.c);
    }
    
}
