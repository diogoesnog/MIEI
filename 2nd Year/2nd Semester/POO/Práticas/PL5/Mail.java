import java.util.GregorianCalendar;

/**
 * Classe Mail.
 * 
 * @author Diogo Nogueira.
 * @version 27.05.2017
 */

public class Mail
{
    /** Variáveis de Instância.*/
        
    private String remetente;
    private GregorianCalendar envio;
    private GregorianCalendar recepcao;
    private String assunto;
    private String texto;

    /** Construtores. */
    
    /** Construtor vazio da classe Mail. */
    public Mail() {
        this.remetente = new String();
        this.envio = new GregorianCalendar();
        this.recepcao = new GregorianCalendar();
        this.assunto = new String();
        this.texto = new String();
    }

    /** Construtor parametrizado da classe Mail. */
    public Mail(String remetente, GregorianCalendar envio, GregorianCalendar recepcao, String assunto, String texto) {
        this.remetente = remetente;
        this.envio = envio;
        this.recepcao = recepcao;
        this.assunto = assunto;
        this.texto = texto;
    }

    /**Construtor de copia da classe Mail. */
    public Mail(Mail o) {
       this.remetente = o.getRemetente();
        this.envio = o.getEnvio();
        this.recepcao = o.getRecepcao();
        this.assunto = o.getAssunto();
        this.texto = o.getTexto(); 
    }
    
    /** Métodos. */
    
    /** Métodos de Instância. -> Gets e Sets. */
    public String getRemetente() {return this.remetente;}
    public GregorianCalendar getEnvio() {return this.envio;}
    public GregorianCalendar getRecepcao() {return this.recepcao;}
    public String getAssunto() {return this.assunto;}
    public String getTexto() {return this.texto;}
    
    public void setRemetente(String eremetente) {this.remetente = eremetente;}
    public void setEnvio(GregorianCalendar eenvio) {this.envio = eenvio;}
    public void setRecepcao(GregorianCalendar erecepcao) {this.recepcao = erecepcao;}
    public void setAssunto(String eassunto) {this.assunto = eassunto;}  
    public void setTexto(String etexto) {this.texto = etexto;}

    /** Métodos Complementares. */
    protected Mail clone() {return new Mail(this);}
    public boolean equals(Object o) {
        if(o == this) {return true;}
        if(o == null || o.getClass() != this.getClass()) {return false;}
        Mail m = (Mail) o;
        return m.getRemetente().equals(remetente) && m.getAssunto().equals(assunto) &&
                m.getEnvio().equals(envio) && m.getRecepcao().equals(recepcao) && m.getTexto().equals(texto);
    }
    public String toString() {return "From: " + remetente + "\nSubject: " + assunto + "\nOn: " +envio+"/"+recepcao+"\n"+texto;}
}