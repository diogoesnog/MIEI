import java.util.ArrayList;
import java.io.Serializable;
import java.awt.geom.Point2D.Float;

/**
 * Classe que ira estruturar um ArrayList de todas as Viaturas.
 * 
 * @author Diogo Araujo
 * @author Diogo Nogueira
 * @version 1.0
 */

public class ConjuntoViatura implements Serializable
{
    /** Variaveis de Instancia. */
    private ArrayList<Viatura> asviaturas;
    
    /** Construtor vazio da classe ConjuntoViatura. */
    public ConjuntoViatura() {
        this.asviaturas = new ArrayList<Viatura>();
    }
    
    /** Construtor parametrizado da classe ConjuntoViatura. 
     * @param easviaturas ArrayList de viaturas externas.
     */
    public ConjuntoViatura (ArrayList<Viatura> easviaturas) {
        this.asviaturas = new ArrayList<Viatura>();
        setAsViaturas(easviaturas);
    }
    
    /** Construtor de copia da classe ConjuntoViatura.
     * @param e ConjuntoViatura externo para fazer a copia.
    */
    public ConjuntoViatura (ConjuntoViatura e) {
        this.asviaturas = e.getAsViaturas();
    }
    
    /** Get do ArrayList das Viaturas.
     * @return Um ArrayList que agrupa as viaturas. 
    */
    public ArrayList<Viatura> getAsViaturas() {
        ArrayList<Viatura> returnado = new ArrayList<Viatura>();
        for (Viatura v : this.asviaturas) 
            returnado.add(v.clone());
        return returnado;
    }
    
    
    /** Define o ArrayList do conjuntos de Viaturas. 
     * @param easviaturas O ArrayList do conjunto de Viaturas.
    */
    public void setAsViaturas(ArrayList<Viatura> easviaturas) {
        this.asviaturas.clear();
        for (Viatura v : easviaturas) 
            this.asviaturas.add(v.clone());
    }
    
    public Viatura temViaturaMotorista(String emailmt) throws NaoTemViaturaException {
        boolean bool = false;
        Viatura viaturaesc = new Viatura();
        do { 
            for (Viatura v : this.asviaturas) {
                if (v.getMotorista().clone().getEmail().equals(emailmt)) 
                    if(v.getMotorista().clone().getDisponivel()) {
                        bool = true;    
                        viaturaesc = v.clone();
                        return viaturaesc;}
            }
        }
        while (!bool);
        if (bool) {
            asviaturas.remove(viaturaesc);
            return viaturaesc;}
        else throw new NaoTemViaturaException();
    }
    
    public void disponibilidade(String email, String disponibilidade) {
        if(disponibilidade.equalsIgnoreCase("S")) {
            for (Viatura v : this.asviaturas) {
            if (v.getMotorista().clone().getEmail().equals(email)) 
                {Motorista temp = v.getMotorista().clone();
                 temp.setDisponivel(true);
                 v.setMotorista(temp.clone());
                }
            }
        }
        if(disponibilidade.equalsIgnoreCase("N")) {
            for (Viatura v : this.asviaturas) {
            if (v.getMotorista().clone().getEmail().equals(email)) 
                {Motorista temp = v.getMotorista().clone();
                 temp.setDisponivel(false);
                 v.setMotorista(temp.clone());
                }
            }
        }
        }
    
    /** Metodo para clonar o ConjuntoViatura.
     *  @return Um ConjuntoViatura novo.
     */
    public ConjuntoViatura clone() {
        return new ConjuntoViatura(this);
    }
    
    /** Metodo para introduzir uma Viatura no ArrayList.
     * @param em Viatura a ser adicionado no ArrayList.
    */
    public void adiciona(Viatura em) {
        asviaturas.add(em.clone());
    }
}