import java.util.*;

public abstract class IdadeNomeComparator implements Comparator<Candidato>{
    public int compare(Candidato c1, Candidato c2){
        String nome1 = c1.getNome();
        String nome2 = c2.getNome();
        int idade1 = c1.getIdade();
        int idade2 = c2.getIdade();
        
        if(idade1 < idade2){return 1;}
        if(idade1 > idade2){return -1;}
        if(idade1 == idade2){
            if(c1.getNome().equals(c2.getNome())){return 0;}
            if( !(c1.getNome().equals(c2.getNome()))){
                return c1.getNome().compareTo(c2.getNome());
            }
        } return 1;
    }
}
