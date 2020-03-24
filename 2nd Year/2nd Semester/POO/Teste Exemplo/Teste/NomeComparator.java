import java.util.*;

public abstract class NomeComparator implements Comparator<Candidato> {
    public int compare(String nome1, String nome2){
        return nome1.compareTo(nome2);
    }
}

