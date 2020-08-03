package estruturas;

import java.time.LocalDate;
import java.util.ArrayList;
import java.util.Collections;
import java.util.HashMap;
import java.util.List;
import java.util.stream.Collectors;

/**
 * Classe que define aquilo que é um User referente ao
 * ficheiro Users.xml.
 *
 * @author  André Peixoto; Diogo Nogueira; Diogo Araújo; Filipe Cunha.
 * @version 4.0
 * @since   2018-05-25
 * @see LocalDate
 */

public class User {

    private long id;
    private String name;
    private int reputation;
    private String bio;
    private int nposts;
    private TreePosts myposts;

    /**
     * Construtor de inicialização.
     */
    public User () {
        this.id = 0;
        this.name = null;
        this.reputation = 0;
        this.bio = null;
        this.nposts = 0;
        myposts = new TreePosts();
    }

    /**
     * Construtor de cópia.
     * @param novoUser User externo para fazer a cópia.
     */
    private User(User novoUser) {
        this.id = novoUser.getID();
        this.name = novoUser.getName();
        this.reputation = novoUser.getReputation();
        this.bio = novoUser.getBio();
        this.nposts = novoUser.getNposts();
        this.myposts = novoUser.getMyposts();
    }

    /**
     * Get do ID.
     * @return O ID do User.
     */
    public long getID() {
        return this.id;
    }

    /**
     * Get do número de Posts do User.
     * @return Número de Posts do User.
     */
    public int getNposts(){
        return nposts;
    }

    /**
     * Set do ID do User.
     * @param newID Novo ID do User.
     */
    public void setID(long newID){
        this.id = newID;
    }
    /**
     * Get do name.
     * @return O name do User.
     */
    public String getName() {
        return this.name;
    }

    /**
     * Set do Name do User.
     * @param newName Novo Name do User.
     */
    public void setName(String newName){
        this.name = newName;
    }

    /**
     * Get da Tree de Posts do User.
     * @return Tree de Posts do User.
     */
    public TreePosts getMyposts() {
        return myposts.clone();
    }

    /**
     * Get da Reputation do User.
     * @return A Reputation do User.
     */
    public int getReputation() {
        return this.reputation;
    }

    /**
     * Set da Reputation do User.
     * @param newReputation Nova Reputation do User.
     */
    public void setReputation(int newReputation) {
        this.reputation = newReputation;
    }

    /**
     * Get da Bio do User.
     * @return A Bio do User.
     */
    public String getBio() {
        return this.bio;
    }

    /**
     * Set da Bio do User.
     * @param newBio Nova Bio do User.
     */
    public void setBio(String newBio) {
        this.bio = newBio;
    }

    /**
     * Método para clonar um User.
     * @return Um User clonado através do construtor de cópia.
     */
    public User clone() {
        return new User(this);
    }

    /** Método para transformar a informação das variáveis de instância em String.
     *  @return Uma String com a info do User.
     */
    public String toString() {
        return ("O User tem as seguintes informações:" + "\n") +
                "ID: " + this.getID() + "\n" +
                "Name: " + this.getName() + "\n" +
                "Reputation: " + this.getReputation() + "\n" +
                "Bio: " + this.getBio() + "\n" +
                "Número de Posts: " + this.getNposts() + "\n";
    }

    /** Método para verificar se dois Users são iguais.
     *  @return Um boolean (true ou false).
     */
    public boolean equals(Object o) {
        if (this == o) {return true;}
        if (o == null || o.getClass() != this.getClass()) {return false;}
        User teste = (User) o;
        return teste.getID()==(this.getID());
    }

    /**
     * Método que incrementa o número de Posts do User.
     */
    public void incrementaNposts(){
        nposts++;
    }

    /**
     * Metodo que devolve uma lista com as IDs dos N Posts mais recenetes.
     * @param N Numero de posts a devolver.
     * @return Lista de que contem os N posts mais recentes.
     */
    public List<Long> obtemNPosts(int N){
        List <Long> ids = new ArrayList<>();
        for(Post p :myposts.values()){
            ids.add(p.getID());
        }
        ids.sort(Collections.reverseOrder());
        ids = ids.stream().limit(N).collect(Collectors.toList());
        return ids;
    }

    /**
     * Metodo que adiciona a uma HashMap as Tags usadas por este User num determindado intervalo de tempo.
     * @param inicio Início do intervalo de tempo.
     * @param fim Fim do intervalo de tempo.
     * @param hashtags Hash à qual as Tags serão adicionadas.
     */
    public void getMyTagsIntervalo(LocalDate inicio, LocalDate fim,HashMap<String,Integer> hashtags){
        myposts.getTagsUsadasIntervalo(inicio,fim,hashtags);
    }

    /**
     * Método que adiciona um Post à Tree de Posts do User.
     * @param post Post a adicionar.
     */
    public void addMyPost(Post post) {
        myposts.adicionarPost(post);
    }

    /**
     * Método que devolve o código hash de um User. Usado para otimizar a procura nas Collections.
     * @return Código hash de um User.
     */
    public int hashCode() {
        int hash = 7;

        hash = 31*hash + (int)(id^(id>>>32));
        hash = 31*hash + name.hashCode();
        hash = 31*hash + reputation;
        hash = 31*hash + bio.hashCode();

        return hash;
    }
}
