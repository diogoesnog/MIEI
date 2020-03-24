import java.util.Arrays;

/**
 * Classe que representa um Stand de automóveis atraves de um Array.
 * 
 * @author Diogo Nogueira.
 * @version 27.05.2017
 */



public class GrowingArray
{
    /** Variáveis de Instância.*/
    
    private Veiculo[] veiculos;
    private int size;
    
    private static final int capacidade_inicial = 20; // Valor por omissao.
    
    public int size() {return this.size;}
   
    
    /** Construtores. */
         
    /** Construtor vazio da classe Growing Array. */
    public GrowingArray(){
        this(GrowingArray.capacidade_inicial);
    }
    
    /** Construtor parametrizado da classe GrowingArray. */
    public GrowingArray(int capacidade){
        this.veiculos = new Veiculo[capacidade];
        this.size = 0;
    }
    
    /** Metodos. */
    
    /** Metodos de Instancia. -> Gets e Sets. */
    public Veiculo get(int indice){
        if(indice < size) {return this.veiculos[indice];}
        else return null;
    }
    
    public void set(int indice, Veiculo v){
        if(indice < this.size) {this.veiculos[indice] = v;}
    }
    
    /** Metodos Pedidos. */
    public void add(Veiculo v){
        aumentaCapacidade(this.size + 1);
        this.veiculos[this.size++] = v;
    }
    private void aumentaCapacidade(int capacidade){
        if(capacidade > this.veiculos.length){
            int nova_capacidade = this.veiculos.length + 1;
            this.veiculos = Arrays.copyOf(this.veiculos, nova_capacidade);
        }
    }
    
    public void add(int indice, Veiculo v){
        if(indice < this.size){
            aumentaCapacidade(this.size + 1);
            System.arraycopy(this.veiculos, indice, this.veiculos, indice+1, this.size - indice);
            this.veiculos[indice] = v;
            this.size++;
        }
    }
    
    public Veiculo remove(int indice){
        if(indice < this.size){
            Veiculo v = this.veiculos[indice];
            Veiculo[] novo = new Veiculo[size-1];
            
            int deslocamento = this.size - indice - 1;
            
            if(deslocamento > 0)
                System.arraycopy(this.veiculos, indice+1, novo, indice, deslocamento);
            
            this.veiculos = novo;
            
            return v;
        }
        else return null;
    }
    
    public boolean remove(Veiculo v){
        if(v != null){
            boolean encontrado = false;
            
            for(int i=0; i<this.size && !encontrado; i++)
                if(v.equals(this.veiculos[i])){
                    encontrado = true;
                    Veiculo[] novo = new Veiculo[size-1];
                    
                    int deslocamento = this.size - i - 1;
                    
                    if(deslocamento > 0)
                        System.arraycopy(this.veiculos, i+1, novo, i, deslocamento);
                    
                    this.veiculos =  novo;
                }
            return encontrado;
        }
        else return false;
    }
            
    public int indexOf(Veiculo v){
        int posicao = -1;
        
        if(v != null){
            boolean encontrado = false;
            
            for(int i=0; i<this.size && !encontrado; i++)
                if(v.equals(this.veiculos[i])){
                    encontrado = true;
                    posicao = i;
                }
        }
        return posicao; 
    }
    
    public boolean contains(Veiculo v){
        boolean existe = false;
        
        if(v != null){
            for(int i=0; i<this.size && !existe; i++)
                if(v.equals(this.veiculos[i]))
                    existe = true;
        }
        
        return existe;
    }
    
    public boolean isEmpty(){
        
        return (size > 0);
    }
 }