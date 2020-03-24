public class HelloRunnable2 implements Runnable {
    
    int num;

    public void run(){
        System.out.println(num);
    }

    HelloRunnable2(int arg){
        num=arg;
    }

    public static void main(String args[]) {
        HelloRunnable2 r222 = new HelloRunnable2(222);
        HelloRunnable2 r111 = new HelloRunnable2(111);
        Thread t1 = new Thread(r222);
        Thread t2 = new Thread(r111);
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