import java.util.Map;
import java.util.HashMap;
import static java.util.stream.Collectors.toList;
import java.util.List;
import java.util.ArrayList;
import java.util.Set;

/**
 * Classe HoteisInc.
 * 
 * @author Diogo Nogueira.
 * @version 27.05.2017
 */

public class HoteisInc
{
   /** Variaveis de Instancia. */
   private String nome;
   private Map<String, Hotel> hoteis;
   
   /** Construtores. */
   
   /** Construtor vazio da classe HoteisInc. */
   public HoteisInc(){
       this.nome = new String();
       this.hoteis = new HashMap<String,Hotel>();
   }
   
   /** Construtor de copia da classe HoteisInc. */
   public HoteisInc(HoteisInc h){
       this.nome = h.getNome();
       this.hoteis = h.getHoteis();
   }
   
   /** Construtor parametrizado da classe HoteisInc. */
   public HoteisInc(String enome, Map<String,Hotel> h){
       this.nome = enome;
       this.hoteis = new HashMap<String,Hotel>();
       
       for(Map.Entry<String,Hotel> e: h.entrySet()){
           this.hoteis.put(e.getKey(), e.getValue().clone());
       }
   }
   public HoteisInc(String nome){
       this.nome = nome;
       this.hoteis = new HashMap<String,Hotel>();
   }
   
   /** Metodos. */
   
   /** Metodos de Instancia. -> Gets e Sets. */
   public String getNome() {return this.nome;}
   public Map<String, Hotel> getHoteis() {
       Map<String, Hotel> novo = new HashMap<>();
       
       for(Map.Entry<String, Hotel> e: hoteis.entrySet()){
           novo.put(e.getKey(), e.getValue().clone());
        }
        
       return novo;
   }
   
   public void setNome(String nome){
       this.nome = nome;
   }
   
   /** Metodos Complementares. */
   public HoteisInc clone(){return new HoteisInc(this);}
   public boolean equals(Object o){
       if(this == o) return true;
       if((o == null) || (this.getClass() != o.getClass())) return false;
       
       HoteisInc hotel = (HoteisInc) o;
       
       return (this.nome.equals(hotel.getNome()) && this.hoteis.equals(hotel.getHoteis()));
   }
   
   /** Metodos pedidos. */
   
   /** Metodo que verifica a existencia de um hotel. */
   public boolean existeHotel(String codigo){
       return this.hoteis.containsKey(codigo);
    }
   
   /** Metodo que devolve a quantidade de hoteis existentes na cadeia. */
   public int quantos(){
       return this.hoteis.size();
   }
   
   /** Metodo que devolve o numero total de hoteis de uma dada localidade. */
   public long quantos(String loc){
       int quantidade = 0;
       for(Hotel l: hoteis.values()) {
           if (l.getLocalidade().equals(loc)) quantidade++;
       }
       return quantidade;
   }
      
   /**
    * Devolve a ficha de um hotel atraveś do seu código
    */
   public Hotel getHotel(String cod) throws HotelNaoExisteException{
       if(!hoteis.containsKey(cod)) throw new HotelNaoExisteException("Hotel "+cod+" não existe");
       
       return this.hoteis.get(cod).clone();
   }
   
   /** Metodo que adiciona a informacao de um novo Hotel. */
   public void adiciona(Hotel h){
      //if(this.hoteis.containsKey(h.getCodigo()))      
      this.hoteis.put(h.getCodigo(), h.clone());
   }
   
   /** Metodo que devolve uma lista contendo a copia de todos os hoteis no sistema. */
   public List<Hotel> getListHoteis(){
       List<Hotel> novo = new ArrayList<Hotel>();
       
       for(Hotel l: hoteis.values()) {novo.add(l.clone());}
       
       return novo;
   }
   
   /**
    * Adiciona a informação de um conjunto de hoteis
    */
   public void adiciona(Set<Hotel> hs){
       hs.forEach(h->this.adiciona(h));
   }
   
   /**
    * Altera o estado da época de todos os HotelStandard
    */
   public void mudaPara(boolean epoca){
       for(Hotel h: hoteis.values()){
           if(h instanceof HotelStandard){
               HotelStandard hs = (HotelStandard) h;
               hs.setEpocaAlta(epoca);
            }
        }
   }
   
   public List<CartaoPonto> daoPontos(){
       return this.hoteis.values().stream().filter(h -> h.getClass().getSimpleName().equals("CartaoPonto")).map(h -> (CartaoPonto) h).collect(toList());
   }
}