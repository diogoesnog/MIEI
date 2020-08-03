import java.util.Map;
import java.util.HashMap;
import java.io.Serializable;

/**
 * Classe que ira estruturar num Map todos os clientes.
 * 
 * @author Diogo Araujo
 * @author Diogo Nogueira
 * @version 1.1
 */

public class ConjuntoCliente implements Serializable
{
    /** Variaveis de Instancia. */
    private HashMap<String, Cliente> osclientes;
    
    /** Construtor vazio da classe ConjuntoCliente. */
    public ConjuntoCliente() {
        this.osclientes = new HashMap<String, Cliente>();
    }
    
    /** Construtor parametrizado da classe ConjuntoCliente. 
     * @param eosclientes Map que agrupa cada um dos Clientes com o seu respetivo email.
     */
    public ConjuntoCliente (HashMap<String, Cliente> eosclientes) {
        this.osclientes = new HashMap<String, Cliente>();
        setOsClientes(eosclientes);
    }
    
    /** Construtor de copia da classe ConjuntoCliente.
     * @param e ConjuntoCliente externo para fazer a copia.
    */
    private ConjuntoCliente (ConjuntoCliente e) {
        this.osclientes = e.getOsClientes();
    }
    
    /** Get do Map dos Clientes.
     * @return Um Map que agrupa cada um dos Clientes com o seu respetivo email.
    */
    private HashMap<String, Cliente> getOsClientes() {
        HashMap<String, Cliente> returnado = new HashMap<String,Cliente>();
        for (Cliente c : this.osclientes.values()) 
            returnado.put(c.getEmail(),c.clone());
        return returnado;
    }
    
    /** Define o Map do conjuntos de Clientes. 
     * @param eosclientes O Map do conjunto de Clientes.
    */
    private void setOsClientes(HashMap<String, Cliente> eosclientes) {
        for (Cliente c : eosclientes.values()) 
            this.osclientes.put(c.getEmail(),c.clone());
    } 
    
     /** Metodo para clonar o ConjuntoCliente.
     *  @return Um ConjuntoCliente novo.
     */
    public ConjuntoCliente clone() {
        return new ConjuntoCliente(this);
    }
    
    /** Metodo para introduzir um Cliente no Map de Clientes.
     * @param ecl Cliente a ser adicionado no Map.
    */
    public void adiciona(Cliente ecl) {
        osclientes.put(ecl.getEmail(), ecl.clone());
    }
    
    /** Metodo para fornecer o motorista consoante o Email dado.
     *  Utilizacao do get da Key e Value do HashMap<String, Cliente>.
     *  @return O Cliente que contem aquele email.
     */
    public Cliente daCEspecifico(String eemail) {
            return osclientes.get(eemail).clone();
    }
    
    /** Metodo para verificar se existe um Cliente inscrito no servico UMeR.
     * @param eemail Email que permite verificar a existencia do Cliente.
    */
    public boolean existeCliente(String eemail) {
        return osclientes.containsKey(eemail);
    }
    
    /** Metodo para verificar se a password introduzida pelo Cliente se encontra correta.
     * @param eemail Email do Cliente.
     * @param epass Password do Cliente.
    */
    public boolean passwordCorreta(String eemail, String epass) {
        if (existeCliente(eemail))
            return (osclientes.get(eemail).clone()).getPassword().equals(epass);
        else return false;
    }
    
     /** Metodo para eliminar um Cliente do conjunto consoante o seu email.
     * @param email Email do Cliente em questao.
     */
    public void eliminaC(String email){
        osclientes.remove(email);
    }
}