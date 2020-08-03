import java.io.Serializable;

/**
 * Classe que define uma Moto do servico UMeR.
 * 
 * @author Diogo Araujo
 * @author Diogo Nogueira
 * @version 1.0
*/

public class Moto extends Viatura implements Serializable
{
    /** Variaveis de Instancia */
    private double velocmedia;
    private double precokm;
    
    /** Construtor vazio da classe Moto. */
    public Moto()  {
        super();
        this.velocmedia = 60;
        this.precokm = 2;        
    }
    
    /** Construtor parametrizado da classe Moto. 
     * @param eviatura A informacao generica duma da Viatura do servico UMeR. 
     *  @param evelocmedia A velocidade media que define a Moto.
     *  @param eeprecokm O preco por km que define a Moto.
    */
    public Moto(Viatura eviatura, double evelocmedia, double eprecokm) {
        super(eviatura);
        this.velocmedia = evelocmedia;
        this.precokm = eprecokm;
    }
    
    /** Construtor copia da classe Moto.
     *   @param e A moto externa recebido para fazer a copia.
    */
    public Moto(Moto e) {
        super(e);
        this.velocmedia = e.getVelocMedia();
        this.precokm = e.getPrecoKm();
    }    
    
    /** Get de instancia para a velocidade media da Moto. 
     *  @return Retorna a velocidade media. 
    */
    public double getVelocMedia() {return this.velocmedia;}
    /** Get de instancia para o preco por km da Moto. 
     *  @return Retorna o preco por km. 
    */
    public double getPrecoKm() {return this.precokm;}
    
    /** Define a velocidade media da Moto. 
     * @param evelocmedia A velocidade media da Moto.
    */
    public void setVelocMedia(double evelocmedia) {this.velocmedia = evelocmedia;}
    /** Define o preco por km da Moto. 
     * @param eprecokm O preco/km da Moto.
    */
    public void setPrecoKm(double eprecokm) {this.precokm = eprecokm;}
    
    /** Metodo para clonar a Moto.
     *  @return Uma Moto clonada atraves do construtor copia.
    */
    public Moto clone() {return new Moto(this);}
    /** Metodo para verificar se duas Motos sao iguais.
     *  @return Um boolean (true ou false).
    */
    public boolean equals(Object o) {
        if (this == o) {return true;}
        if (o == null || o.getClass() != this.getClass()) {return false;}
        Moto teste = (Moto) o;
        return ( super.equals(teste) &&
        this.velocmedia == teste.getVelocMedia() &&
        this.precokm == teste.getPrecoKm()
        );
    }
    /** Metodo para transformar a informacao das variaveis de instancia em String.
     *  @return Uma String com a info da Moto.
    */
    public String toString() {
        StringBuilder str = new StringBuilder();
        str.append("A Moto tem os seguintes dados: ")
            .append(getVelocMedia() + "km \n")
            .append(getPrecoKm() + "km \n")
            .append("Situa-se em " + super.getLocViatura().toString() + "\n");
        return str.toString();
    }
}