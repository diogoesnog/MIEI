/**
 * Classe base Hotel.
 * 
 * @author Diogo Nogueira.
 * @version 27.05.2017
 */

public abstract class Hotel implements Comparable<Hotel> {
    /** Variaveis de Instancia. */
    private String codigo;
    private String nome;
    private String localidade;
    private double precoBaseQuarto;
    private int numeroQuartos;
    private int estrelas;
    
    /** Construtores. */
    
    /** Construtor vazio da classe Hotel. */
    public Hotel() {
        this.codigo = "n/a";
        this.nome = "n/a";
        this.localidade = "n/a";
        this.precoBaseQuarto = 0;
        this.numeroQuartos = 0;
        this.estrelas = 0;
    }
    
    /** Construtor parametrizado da classe Hotel. */
    public Hotel(String codigo, String nome, String localidade, double precoBaseQuarto, int numQuartos, int estrelas) {
        this.codigo = codigo;
        this.nome = nome;
        this.localidade = localidade;
        this.precoBaseQuarto = precoBaseQuarto;
        this.numeroQuartos = numQuartos;
        this.estrelas = estrelas;
    }
    
    /** Construtor de copia da classe Hotel. */
    public Hotel(Hotel c) {
        this.codigo = c.getCodigo();
        this.nome = c.getNome();
        this.localidade = c.getLocalidade();
        this.precoBaseQuarto = c.getPrecoBaseQuarto();
        this.numeroQuartos = c.getNumeroQuartos();
        this.estrelas = c.getEstrelas();
    }

    /** Metodos. */
    
    /** Metodos de Instancia. -> Gets e Sets. */
    public String getCodigo() {return this.codigo;}
    public String getNome() {return this.nome;}
    public String getLocalidade() {return this.localidade;}
    public double getPrecoBaseQuarto() {return this.precoBaseQuarto;}
    public int getNumeroQuartos() {return this.numeroQuartos;}
    public int getEstrelas() {return this.estrelas;}
    
    public void setCodigo(String ecodigo) {this.codigo = ecodigo;}
    public void setNome(String enome) {this.nome = enome;}
    public void setLocalidade(String elocalidade) {this.localidade = elocalidade;}
    public void setPrecoBaseQuarto(int eprecoBaseQuarto) {this.precoBaseQuarto = eprecoBaseQuarto;}
    public void setNumeroQuartos(int equartos) {this.numeroQuartos = equartos;}
    public void setEstrelas(int eestrelas) {this.estrelas = eestrelas;}
        
    /** Metodos Complementares. */
    public boolean equals(Object obj) {
        if(obj == this) {return true;}
        if(obj == null || obj.getClass() != this.getClass()) {return false;}
        Hotel o = (Hotel) obj;
        return o.getCodigo().equals(this.codigo) && o.getNome().equals(this.nome) && 
                o.getLocalidade().equals(this.localidade) && o.getPrecoBaseQuarto() == this.precoBaseQuarto 
                && o.getEstrelas() == this.estrelas;
    }
    public String toString() {
        StringBuilder sb = new StringBuilder();
        sb.append("Hotel '").append(nome).append("'\n");
        sb.append("(").append(this.codigo).append(") ").append(this.localidade);
        sb.append("Preço por quarto: ").append(this.precoBaseQuarto).append("€");
        sb.append("Numero de Quartos: ").append(this.numeroQuartos);
        sb.append("Estrelas: ").append(this.estrelas).append("**");
        return sb.toString();
    }
    public abstract Hotel clone(); // Abstract pois ha mais de 1 tipo de Hotel.
    
    /** Metodos Pedidos. */
        
    /** Metodo que calcula o preco de uma noite no hotel. */
    public abstract double precoQuarto(); // Abstract pois cada hotel faz o seu preco.
    
    /** Codigo hash. */
    public int hashCode() {
        return codigo.hashCode();
    }
    
    
    /**
    * Implementação da ordem natural de comparação de instâncias de Hotel.
    * Por simplificação, apenas se está a comparar os códigos.
    *
    */
    
    public int compareTo(Hotel h) {
        return h.getCodigo().compareTo(codigo);
    }
}