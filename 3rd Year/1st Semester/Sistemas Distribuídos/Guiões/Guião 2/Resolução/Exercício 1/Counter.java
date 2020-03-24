public class Counter {

    public int contador;

    public Counter() {
        this.contador = 0;
    }

    // Método Synchronized
    public synchronized void increment1() {
        System.out.println("A " + Thread.currentThread().getName() + " possui o sguinte valor de contador atual" + ": " + contador);
        this.contador++;
        System.out.println("A " + Thread.currentThread().getName() + " acabou de incrementar. Valor atual" + ": " + contador + "\n");
    }

    // Bloco Synchronized
    public void increment2() {
        synchronized(this) {
            this.contador++;
        }
    }

    public int getCounter() {
        return this.contador;
    }
}