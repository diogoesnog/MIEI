package configurafacil.business;

import java.io.Serializable;

/**
 * A classe que define um componente.
 * @author Todos
 */
public class Componente implements Serializable {
    
    private int id;
    private String designacao;
    private double valor;
    private int stock;

    /**
     * O Construtor do Componente.
     */
    public Componente() {
        this.id = 0;
        this.designacao = "";
        this.valor = 0;
        this.stock = 0;
    }
    
    // Só para a Stock.java

    /**
     * O Construtor parametrizado do Componente.
     * @param designacao A designação do Componente.
     * @param valor O valor associado ao Componente.
     * @param stock O stock desse componente.
     */
    public Componente(String designacao, double valor, int stock) {
        this.designacao = designacao;
        this.valor = valor;
        this.stock = stock;
    }
    
    
    
    public Componente(int id, String designacao, double valor, int quantidade) {
        this.id = id;
        this.designacao = designacao;
        this.valor = valor;
        this.stock = quantidade;
    }

    public String getDesignacao() {
        return designacao;
    }

    public void setDesignacao(String designacao) {
        this.designacao = designacao;
    }

    public double getValor() {
        return valor;
    }

    public void setValor(double valor) {
        this.valor = valor;
    }

    public int getStock() {
        return stock;
    }

    public void setStock(int stock) {
        this.stock = stock;
    }  

    public int getId() {
        return id;
    }

    public void setId(int id) {
        this.id = id;
    }
    
    /**
     *
     * @throws ExcecaoGeral
     */
    public void retiraQuantidade() throws ExcecaoGeral {
        if((this.stock-1)<0) throw new ExcecaoGeral();
        this.stock--;
    }
    
    public void adicionaQuantidade(int quantidade){
        this.stock += quantidade;
    }
    
    public String toString(){
        StringBuilder s = new StringBuilder();
        s.append(this.designacao+" | ");
        s.append("Preço "+this.valor+"€");
      //  s.append("Quantidade "+this.stock+"\n");
        return s.toString();
    }
        
    @Override
    public boolean equals(Object obj) {
        if (this == obj) {
            return true;
        }
        if (obj == null) {
            return false;
        }
        if (getClass() != obj.getClass()) {
            return false;
        }
        Componente other = (Componente) obj;
        return other.getDesignacao().equals(this.designacao);
    }
}
