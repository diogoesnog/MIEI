import java.io.Serializable;

/**
 * Classe que define um Taxi do servico UMeR.
 * 
 * @author Diogo Araujo
 * @author Diogo Nogueira
 * @version 1.0
*/

public class Taxi extends Viatura implements Serializable
{
    /** Variaveis de Instancia */
    private double velocmedia;
    private double precokm;
    
    /** Construtor vazio da classe Taxi. */
    public Taxi()  {
        super();
        this.velocmedia = 50;
        this.precokm = 3;        
    }
    
    /** Construtor parametrizado da classe Taxi. 
     * @param eviatura A informacao generica da Viatura do servico UMeR. 
     *  @param evelocmedia A velocidade media que define o Taxi.
     *  @param eeprecokm O preco por km que define o Taxi.
    */
    public Taxi(Viatura eviatura, double evelocmedia, double eprecokm) {
        super(eviatura);
        this.velocmedia = evelocmedia;
        this.precokm = eprecokm;
    }
    
    /** Construtor copia da classe Taxi.
     *   @param e O Taxi externo recebido para fazer a copia.
    */
    public Taxi(Taxi e) {
        super(e);
        this.velocmedia = e.getVelocMedia();
        this.precokm = e.getPrecoKm();
    }    
    
    /** Get de instancia para a velocidade media do Taxi. 
     *  @return Retorna a velocidade media. 
    */
    public double getVelocMedia() {return this.velocmedia;}
    /** Get de instancia para o preco por km do Taxi. 
     *  @return Retorna o preco por km. 
    */
    public double getPrecoKm() {return this.precokm;}
    
    /** Define a velocidade media do Taxi. 
     * @param evelocmedia A velocidade media do Taxi.
    */
    public void setVelocMedia(double evelocmedia) {this.velocmedia = evelocmedia;}
    /** Define o preco por km do Taxi. 
     * @param eprecokm O preco/km do Taxi.
    */
    public void setPrecoKm(double eprecokm) {this.precokm = eprecokm;}
    
    /** Metodo para clonar o Taxi.
     *  @return Um Taxi clonado atraves do construtor copia.
    */
    public Taxi clone() {return new Taxi(this);}
    /** Metodo para verificar se dois Taxis sao iguais.
     *  @return Um boolean (true ou false).
    */
    public boolean equals(Object o) {
        if (this == o) {return true;}
        if (o == null || o.getClass() != this.getClass()) {return false;}
        Taxi teste = (Taxi) o;
        return ( super.equals(teste) &&
        this.velocmedia == teste.getVelocMedia() &&
        this.precokm == teste.getPrecoKm()
        );
    }
    /** Metodo para transformar a informacao das variaveis de instancia em String.
     *  @return Uma String com a info do Taxi.
    */
    public String toString() {
        StringBuilder str = new StringBuilder();
        str.append("O Taxi tem os seguintes dados: ")
            .append(getVelocMedia() + "km \n")
            .append(getPrecoKm() + "km \n")
            .append("Situa-se em " + super.getLocViatura().toString() + "\n");
        return str.toString();
    }
}