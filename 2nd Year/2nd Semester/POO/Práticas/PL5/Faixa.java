/**
 * Classe Faixa.
 * 
 * @author Diogo Nogueira.
 * @version 27.05.2017
 */

public class Faixa
{
    /** Variáveis de Instância.*/
    
    private String nome;
    private String autor;
    private double duracao;
    private int classificacao;
    
    /** Construtores. */
    
    /** Construtor vazio da classe Faixa. */
    public Faixa() {
        this.nome = new String();
        this.autor = new String();
        this.duracao = 0;
        this.classificacao = 0;
    }
    
    /** Construtor parametrizado da classe Faixa. */
    public Faixa(String enome, String eautor, double eduracao, int eclassificacao) {
        this.nome = enome;
        this.autor = eautor;
        this.duracao = eduracao;
        this.classificacao = eclassificacao;
    }

    /** Construtor de copia da classe Faixa. */
    public Faixa(Faixa o) {
        this.nome = o.getNome();
        this.autor = o.getAutor();
        this.duracao = o.getDuracao();
        this.classificacao = o.getClassificacao();
    }

    /** Métodos. */
    
    /** Métodos de Instância. -> Gets e Sets. */
    public String getNome() {return this.nome;}
    public String getAutor() {return this.autor;}
    public double getDuracao() {return this.duracao;}
    public int getClassificacao() {return this.classificacao;}
    
    public void setNome(String enome) {this.nome = enome;}
    public void setAutor(String eautor) {this.autor = eautor;}
    public void setDuracao(double eduracao) {this.duracao = eduracao;}
    public void setClassificacao(int eclassificacao) {this.classificacao = eclassificacao;}

    /** Métodos Complementares. */
    public boolean equals(Object o) {
        if(o==this) {return true;}
        if(o==null || o.getClass() != this.getClass()) {return false;}
        Faixa f = (Faixa) o;
        return f.getNome().equals(nome) && f.getAutor().equals(autor) && f.getDuracao() == duracao && f.getClassificacao() == classificacao;
    }
    public Faixa clone() {
        return new Faixa(this);
    }
    public String toString() {
        return nome +" ("+autor+"): "+ classificacao + "* ["+duracao+"m]";
    }
}