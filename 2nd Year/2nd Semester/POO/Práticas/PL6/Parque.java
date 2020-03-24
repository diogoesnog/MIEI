import java.util.Map;
import java.util.HashMap;
import java.util.Set;
import java.util.Iterator;
import java.util.ArrayList;
import java.util.List;
import java.util.stream.Collectors;
import java.util.TreeSet;

/** 
 * Classe Parque.
 * 
 * @author Diogo Nogueira.
 * @version 27.05.2017
 */

public class Parque
{
   /** Variaveis de Instancia. */
   public String nome;
   private Map<String, Lugar> lugares;
   
   /** Construtores. */
   
   /** Construtor vazio da classe Parque. */
   public Parque(){
       this.nome = new String();
   }
   
   /** Construtor parametrizado da classe Parque. */
   public Parque(String nome){
       this.nome = nome;
       this.lugares = new HashMap<String, Lugar>();
   }
   public Parque(String nome, Map<String, Lugar> novo){
       this.nome = nome;
       
       this.lugares = new HashMap<String, Lugar>();
       
       for(Map.Entry<String, Lugar> e : novo.entrySet()){
           this.lugares.put(e.getKey(), e.getValue().clone());
       }
       
       /**
       for(String m: novo.keySet()){
           Lugar l = novo.get(m);
           this.lugares.put(m, l.clone());
       }
       
       for(Lugar l: novo.values()){
           this.lugares.put(l.getMatricula(), l.clone());
       }
       */
   }
      
   /** Construtor de copia da classe Parque. */
   public Parque(Parque o){
       this.nome = o.getNome();
       this.lugares = o.getLugares();
   }
   
   /** Metodos. */
   
   /** Metodos de Instancia. -> Gets e Sets. */
   public String getNome() {return this.nome;}
   public Map<String, Lugar> getLugares(){
       Map<String, Lugar> copia = new HashMap<>();
       
       for(Map.Entry<String, Lugar> e: lugares.entrySet()){
           copia.put(e.getKey(), e.getValue().clone());
       }
       
       return copia;
       
       //return lugares.entrySet().stream().collect(Collectors.toMap(e->e.getKey(),e->e.getValue().clone()));
   }
   
   public static void setNome(String nome){this.nome = nome;}
   
   /** Metodos Pedidos. */
   
   /** Método que devolve todas as matriculas dos lugares ocupados. */
   public Set<String> getMatriculas(){return this.lugares.keySet();}
   
   /** Metodo que adiciona um novo lugar. */
   public void addLugar(Lugar l){
       this.lugares.put(l.getMatricula(), l.clone());
   }
   
   /** Metodo que remove um lugar. */
   public void removeLugar(Lugar l){
       this.lugares.remove(l.getMatricula());
   }
   
   /** Método que altera o tempo disponível de um lugar, para uma dada matricula. */
   public void alteraTempo(String mat, int tempo){
       if(this.lugares.containsKey(mat)) 
           this.lugares.get(mat).setMinutos(tempo);   
   }
   
   /**  Método que devolve a quantidade total de minutos atribuídos. */
   
   /** Iterador externo. */
   public int totalMinutos(){
      int total = 0;
       
      for(Lugar l: this.lugares.values()){total += l.getMinutos();}
      
      return total;
   }
   /** Iterador interno. */
   public int totalMinutosF(){
       return this.lugares.values().stream().mapToInt(Lugar::getMinutos).sum();
   }
   
   /** Método que verifica se existe lugar atribuído a uma dada matrícula. */
   public boolean existe(String mat){
       return this.lugares.containsKey(mat);
   }
   
   //iterador externo
   public List<String> getPermanentes(int tempo){
       List<String> res = new ArrayList<String>();
       
       for(Lugar l: this.lugares.values()){
           if(l.getMinutos() > tempo && l.getPermanente())
                res.add(l.getMatricula());
       }
       
       return res;
   }
   
   //iterador interno
   public List<String> getPermanentesF(int tempo){
       return this.lugares.values().stream().filter(l -> l.getMinutos() > tempo && l.getPermanente()).map(Lugar::getMatricula).collect(Collectors.toList());
   }
   
   public TreeSet<Lugar> getLugaresPorTempo(){
       TreeSet<Lugar> res = new TreeSet<>();
       
       for(Lugar l: lugares.values()){
           res.add(l.clone());
       }
       
       return res;
   }
   
   public Map<Integer, List<Lugar>> getAgrupPorTempo(){
       Map<Integer, List<Lugar>> res = new HashMap<>();
       
       for(Lugar l: lugares.values()){
           if(!(res.containsKey(l.getMinutos()))){
              res.put(l.getMinutos(), new ArrayList<>()); 
           }
           res.get(l.getMinutos()).add(l.clone());
       }
       
       return res;
       
       //return this.lugares.values().stream().map(lugar::clone)-collect(Collectors.groupingBy(Lugar::getMinutos));
   }
   
   public Parque clone(){
       return new Parque(this);
   }
   
   public String toString(){
       StringBuilder sb = new StringBuilder("Parque(");
       sb.append(nome);
       sb.append(", ");
       sb.append(lugares.toString());
       sb.append(")");
       return sb.toString();
   } 
   
   public int hashCode(){
       return nome.hashCode();
   }
   
   public boolean equals(Object o){
       if(o == this) return true;
       if( o == null || o.getClass() != this.getClass()) return false;
       
       Parque p = (Parque) o;
       
       return this.nome.equals(p.getNome()) && this.lugares.equals(p.getLugares());
   }
}
