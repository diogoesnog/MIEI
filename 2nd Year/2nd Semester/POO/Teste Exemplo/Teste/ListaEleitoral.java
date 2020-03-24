 import java.util.Set;
import java.util.List;
import java.util.ArrayList;
import java.util.Map;
import java.util.HashMap;
import java.util.Iterator;
import java.util.Collection;
import java.util.TreeSet;

/** 
 * Classe ListaEleitoral.
 * 
 * @author Diogo Nogueira.
 * @version 27.05.2017.
 */

public class ListaEleitoral
{
    /** Variaveis de Instancia. */
    private String partidoPolitico;
    private Set<Candidato> eleitos;
    private List<Candidato> porEleger;
    
    /** Metodos Pedidos. */
    
    // PARTE I
    
    /** Construtor inicial que cria uma lista com os candidatos a serem eleitos. */
    public ListaEleitoral(String partido, Collection<Candidato> candidatos) {
        this.partidoPolitico = partido;
        this.porEleger = new ArrayList<>();
        
        for(Candidato e: candidatos){porEleger.add(e.clone());}
    }
    
    /** Metodo que devolve o proximo candidato a eleger. */
    public Candidato aElegerV1() throws NoMoreCandidatosException {
        Iterator<Candidato> it = porEleger.iterator();
        Candidato c = it.next();
        if(it.hasNext()) return c;
        else throw new NoMoreCandidatosException("Nao tem mais candidatos a eleger.");
    }
    public Candidato aElegerV2() throws NoMoreCandidatosException {
        Candidato c = this.porEleger.get(0);
        if(c != null) {return c.clone();}
        else throw new NoMoreCandidatosException("Nao tem mais candidatos a eleger.");
    }
    
    /** Metodo que elege o proximo candidato (caso ainda existam candidatos por eleger). */
    public void elege() throws NoMoreCandidatosException {
        Iterator<Candidato> it = porEleger.iterator();
        Candidato c = it.next();
        
        if(it.hasNext()) eleitos.add(c.clone());
        else throw new NoMoreCandidatosException("Nao tem mais candidatos a Eleger.");
    }
    
    /** Metodo que elege n candidatos se possivel, caso contrario, deixa a lista inalterada. */
    public void elege(int n) throws NotEnoughCandidatosException {
        if(n <= porEleger.size()){
            for(Candidato c: porEleger) eleitos.add(c.clone());}
            
        else throw new NotEnoughCandidatosException("Nao e possivel eleger " + n + " candidatos");
    }
    
    /** Metodo que devolve uma colecao com todos os candidatos do partido. */
    public Collection<Candidato> candidatos() {
        Collection<Candidato> candidatos = new ArrayList<>();
        
        for(Candidato e: eleitos) candidatos.add(e.clone());
        for(Candidato p: porEleger) candidatos.add(p.clone());
        
        return candidatos;
    }  
    
    // PARTE II
    
    /** Metodo que devolve todos os candidatos ja eleitos, segundo a ordem natual de Candidato. */
    public TreeSet<Candidato> eleitos(){
        TreeSet<Candidato> candidatos = new TreeSet<Candidato>();
        
        for(Candidato c: eleitos) candidatos.add(c.clone());
        
        return candidatos;
    }
    
    /** Metodo que devolve */
     public TreeSet<Candidato> candidatosOrd(){
        TreeSet<Candidato> candidatos = new TreeSet<Candidato>(new NomeComparator());
        for(Candidato c : eleitos){
            candidatos.add(c.clone());
        }
        return candidatos;
    }
    
       
    /** Metodo que devolve um TreeSet em que os candidatos estao ordenados primeiro por idade e so depois por nome, se a sua idade for igual. */
    public TreeSet<Candidato> candidatosOrd1(){
        TreeSet<Candidato> candidatos = new TreeSet<Candidato>(new IdadeNomeComparator());
        for(Candidato c : eleitos){
            candidatos.add(c.clone());
        }
        return candidatos;
    }
}