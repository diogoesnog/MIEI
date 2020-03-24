package sd;

public class Counter {
    private int value = 0;
    private Lock l;

    public int incr() {

        try {
            l.lock();
            int temp = value;
            value = temp + 1;
            return temp;
        } finally {
            l.unlock();
        }

    }
}
