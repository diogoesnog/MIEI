package sd;

public class LockFilter implements Lock {

    int[] flags;
    int[] victim;

    private boolean alone(int i, int l) {
        for(int j=0; j<ThreadId.max(); j++) {
            if (j!=i && flags[j] >= l)
                return false;
        }
        return true;
    }

    public void lock() {
        for(int l=1; l<ThreadId.max(); l++) {
            int i = ThreadId.get(); // eu

            flags[i] = l;
            victim[l] = i;

            while(!alone(i,l) && victim[l] == i) {}
        }
    }

    public void unlock() {
        int i = ThreadId.get(); // eu
        flags[i] = 0;
    }
}
