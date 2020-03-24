package sd;

public class LockOne implements Lock {
    boolean[] flags = new boolean[2];
    int victim;

    public void lock() {
        int i = ThreadId.get(); // eu
        flags[i] = true;

        int j = 1-i; // o outro

        victim = i;

        while(flags[j] && victim == i) {}

    }

    public void unlock() {
        int i = ThreadId.get(); // eu
        flags[i] = false;
    }
}
