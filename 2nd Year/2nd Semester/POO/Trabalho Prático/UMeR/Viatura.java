import java.awt.geom.Point2D.Float;
import java.io.Serializable;


/**
 * Classe que define Viatura do servico UMeR.
 * 
 * @author Diogo Araujo
 * @author Diogo Nogueira
 * @version 2.7
 */

public class Viatura implements Serializable
{
    /** Variaveis de Instancia */
    private double fiavel;
    private Float locviatura;
    private Motorista motorista;
    private double lucro;
    
    /** Construtor vazio da classe Viatura. */
    public Viatura() {
        this.fiavel = Math.random();
        this.locviatura = new Float();
        this.motorista = new Motorista();
        this.lucro = 0;
    }

    /** Construtor parametrizado da classe Viatura. 
     *  @param efiavel Define a capacidade da Viatura cumprir o tempo acordado com o cliente.
     *  @param elocviatura A localizacao da Viatura.
     *  @param emotorista O motorista da Viatura.
     *  @param elucro O lucro (dinheiro acumulado/feito pela Viatura).
    */
    public Viatura(double efiavel, Float elocviatura, Motorista emotorista, double elucro) {
        this.fiavel = efiavel;
        this.locviatura = elocviatura;
        this.motorista = emotorista.clone();
        this.lucro = elucro;
    }
    
    /** Construtor copia da classe Viatura.
     *   @param e A Viatura externa recebida para fazer a copia.
    */
    public Viatura(Viatura e) {
        this.fiavel = e.getFiavel();
        this.locviatura = e.getLocViatura();
        this.motorista = e.getMotorista().clone();
        this.lucro = e.getLucro();
    }
     
    /** Get de instancia para a fiabilidade da Viatura. 
     *  @return Retorna o fator de fiabilidade.
    */
    public double getFiavel() {return this.fiavel;}
    /** Get de instancia para a localizacao. 
     *  @return Retorna a localizacao da Viatura. 
    */
    public Float getLocViatura() {return this.locviatura;}
    /** Get de instancia para o motorista. 
     *  @return Retorna o motorista da Viatura. 
    */
    public Motorista getMotorista() {return this.motorista.clone();}
    /** Get de instancia para o lucro feito pela viatura.
     *  @return O lucro da Viatura.
    */
    public double getLucro() {return this.lucro;}
        
    /** Define o fator de fiabilidade da Viatura. 
     * @param efiavel Fator dde fiabilidade da Viatura.
    */
    public void setFiavel(double efiavel) {this.fiavel = efiavel;}
    /** Define o lucro da Viatura. 
     * @param elucro O lucro da Viatura.
    */
    public void setLucro(double elucro) {this.lucro = elucro;}
    /** Define a localizacao da Viatura. 
     * @param ex A cordenada x (em km) da localizacao da Viatura.
     * @param ey A coordenada y (em km) da localizacao da Viatura.
     * @see Point2D.Float
    */
    public void setLocViatura(float ex, float ey) {this.locviatura = new Float(ex,ey);}
     /** Define o motorista da Viatura. 
     * @param emotorista O motorista da Viatura.
    */
    public void setMotorista(Motorista emotorista) {this.motorista = emotorista.clone();}
    
    /** Metodo para clonar a Viatura.
     *  @return Uma Viatura clonada atraves do construtor copia.
    */
    public Viatura clone() {return new Viatura(this);}
    /** Metodo para verificar se duas Viaturas sao iguais.
     *  @return Um boolean (true ou false).
    */
    public boolean equals(Object o) {
        if (this == o) {return true;}
        if (o == null || o.getClass() != this.getClass()) {return false;}
        Viatura teste = (Viatura) o;
        return (
        this.fiavel == teste.getFiavel() &&
        this.locviatura.equals(teste.getLocViatura()) &&
        this.motorista.equals(teste.getMotorista().clone())
        );
    }
    /** Metodo para transformar a informacao das variaveis de instancia em String.
     *  @return Uma String com a info da Viatura.
    */
    public String toString() {
        StringBuilder str = new StringBuilder();
        str.append("A viatura situa-se em " + getLocViatura().toString() + "\n");
        return str.toString();
    }
}