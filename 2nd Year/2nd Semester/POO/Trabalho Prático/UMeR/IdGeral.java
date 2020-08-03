import java.time.LocalDate;
import java.io.Serializable;

/**
 * Classe da informacao generica dos utilizadores do servico UMeR.
 * 
 * @author Diogo Araujo
 * @author Diogo Nogueira
 * @version 1.5
 */

public abstract class IdGeral implements Serializable
{
    /** Variaveis de Instancia. */ 
    private String email;
    private String nome;
    private String password;
    private String morada;
    private LocalDate data;
    
    /** Construtor vazio da classe IdGeral. */
    public IdGeral() {
        this.email = "N/A";
        this.nome = "N/A";
        this.password = "N/A";
        this.morada = "N/A";
        this.data = LocalDate.now();
    }
    
    /** Construtor parametrizado da classe IdGeral. 
     *  @param eemail O email utilizado para criar uma identificacao.
     *  @param enome O nome do utilizador generico.
     *  @param epassword A password do utilizador generico.
     *  @param emorada A morada do utilizador generico.
     *  @param ano O ano de nascimento do utilizador generico.
     *  @param mes O mes de nascimento do utilizador generico.
     *  @param dia O dia de nascimento do utilizador generico.
     *  @see LocalDate
    */
    public IdGeral(String eemail, String enome, String epassword, String emorada, int ano, int mes, int dia) {
        this.email = eemail;
        this.nome = enome;
        this.password = epassword;
        this.morada = emorada;
        this.data = LocalDate.of(ano,mes,dia);
    }
    
    /** Construtor de copia da classe IdGeral. 
     *  @param a O IdGeral externo recebido para fazer a copia.
    */
    public IdGeral(IdGeral a) {
        this.email = a.getEmail();
        this.nome = a.getNome();
        this.password = a.getPassword();
        this.morada = a.getMorada();
        this.data = a.getData();
    }
    
    /** Get de instancia para o Email. 
     *  @return Retorna o email do IdGeral. 
    */
    public String getEmail() {return this.email;}
    /** Get de instancia para o Nome. 
     *  @return Retorna o nome do IdGeral. 
    */
    public String getNome() {return this.nome;}
    /** Get de instancia para password. 
     *  @return Retorna a password do IdGeral. 
    */
    public String getPassword() {return this.password;}
    /** Get de instancia para a morada. 
     *  @return Retorna a morada do IdGeral. 
    */
    public String getMorada() {return this.morada;}
    /** Get de instancia para a data de nascimento. 
     *  @return Retorna a data de nascimento do IdGeral.
     *  @see LocalDate
    */
    public LocalDate getData() {return this.data;}
    
    /** Set de instancia para o email.
     *  @param eemail O email utilizado para criar uma identificacao.
    */
    public void setEmail(String eemail) {this.email = eemail;}
    /** Set de instancia para o nome.
     *  @param enome O nome do utilizador generico.
    */
    public void setNome(String enome) {this.nome = enome;}
    /** Set de instancia para a password.
     *  @param epassword A password do utilizador generico.
     */
    public void setPassword(String epassword) {this.password = epassword;}
    /** Set de instancia para a morada.
     *  @param emorada A morada do utilizador generico.
     */
    public void setMorada (String emorada) {this.morada = emorada;}
    /** Set de instancia para a data de nascimento. 
     * @param ano O ano de nascimento do utilizador generico.
     * @param mes O mes de nascimento do utilizador generico.
     * @param dia O dia de nascimento do utilizador generico.
     * @see LocalDate
     */
    public void setData(int ano, int mes, int dia) {this.data = LocalDate.of(ano, mes, dia);}
    
    /** Metodo clone abstrato para ser implementado corretamente nas subclasses */
    public abstract IdGeral clone();
    /** Metodo toString abstrato para ser implementado corretamente nas subclasses */
    public abstract String toString();
    /** Metodo equals abstrato para ser implementado corretamente nas subclasses */
    public abstract boolean equals(Object o);
}