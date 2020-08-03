import java.time.LocalDateTime;
import java.awt.geom.Point2D.Float;
import java.io.Serializable;
import java.time.Duration;

/**
 * Classe que define a Viagem do servico UMeR.
 * 
 * @author Diogo Araujo
 * @author Diogo Nogueira
 * @version 1.5
 */

public class Viagem implements Serializable
{
    /** Variaveis de Instancia. */
    private Cliente cl;
    private Motorista mt;
    private LocalDateTime datetime;
    private Viatura viatura;
    private double precoviagem; 
    private double distanciaviagem; // Em km.
    private Duration tempo;
    private Float gpsdestino;
    
    /** Construtor parametrizado da classe Viagem. 
     *  @param ecl O Cliente utilizado para criar uma Viagem.
     *  @param eviatura A viatura escolhida para a viagem.
     *  @see LocalDateTime
    */
    public Viagem (Cliente ecl, Viatura eviatura, float ex, float ey) {
        this.cl = ecl.clone();
        this.viatura = eviatura.clone();
        this.mt = viatura.getMotorista().clone();
        this.datetime = LocalDateTime.now();
        this.gpsdestino = new Float(ex,ey);
        calculaDistancia();
        calculaPreco();
        calculaTempo();
    }
    
    /**  Construtor copia da classe Viagem.
     *   Esta privado porque nao tem sentido criar uma copia duma viagem em si. Apenas esta construido para o clone(). 
     *   @param e A Viagem externa recebida para fazer a copia.
    */
    private Viagem (Viagem e) {
        this.cl = e.getCliente();
        this.mt = e.getMotorista();
        this.datetime = e.getDate();
        this.viatura = e.getViatura();
        this.precoviagem = e.getPreco();
        this.distanciaviagem = e.getDistancia();
        this.tempo = e.getTempo();
        this.gpsdestino = e.getDestino();
    }
       
    /** Get de instancia para o Cliente. 
     *  @return Retorna o Cliente da Viagem. 
    */
    public Cliente getCliente() {return this.cl.clone();}
    /** Get de instancia para o Motorista. 
     *  @return Retorna o Motorista da Viagem. 
    */
    public Motorista getMotorista() {return this.mt.clone();}
    /** Get de instancia para a Data. 
     *  @return Retorna a data em que foi efetuada a Viagem. 
     *  @see LocalDateTime
    */
    public LocalDateTime getDate() {return this.datetime;}
    /** Get de instancia para a Viatura.
     *  @return Retorna a Viatura que efectuou a Viagem.
     */
    public Viatura getViatura() {return this.viatura.clone();}
    /** Get de instancia para o Preco.
     *  @return Retorna o preco.
     */
    public double getPreco() {return this.precoviagem;}
    /** Get de instancia para a Distancia.
     *  @return Retorna a distancia.
     */
    public double getDistancia() {return this.distanciaviagem;}
    /** Get de instancia para o Tempo.
     *  @return Retorna o tempo.
     */
    public Duration getTempo() {return this.tempo;}
    /** Get de instancia para o Destino.
     *  @return Retorna o destino.
     */
    public Float getDestino() {return this.gpsdestino;}
    
    /** Metodo distancia que permite calcular a distancia entre as localizacoes da Viatura e do Cliente.
     * @return Retorna a distancia total da Viagem.
    */
    public void calculaDistancia(){
        Float gpscliente = cl.getLocalizacao();
        Float gpsviatura = viatura.getLocViatura();
        
        this.distanciaviagem = gpsviatura.distance(gpscliente) + gpscliente.distance(gpsdestino);
    }

    /** Metodo que calcula o preco de uma Viagem. 
     * @return Retorna o preco da Viagem de acordo com a Viatura escolhida.
    */
    public void calculaPreco(){
        if (viatura instanceof Taxi) this.precoviagem = ((Taxi) viatura).getPrecoKm() * distanciaviagem;
        if (viatura instanceof Moto) this.precoviagem = ((Moto) viatura).getPrecoKm() * distanciaviagem;
        if (viatura instanceof MonoVolume) this.precoviagem = ((MonoVolume)viatura).getPrecoKm() * distanciaviagem;
    }
      
    /** Metodo que calcula o tempo total de uma Viagem. 
     * @return Retorna o tempo da Viagem de acordo com a Viatura escolhida.
    */
    public void calculaTempo(){
        if (viatura instanceof Taxi) {
            long temp = (long)((distanciaviagem/((Taxi) viatura).getVelocMedia())*60);
            this.tempo = Duration.ofMinutes(temp);
        }
        if (viatura instanceof Moto) {
            long temp = (long)((distanciaviagem/((Moto) viatura).getVelocMedia())*60);
            this.tempo = Duration.ofMinutes(temp);
        }
        if (viatura instanceof MonoVolume) {
            long temp = (long)((distanciaviagem/((MonoVolume) viatura).getVelocMedia())*60);
            this.tempo = Duration.ofMinutes(temp);
        }
    }
    
             
    /** Metodo para transformar a informacao das variaveis de instancia em String.
     *  @return Uma String com a info da Viagem.
    */
    public String toString() {
        StringBuilder str = new StringBuilder();
        str.append("A viagem custou: \n")
            .append(getPreco()+" € \n")
            .append("Demorou: \n")
            .append(getTempo()+"\n")
            .append("Foram percorridos: \n")
            .append(getDistancia()+" km \n");
        return str.toString();
    }
    /** Metodo para clonar a Viagem.
     *  @return Uma Viagem clonada atraves do construtor copia.
     */
    public Viagem clone() {return new Viagem(this);}
    /** Metodo para verificar se duas Viagens sao iguais.
     *  @return Um boolean (true ou false).
     */
    public boolean equals (Object o) {
        if (this == o) {return true;}
        if (o == null || o.getClass() != this.getClass()) {return false;}
        Viagem teste = (Viagem) o;
        boolean igual = (teste.getCliente()).equals(this.getCliente()) && (teste.getDate().equals(this.getDate()));
        return igual;
    }                    
}