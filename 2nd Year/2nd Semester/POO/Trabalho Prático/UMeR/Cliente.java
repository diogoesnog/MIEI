import java.awt.geom.Point2D.Float;
import java.io.Serializable;
import java.util.ArrayList;

/**
 * A classe que define o Cliente do servico UMeR.
 * 
 * @author Diogo Araujo
 * @author Diogo Nogueira
 * @version 2.1
 */

public class Cliente extends IdGeral implements Serializable
{
    /** Variaveis de Instancia. */
    private Float localizacao;
    private ArrayList<Viagem> historico;
    
    /** Construtor vazio da classe Cliente. */
    public Cliente() {
        super();
        this.localizacao = new Float();
        this.historico = new ArrayList<Viagem>();
    }
    
    /** Construtor parametrizado da classe Cliente.
     *  @param eid A identificacao generica dum utilizador do servico UMeR.
     *  @param ex A coordenada x (em km) da localizacao do Cliente.
     *  @param ey A coordenada y (em km) da localizacao do Cliente.
     *  @see Point2D.Float
    */
    public Cliente(IdGeral eid, float ex, float ey, ArrayList<Viagem> ehistorico){
        super(eid);
        this.localizacao = new Float (ex,ey);
        setHistorico(ehistorico);
    }
    
    /** Construtor de copia da classe Cliente.
     *  @param e Cliente externo para fazer a copia.
    */
    public Cliente(Cliente e) {
        super(e);
        this.localizacao = e.getLocalizacao();
        this.historico = e.getHistorico();
    }
    
    /** Get da Localizacao do Cliente.
     *  @return A localizacao do Cliente.
     *  @see Point2D.Float
    */
    public Float getLocalizacao() {return this.localizacao;}
     /** Get do historico das Viagens efetuadas pelo Cliente.
     *  @return Uma lista do historico das Viagens do Cliente.
    */
    public ArrayList<Viagem> getHistorico() {
        ArrayList<Viagem> novo = new ArrayList<Viagem>();
        for (Viagem v : this.historico) {
            novo.add(v.clone());
        }
        return novo;
    }
   
    /** Define a localizacao do Cliente.
     *  @param ex A coordenada x (em km) da localizacao do Cliente.
     *  @param ey A coordenada y (em km) da localizacao do Cliente.
     *  @see Point2D.Float
    */
    public void setLocalizacao(float ex, float ey) {
        this.localizacao.setLocation(ex,ey);
    }
    /** Define o historico de Viagens do Cliente. 
     * @param ehistorico O historico das viagens.
    */
    public void setHistorico(ArrayList<Viagem> ehistorico) {
        this.historico.clear();
        for (Viagem v : ehistorico) {
            this.historico.add(v.clone());
        }
    }
    
    /** Metodo para transformar o historico das Viagens efetuadas pelo Cliente em String. 
     * @return Uma String com o historico das viagens.
    */
    public String datasViagemString() {
        StringBuilder str = new StringBuilder();
        str.append("O Cliente efetuou viagens nas seguintes datas: \n");
        for(Viagem v: this.historico) {
            str.append("Data: \n" + v.getDate().toLocalDate().toString() + "\n")
               .append("Hora: \n" + v.getDate().toLocalTime().toString() + "\n\n");
        }
        return str.toString();
    }
          
    /** Metodo para transformar a informacao das variaveis de instancia em String.
     *  @return Uma String com a info do Cliente.
    */
    public String toString() {
        StringBuilder str = new StringBuilder();
        str.append("O cliente tem os seguintes dados: \n")
            .append("Nome:" + getNome() + "\n")
            .append("Morada: " + getMorada() + "\n")
            .append("Data: " + getData().toString()+"\n");
        return str.toString();
    }
    /** Metodo para clonar o Cliente.
     *  @return Um Cliente clonado atraves do construtor copia.
    */
    public Cliente clone() {return new Cliente(this);}
    /** Metodo para verificar se dois Clientes sao iguais.
     *  @return Um boolean (true ou false).
    */
    public boolean equals(Object o) {
        if (this == o) {return true;}
        if (o == null || o.getClass() != this.getClass()) {return false;}
        Cliente teste = (Cliente) o;
        return teste.getEmail().equals(this.getEmail());
    }
    
    /** Metodo que adiciona uma Viagem ao historico de Viagens do Cliente.
     * @param v Viagem a ser adicionada ao historico.
    */
    public void adicionaViagem(Viagem v){historico.add(v.clone());}
}