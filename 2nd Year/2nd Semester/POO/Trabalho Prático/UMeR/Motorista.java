import java.util.ArrayList;
import java.io.Serializable;

/**
 * A classe que define o Motorista do servico UMeR.
 * 
 * @author Diogo Araujo
 * @author Diogo Nogueira
 * @version 2.1
 */

public class Motorista extends IdGeral implements Serializable
{
    /** Variaveis de Instancia. */
    private int classificacao;
    private double kmsfeitos;
    private boolean disponivel;
    private ArrayList<Viagem> historico;

    /** Construtor vazio da classe Motorista. */
    public Motorista() {
        super();
        this.classificacao = 100;
        this.kmsfeitos = 0;
        this.disponivel = true;
        this.historico = new ArrayList<Viagem>();
    }

    /** Construtor parametrizado da classe Motorista. 
     *  @param eid O ID generico do Motorista.
     *  @param egrau Grau de cumprimento de horario estabelecido com o cliente, dado por um factor entre 0 e 100.
     *  @param eclass Classificacao do motorista, dado numa escala de 0 a 100.
     *  @param ekmsf Numero de kms ja realizados na UMeR.
     *  @param edisp Se esta ou nao disponivel.
    */
    public Motorista(IdGeral eid, short eclass, double ekmsf, boolean edisp, ArrayList<Viagem> ehistorico) {
        super(eid);
        this.classificacao = eclass;
        this.kmsfeitos = ekmsf;
        this.disponivel = edisp;
        setHistorico(ehistorico);
    }
    
    /** Construtor de copia da classe Motorista. 
     *  @param e Um Motorista que tera a copia.
    */
    public Motorista(Motorista e) {
        super(e);
        this.classificacao = e.getClassificacao();
        this.kmsfeitos = e.getKmsFeitos();
        this.disponivel = e.getDisponivel();
        this.historico = e.getHistorico();
    }
    
    
    /** Get da Classificacao.
     *  @return Classificacao do Motorista.
    */
    public int getClassificacao() {return this.classificacao;}
    /** Get dos Kms Feitos.
     *  @return Kilometros feitos.
    */
    public double getKmsFeitos() {return this.kmsfeitos;}
    /** Get da Disponibilidade.
     *  @return Disponibilidade do motorista.
    */
    public boolean getDisponivel() {return this.disponivel;}
    /** Get do historico das Viagens efetuadas pelo Motorista.
     *  @return Uma lista do historico das Viagens do Motorista.
    */
    public ArrayList<Viagem> getHistorico() {
        ArrayList<Viagem> novo = new ArrayList<Viagem>();
        for (Viagem v : this.historico) {
            novo.add(v.clone());
        }
        return novo;
    }
    
   
    /** Define a classificacao do Motorista. 
     *  @param eclass A classificacao para alterar para.
    */
    public void setClassificacao(int eclass) {
        int temp = (this.classificacao + eclass) / 2;
        this.classificacao = temp;}
    /** Define os kms feitos pelo Motorista. 
     *  @param ekmsf Os kms para alterar para.
    */
    public void setKmsFeitos(double ekmsf) {this.kmsfeitos += ekmsf;}
    /** Define a disponibilidade do Motorista. 
     *  @param edisp A disponibilidade para alterar para.
    */
    public void setDisponivel(boolean edisp) {this.disponivel = edisp;}
    /** Define o historico de Viagens do Motorista. 
     * @param ehistorico O historico das viagens.
     */
    public void setHistorico(ArrayList<Viagem> ehistorico) {
        this.historico.clear();
        for (Viagem v : ehistorico) {
            this.historico.add(v.clone());
        }
    }
    
    /** Metodo para transformar o historico das Viagens efetuadas pelo Motorista em String. 
     * @return Uma String com o historico das viagens.
     */
    public String datasViagemString() {
        StringBuilder str = new StringBuilder();
        str.append("O Motorista efetuou viagens nas seguintes datas: \n");
        for(Viagem v: this.historico) {
            str.append("Data: " + v.getDate().toLocalDate().toString() + "\n")
               .append("Hora: " + v.getDate().toLocalTime().toString() + "\n\n");
        }
        return str.toString();
    }
    
    /** Metodo que adiciona uma Viagem ao historico de Viagens do Cliente.
     * @param v Viagem a ser adicionada ao historico.
    */
    public void adicionaViagem(Viagem v){historico.add(v.clone());}
    

    /** Metodo para transformar a informacao das variaveis de instancia em String.
     *  @return Uma String com a info do Motorista.
    */
    public String toString() {
        StringBuilder str = new StringBuilder();
        str.append("O Motorista tem os seguintes dados: ")
            .append(getNome()+"\n")
            .append(getMorada()+"\n")
            .append(getData().toString()+"\n");
        return str.toString();
    }
    /** Metodo para clonar o Motorista.
     *  @return Um Motorista clonado atraves do construtor copia.
     */
    public Motorista clone() {return new Motorista(this);}
    /** Metodo para verificar se dois Motoristas sao iguais.
     *  @return Um boolean (true ou false).
     */
    public boolean equals(Object o) {
        if (this == o) {return true;}
        if (o == null || o.getClass() != this.getClass()) {return false;}
        Motorista teste = (Motorista) o;
        return teste.getEmail().equals(this.getEmail());
    }
}