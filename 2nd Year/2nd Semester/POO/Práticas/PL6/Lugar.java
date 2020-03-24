/** 
 * Classe Lugar.
 * 
 * @author Diogo Nogueira.
 * @version 27.05.2017
 */

public class Lugar implements Comparable<Lugar>
{
    /** Variáveis de Instância.*/
        
    private String matricula;
    private String nome;
    private int minutos;
    private boolean permanente;
    
    
    /** Construtores. */
    
    /** Construtor vazio da classe Lugar. */
    public Lugar() {
        this.matricula = new String();
        this.nome = new String();
        this.minutos = 0;
        this.permanente = false;
    }
    
    /** Construtor parametrizado da classe Lugar. */
    public Lugar(String ematricula, String enome, int eminutos, boolean epermanente) {
        this.matricula = ematricula;
        this.nome = enome;
        this.minutos = eminutos;
        this.permanente = epermanente;
    }
    
    /** Construtor de copia da classe Lugar. */
    public Lugar(Lugar o) {
        this.matricula = o.getMatricula();
        this.nome = o.getNome();
        this.minutos = o.getMinutos();
        this.permanente = o.getPermanente();
    }
    
    
    /** Métodos. */
        
    /** Métodos de Instância. -> Gets e Sets. */
    public String getMatricula(){return this.matricula;}
    public String getNome(){return this.nome;}
    public int getMinutos(){return this.minutos;}
    public boolean getPermanente(){return this.permanente;}
    
    public void setMatricula(String matricula){this.matricula = matricula;}
    public void setNome(String nome){this.nome = nome;}
    public void setMinutos(int minutos){this.minutos = minutos;}
    public void setPermanente(boolean permanente){this.permanente = permanente;}
    
    /** Metodos Complementares. */
    public Lugar clone(){return new Lugar(this);}
    public String toString(){return "Lugar("+matricula+", "+nome+", "+minutos+", "+permanente+")";}
    public int compareTo(Lugar o){
        if(this.minutos > o.getMinutos()) {return 1;}
        
        else{
            if(this.minutos < o.getMinutos()) {return -1;}
             else {return 0;}
        }
    }
}