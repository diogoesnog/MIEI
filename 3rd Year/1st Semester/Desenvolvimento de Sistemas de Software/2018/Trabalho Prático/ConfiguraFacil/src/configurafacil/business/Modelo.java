package configurafacil.business;

import java.io.Serializable;
import java.util.Objects;

/**
 *
 * @author Todos
 */
public class Modelo implements Serializable {
    
    private int id;
    private Cliente cliente;
    private String tipo;
    private double precoModelo;
    private double precofinal;
    private Pacote pacote;
    private Componente pintura;
    private Componente motorizacao;
    private Componente jantes;
    private Componente pneus;
    private Componente tipoVidros;
    private Componente tipoParaChoque;
    private Componente tipoTeto;
    private Componente tipoLuzes;
    private Componente tipoFrisos;
    private Componente tipoEstofos;

    

    public Modelo() {
        this.id = 0;
        this.tipo = "";
        this.pintura = new Componente();
        this.jantes = new Componente();
        this.pneus = new Componente();
        this.motorizacao = new Componente();
        this.tipoVidros = new Componente();
        this.tipoParaChoque = new Componente();
        this.tipoTeto = new Componente();
        this.tipoEstofos = new Componente();
        this.tipoLuzes = new Componente();
        this.tipoFrisos = new Componente();
        this.pacote = null;
        this.precoModelo = 0;
        this.precofinal = 0;
    }
    
    public void setPacote(Pacote pacoteN) {
        this.pacote = pacoteN;
        this.jantes = pacoteN.getJantes();
        this.pneus = pacoteN.getPneus();
        this.tipoVidros = pacoteN.getTipoVidros();
        this.tipoParaChoque = pacoteN.getTipoParaChoques();
        this.tipoTeto = pacoteN.getTipoTeto();
        this.tipoEstofos = pacoteN.getTipoEstofos();
        this.tipoLuzes = pacoteN.getTipoLuzes();
        this.tipoFrisos = pacoteN.getTipoFrisos();
        this.precofinal = precoModelo + motorizacao.getValor() + pintura.getValor() + pacote.getPreco();
    }

    public void setId (int id) {
        this.id = id;
    }
    
    public void setParaChoque(Componente c){
        this.tipoParaChoque = c;
    }
    
    public void setTipo(String tipo) {
        this.tipo = tipo;
    }
    
    public void setMotorizacao (Componente n) throws ExcecaoGeral {
        if (tipo.equals("Desportivo")) {
            Componente teste = new Componente("Motor Gasolina",0,0);
            if(!n.equals(teste)) {
                motorizacao = n;
                throw new ExcecaoGeral("Este motor não é compatível do carro.\nFoi escolhido o MOTOR GASOLINA.", 2);
            }
            else motorizacao = n;
        }
        else motorizacao = n;
    }    

    public void setTeto (Componente teto) {
        this.tipoTeto = teto;
    }
    
    public void setVidros (Componente vidros) {
        this.tipoVidros = vidros;
    }
        
    public void setPneus (Componente pneus) {
        this.pneus = pneus;        
    }
    
    public void setJantes (Componente jantes) {
        this.jantes = jantes;
    }
    
    public void setPintura(Componente pintura) {
        this.pintura = pintura;
    }
     
    public void setEstofo (Componente estofo) {
        this.tipoEstofos = estofo;
    }
    
    public void setTipoFrisos(Componente tipoFrisos){
        this.tipoFrisos = tipoFrisos;
    }
    
    public void setLuzes(Componente luzes) {
        this.tipoLuzes = luzes;
    }
    
    public void setPrecoModelo(double preco) {
        this.precoModelo = preco;
    }

    public int getId() {
        return id;
    }

    public String getTipo() {
        return tipo;
    }

    public Pacote getPacote() {
        return pacote;
    }
    
    public String getPacoteN() {
        if (pacote != null)
            return pacote.getDesignacao();
        else return "";
    }

    public double getPrecoModelo() {
        return precoModelo;
    }

    public double getPrecofinal() {
        if (pacote == null) 
            this.precofinal = precoTotal();
        return precofinal;
    }

    public Cliente getCliente() {
        return cliente;
    }

    public void setCliente(Cliente cliente) {
        this.cliente = cliente;
    }

    public Componente getPintura() {
        return pintura;
    }

    public Componente getMotorizacao() {
        return motorizacao;
    }

    public Componente getJantes() {
        return jantes;
    }

    public Componente getPneus() {
        return pneus;
    }

    public Componente getTipoVidros() {
        return tipoVidros;
    }

    public Componente getTipoParaChoque() {
        return tipoParaChoque;
    }

    public Componente getTipoTeto() {
        return tipoTeto;
    }

    public Componente getTipoLuzes() {
        return tipoLuzes;
    }

    public Componente getTipoFrisos() {
        return tipoFrisos;
    }

    public Componente getTipoEstofos() {
        return tipoEstofos;
    }
    
    
    
    
    private double precoTotal(){
        double base = this.precoModelo + this.motorizacao.getValor() + this.pintura.getValor();
        double ext = this.jantes.getValor() + this.pneus.getValor() + this.tipoParaChoque.getValor() + this.tipoTeto.getValor()+ this.tipoVidros.getValor();
        double inte = this.tipoEstofos.getValor() + this.tipoLuzes.getValor() ;
        return (base+ext+inte);
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
        final Modelo other = (Modelo) obj;
        return Objects.equals(this.id, other.id);
    }    
    
    
    public String toString(){
        StringBuilder s = new StringBuilder("Modelo escolhido\n");
        s.append("Tipo "+this.tipo+"\n");
        s.append("Preco Base "+this.precoModelo+"€\n\n");
        s.append(this.tipoFrisos+"\n");
        s.append(this.jantes+"\n");
        s.append(this.motorizacao+"\n");
        s.append(this.pintura+"\n");
        s.append(this.pneus+"\n");
        s.append(this.tipoEstofos+"\n");
        s.append(this.tipoLuzes+"\n");
        s.append(this.tipoParaChoque+"\n");
        s.append(this.tipoVidros+"\n");
        return s.toString();
    }
}

