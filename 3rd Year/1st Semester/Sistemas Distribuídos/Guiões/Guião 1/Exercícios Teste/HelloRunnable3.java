public class HelloRunnable3 implements Runnable {
    
    int num;

    public void run(){
        System.out.println(num);
        num=111;
    }

    HelloRunnable3(int arg){
        num=arg;
    }

    public static void main(String args[]) {
        /* 
        A diferença aqui foi que se criou duas Threads com o mesmo objeto
        Desta forma o thread começa com o argumento sendo 222, mas a meio do thread o computador tentou trocar o num para 111.
        Assim as opções possíveis seriam imprimir
        222
        111 (dado que o 1º thread imprime o arg 222 e muda para 111. quando o outro thread já corre o run o arg já é 111 e imprime 111)
        e
        222
        222 (dado que um thread imprimia o arg 222 e antes de esse thread mudar o arg para 111, já tinha entrado o segundo thread e imprime 222 também antes de ter trocado)
        */
        HelloRunnable3 r = new HelloRunnable3(222);
        Thread t1 = new Thread(r);
        Thread t2 = new Thread(r);
        System.out.println("Antes");
        t1.start();
        t2.start();
        System.out.println("Depois");
        try {
            t2.join();
            t1.join();
        } catch (InterruptedException e) {}
        System.out.println("Fim");
    }
}