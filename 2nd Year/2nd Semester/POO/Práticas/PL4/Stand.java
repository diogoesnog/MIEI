import java.lang.String;
import java.util.Arrays;
import java.util.ArrayList;

/**
 * Classe que representa um Stand de automóveis atraves de um ArrayList.
 * 
 * @author Diogo Nogueira.
 * @version 27.05.2017
 */

public class Stand
{
    /** Variáveis de Instância.*/
  
    private String nomeStand;
    private ArrayList<Veiculo> carros;
    private int nveiculos;
  
    private static final int capacidade_inicial = 10; // Valor por omissao.
  
    /** Construtores. */
  
    /** Construtor vazio da classe ArrayList. */
    public Stand() {
    this.nomeStand = new String();
    this.carros = new ArrayList <Veiculo>();
    }
  
    /** Construtor parametrizado da classe ArrayList. */
    public Stand(String nome, int capacidade) {
    this.nomeStand = nome;
    this.carros = new ArrayList<Veiculo>(capacidade);
    }
  
    /** Construtor de copia da classe Stand. */
    public Stand(Stand o) {
    this.nomeStand  = o.getNomeStand();
    this.carros = o.getCarros();
    }
  
    /** Métodos. */
    
    /** Métodos de Instância. -> Gets e Sets. */
    public String getNomeStand() {return nomeStand;}
    public ArrayList<Veiculo> getCarros(){
      ArrayList<Veiculo> novo = new ArrayList();
      
      for(Veiculo v: carros){novo.add(v.clone());} // Iterador implicito.
      return novo;
    }
    
    public void setNomeStand(String enome){
       this.nomeStand = enome;
    }
  
    /** Metodos Complementares. */
    public String toString() {
        String result = "";
        for (int i = 0; i < carros.size(); i++) {
            result = result + " " + carros.get(i);
        }
        return result;
    }
    public Stand clone() {return new Stand(this);}
    public boolean equals(Object o) {
        if (o == this) return true;
        if ((o == null) || (this.getClass() != o.getClass())) return false;
        
        Stand s = (Stand) o;
        
        return this.nomeStand.equals(s.getNomeStand());
    }
    

    /** Metodos Pedidos. */
  
    /** Método que insere um Veiculo no Stand. */
    public void insereVeiculo(Veiculo v) {
       if (!carros.contains(v)) {carros.add(v.clone());}
    }
         
    /** Método que verifica se um Veiculo, cuja matrícula é conhecida, esta na Stand. -> Nao esta a funcionar. */
    public boolean existeVeiculoPorMatricula(String matricula) {
        boolean resultado = false;
        
        for(int i=0; i< nveiculos; i++) {       
            if (carros.get(i).getMatricula().equals(matricula)) {resultado = true;}
            else resultado = false;
        }
        return resultado;
    }
  
    /** Método que determina o número de kms de todos os Veiculos da garagem. */
    public double totalKmsTodosVeiculos() {
        double soma=0;
        
        for(int i=0; i<nveiculos; i++) {soma = soma + carros.get(i).getKmTotais();}
            
        return soma;
    } 
   
    /** Método que devolve o Veiculo com mais kms. */
    public Veiculo veiculoComMaisKms() {
        double kms = 0;
        Veiculo v = new Veiculo();
      
        for(int i=0; i<nveiculos; i++){
            if(carros.get(i).getKmTotais() > kms){
                kms = carros.get(i).getKmTotais();
                v = carros.get(i);
            }
        }
        
        return v;
    }
    
    /** Método que devolve o Veiculo mais gastador (em termos de combustível). */
    public Veiculo veiculoMaisGastador() {
        double consumo=0;
        Veiculo v = new Veiculo();
        
        for(int i=0; i<nveiculos; i++){
            if(carros.get(i).getConsumoMedio() > consumo){
                consumo = carros.get(i).getConsumoMedio();
                v = carros.get(i);
            }
        }
        
        return v;
    }
}