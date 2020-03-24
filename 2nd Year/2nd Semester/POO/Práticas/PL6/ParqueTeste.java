
/**
 * Escreva a descrição da classe ParqueTeste aqui.
 * 
 * @author (seu nome) 
 * @version (número de versão ou data)
 */

import java.util.HashSet;

public class ParqueTeste
{
    public static void main(String[] args){
        Parque p1 = new Parque();
        HashSet<Parque> hs = new HashSet<>();
        Lugar l = new Lugar("a", "a", 10, true);
        
        p1.addLugar(l);
        p1.addLugar(new Lugar());
        hs.add(p1);
        System.out.println("OK? (1) "+hs.size());
        System.out.println("OK? (true) "+hs.contains(p1));
        
        hs.add(new Parque());
        hs.add(new Parque());
        System.out.println("OK? (2) "+hs.size());
        System.out.println("OK? (true) "+hs.contains(new Parque()));
        
        hs.forEach(p->System.out.println(p.toString()));
        
        System.out.println("Ordenado? "+p1.getLugaresPorTempo());
        
        p1.addLugar(new Lugar("b", "b", 10, true));
        System.out.println("OK? "+p1.getAgrupPorTempo());
    }
}