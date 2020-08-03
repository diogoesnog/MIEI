import java.io.Serializable;

/**
 * Classe que define uma Monovolume do servico UMeR.
 * 
 * @author Diogo Araujo
 * @author Diogo Nogueira
 * @version 1.0
*/

public class MonoVolume extends Viatura implements Serializable
{
    /** Variaveis de Instancia */
    private double velocmedia;
    private double precokm;
    
    /** Construtor vazio da classe MonoVolume. */
    public MonoVolume()  {
        super();
        this.velocmedia = 55;
        this.precokm = 5;        
    }
    
    /** Construtor parametrizado da classe MonoVolume. 
     * @param eviatura A informacao generica duma Viatura do servico UMeR. 
     *  @param evelocmedia A velocidade media que define a Monovolume.
     *  @param eeprecokm O preco por km que define a Monovolume.
    */
    public MonoVolume(Viatura eviatura, double evelocmedia, double eprecokm) {
        super(eviatura);
        this.velocmedia = evelocmedia;
        this.precokm = eprecokm;
    }
    
    /** Construtor copia da classe MonoVolume.
     *   @param e A Monovolume externa recebido para fazer a copia.
    */
    public MonoVolume(MonoVolume e) {
        super(e);
        this.velocmedia = e.getVelocMedia();
        this.precokm = e.getPrecoKm();
    }    
    
    /** Get de instancia para a velocidade media da Monovolume. 
     *  @return Retorna a velocidade media. 
    */
    public double getVelocMedia() {return this.velocmedia;}
    /** Get de instancia para o preco por km da Monovolume. 
     *  @return Retorna o preco por km. 
    */
    public double getPrecoKm() {return this.precokm;}
    
    /** Define a velocidade media da Monovolume. 
     * @param evelocmedia A velocidade media da Monovolume.
    */
    public void setVelocMedia(double evelocmedia) {this.velocmedia = evelocmedia;}
    /** Define o preco por km da Monovolume. 
     * @param eprecokm O preco/km da Monovolume.
    */
    public void setPrecoKm(double eprecokm) {this.precokm = eprecokm;}
    
    /** Metodo para clonar a Monovolume.
     *  @return Uma Monovolume clonada atraves do construtor copia.
    */
    public MonoVolume clone() {return new MonoVolume(this);}
    /** Metodo para verificar se duas Monovolumes sao iguais.
     *  @return Um boolean (true ou false).
    */
    public boolean equals(Object o) {
        if (this == o) {return true;}
        if (o == null || o.getClass() != this.getClass()) {return false;}
        MonoVolume teste = (MonoVolume) o;
        return ( super.equals(teste) &&
        this.velocmedia == teste.getVelocMedia() &&
        this.precokm == teste.getPrecoKm()
        );
    }
    /** Metodo para transformar a informacao das variaveis de instancia em String.
     *  @return Uma String com a info da Monovolume.
    */
    public String toString() {
        StringBuilder str = new StringBuilder();
        str.append("A Monovolume tem os seguintes dados: ")
            .append(getVelocMedia() + "km \n")
            .append(getPrecoKm() + "km \n")
            .append("Situa-se em " + super.getLocViatura().toString() + "\n");
        return str.toString();
    }
}  