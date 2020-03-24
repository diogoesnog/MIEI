package common;

import java.util.Objects;

public class Pair<X,Y> {
    private X fst;
    private Y snd;

    public Pair(X fst, Y snd) {
        this.fst = fst;
        this.snd = snd;
    }

    public int hashCode() {
        int hashFst = fst != null ? fst.hashCode() : 0;
        int hashSnd = snd != null ? snd.hashCode() : 0;

        return (hashFst + hashSnd) * hashSnd + hashFst;
    }

    public boolean equals(Object o) {
        if (o instanceof Pair) {
            Pair p = (Pair) o;
            return Objects.equals(this.fst, p.fst) && Objects.equals(snd, p.snd);
        }
        return false;
    }

    public String toString() {
        return "(" + fst + ", " + snd + ")";
    }

    public X getFst() {
        return fst;
    }

    public void setFst(X fst) {
        this.fst = fst;
    }

    public Y getSnd() {
        return snd;
    }

    public void setSecond(Y snd) {
        this.snd = snd;
    }
}