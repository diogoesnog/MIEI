import java.util.HashMap;
import java.io.Serializable;

/**
 * Classe que ira estruturar num Map todos os Motoristas.
 * 
 * @author Diogo Araujo
 * @author Diogo Nogueira
 * @version 1.1
 */

public class ConjuntoMotorista implements Serializable
{
    /** Variaveis de Instancia. */
    private HashMap<String, Motorista> osmotoristas;
    
    /** Construtor vazio da classe ConjuntoMotorista. */
    public ConjuntoMotorista() {
        this.osmotoristas = new HashMap<String, Motorista>();
    }
    
    /** Construtor parametrizado da classe ConjuntoMotorista. 
     * @param eosmotoristas Map que agrupa cada um dos Motoristas com o seu respetivo email.
     */
    public ConjuntoMotorista (HashMap<String, Motorista> eosmotoristas) {
        this.osmotoristas = new HashMap<String, Motorista>();
        setOsMotoristas(eosmotoristas);
    }
    
    /** Construtor de copia da classe ConjuntoMotorista.
     * @param e ConjuntoMotorista externo para fazer a copia.
    */
    private ConjuntoMotorista (ConjuntoMotorista e) {
        this.osmotoristas = e.getOsMotoristas();
    }
    
    /** Get do Map dos Motoristas.
     * @return Um Map que agrupa cada um dos Motoristas com o seu respetivo email.
    */
    private HashMap<String, Motorista> getOsMotoristas() {
        HashMap<String, Motorista> returnado = new HashMap<String,Motorista>();
        for (Motorista m : this.osmotoristas.values()) 
            returnado.put(m.getEmail(),m.clone());
        return returnado;
    }
    
    /** Define o Map do conjuntos de Motoristas. 
     * @param eosmotoristas O Map do conjunto de Motoristas.
    */
    private void setOsMotoristas(HashMap<String, Motorista> eosmotoristas) {
        for (Motorista m : eosmotoristas.values()) 
            this.osmotoristas.put(m.getEmail(),m.clone());
    }
        
    /** Metodo para clonar o ConjuntoMotorista.
     *  @return Um ConjuntoMotorista novo.
     */
    public ConjuntoMotorista clone() {
        return new ConjuntoMotorista(this);
    }
    
    /** Metodo para introduzir um Motorista no Map de Clientes.
     * @param em Motorista a ser adicionado no Map.
    */
    public void adiciona(Motorista em) {
        osmotoristas.put(em.getEmail(), em.clone());
    }
    
    /** Metodo para fornecer o motorista consoante o Email dado.
     *  Utilizacao do get da Key e Value do HashMap<String, Motorista>.
     *  @return O motorista que contem aquele email.
     */
    public Motorista daMtEspecifico(String eemail) {
            return osmotoristas.get(eemail).clone();
    }
        
    /** Metodo para verificar se existe um Motorista inscrito no servico UMeR.
     * @param eemail Email que permite verificar a existencia do Motorista.
    */
    public boolean existeMotorista(String eemail) {
        return osmotoristas.containsKey(eemail);
    }
    
    /** Metodo para verificar se a password introduzida pelo Motorista se encontra correta.
     * @param eemail Email do Motorista.
     * @param epass Password do Motorista.
    */
    public boolean passwordCorreta(String eemail, String epass) {
        if (existeMotorista(eemail))
            return (osmotoristas.get(eemail).clone()).getPassword().equals(epass);
        else return false;
    }
    
    /** Metodo para alterar a disponibilidade de um Motorista consoante o seu email. 
     * @param email Email do Motorista em questao.
     * @param disponibilidade String da disponibilidade a impor.
     */
    public void disponibilidade(String email, String disponibilidade){
        if(disponibilidade.equalsIgnoreCase("S")) {
            Motorista temp = osmotoristas.get(email);
            temp.setDisponivel(true);
            osmotoristas.put(email, temp.clone());
        }
        if(disponibilidade.equalsIgnoreCase("N")) {
            Motorista temp = osmotoristas.get(email);
            temp.setDisponivel(false);
            osmotoristas.put(email, temp.clone());
        }
    }
    
    /** Metodo para eliminar um Motorista do conjunto consoante o seu email.
     * @param email Email do Motorista em questao.
     */
    public void eliminaM(String email){
        osmotoristas.remove(email);
    }
}