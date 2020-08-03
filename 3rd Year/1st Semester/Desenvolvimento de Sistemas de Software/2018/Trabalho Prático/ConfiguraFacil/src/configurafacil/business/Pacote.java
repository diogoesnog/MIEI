package configurafacil.business;

import java.io.Serializable;

/**
 *
 * @author Todos
 */
public class Pacote implements Serializable {
    
    private String designacao;
    private double preco;
    private Componente tipoEstofos;
    private Componente tipoFrisos;
    private Componente tipoLuzes;
    private Componente tipoParaChoques;
    private Componente tipoTeto;
    private Componente tipoVidros;
    private Componente pneus;
    private Componente jantes;

    public Pacote (String designacao) {
        this.designacao = designacao;
        switch (designacao) {
            case "Sport":
                this.tipoFrisos = new Componente("Frisos Liga de Carbono",200,1);
                this.tipoEstofos = new Componente("Estofo Sport Cinzento", 1765, 1);
                this.tipoLuzes = new Componente("Luzes Azul",115,1);
                this.tipoParaChoques = new Componente("Pára-Choque Linha Sport",1869,1);
                this.tipoTeto = new Componente("Teto de Abrir em Tecido",1630,1);
                this.tipoVidros = new Componente("Vidro Escurecido", 2069, 1);
                this.pneus = new Componente("Pneu Michelin", 1555, 1);
                this.jantes = new Componente("Jantes em Preto",745,1);
                this.preco = 9700;
                break;
            case "Comfort":
                this.tipoFrisos = new Componente("Frisos Pérola Cromado",180,1);
                this.tipoEstofos = new Componente("Estofo Pele Preto", 1255, 1);
                this.tipoLuzes = new Componente("Luzes Vermelhas", 115, 1);
                this.tipoParaChoques = new Componente("Pára-Choque Linha Confort",1559,1);
                this.tipoTeto = new Componente("Teto Panorâmico", 1755, 10);
                this.tipoVidros = new Componente("Vidro Escurecido", 2069, 1);
                this.pneus = new Componente("Pneu Michelin", 1555, 1);
                this.jantes = new Componente("Jantes Liga-Leve Ferric",856, 10);
                this.preco = 9200;
            case "Deluxe":
                this.tipoFrisos = new Componente("Frisos Liga de Carbono",200,1);
                this.tipoEstofos = new Componente("Estofo Pele Camel",1855,1);
                this.tipoLuzes = new Componente("Luzes Personalizáveis",155,1);
                this.tipoParaChoques = new Componente("Pára-Choque Linha Sport",1869,1);
                this.tipoTeto = new Componente("Teto de Abrir Automático", 1950, 1);
                this.tipoVidros = new Componente("Vidro Escurecido", 2069, 1);
                this.pneus = new Componente("Pneu Michelin", 1555, 1);
                this.jantes = new Componente("Jantes Bicolores em Preto",945,10);
                this.preco = 10500;
                break;
        }
        
    }

    public String getDesignacao() {
        return designacao;
    }

    public void setDesignacao(String designacao) {
        this.designacao = designacao;
    }

    public double getPreco() {
        return preco;
    }

    public void setPreco(double preco) {
        this.preco = preco;
    }

    public Componente getTipoEstofos() {
        return tipoEstofos;
    }

    public void setTipoEstofos(Componente tipoEstofos) {
        this.tipoEstofos = tipoEstofos;
    }

    public Componente getTipoFrisos() {
        return tipoFrisos;
    }

    public void setTipoFrisos(Componente tipoFrisos) {
        this.tipoFrisos = tipoFrisos;
    }

    public Componente getTipoLuzes() {
        return tipoLuzes;
    }

    public void setTipoLuzes(Componente tipoLuzes) {
        this.tipoLuzes = tipoLuzes;
    }

    public Componente getTipoParaChoques() {
        return tipoParaChoques;
    }

    public void setTipoParaChoques(Componente tipoParaChoques) {
        this.tipoParaChoques = tipoParaChoques;
    }

    public Componente getTipoTeto() {
        return tipoTeto;
    }

    public void setTipoTeto(Componente tipoTeto) {
        this.tipoTeto = tipoTeto;
    }

    public Componente getTipoVidros() {
        return tipoVidros;
    }

    public void setTipoVidros(Componente tipoVidros) {
        this.tipoVidros = tipoVidros;
    }

    public Componente getPneus() {
        return pneus;
    }

    public void setPneus(Componente pneus) {
        this.pneus = pneus;
    }

    public Componente getJantes() {
        return jantes;
    }

    public void setJantes(Componente jantes) {
        this.jantes = jantes;
    }
}