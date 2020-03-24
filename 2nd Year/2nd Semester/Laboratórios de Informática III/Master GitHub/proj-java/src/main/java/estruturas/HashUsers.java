package estruturas;

import java.util.*;
import java.util.stream.Collectors;

/**
 * Classe que define uma Hash com todos os Users obtidos do
 * ficheiro Users.xml aquando da realização do parse.
 *
 * @author  André Peixoto; Diogo Nogueira; Diogo Araújo; Filipe Cunha.
 * @version 4.0
 * @since   2018-05-25
 */

public class HashUsers {

    private HashMap<Long, User> users;

    /**
     * Construtor de inicialização.
     */
    public HashUsers() {
        this.users = new HashMap<>();
    }

    /**
     * Get da Hash dos Users. Auxiliar aos construtores dai ser privado.
     * @return A Hash dos Users.
     */
    public HashMap<Long, User> getHashUsers() {
        HashMap<Long, User> novoHashUsers = new HashMap<>();

        for (User p : this.users.values())
            novoHashUsers.put(p.getID(), p.clone());

        return novoHashUsers;
    }

    /**
     * Set para definir os Users. Auxiliar aos construtores dai ser privado.
     * @param novoHashUsers Nova Hash de Users.
     */
    private void setHashUsers(HashMap<Long, User> novoHashUsers) {
        for (User p : novoHashUsers.values())
            this.users.put(p.getID(), p.clone());
    }

    /**
     * Método para obter um User da Hash.
     * @param idUser ID do User a obter.
     * @return User com o ID passado como parâmetro.
     */
    public User getUser(long idUser) {
        return users.get(idUser);
    }

    /**
     * Método que devolve uma lista dos N users com melhor reputação da HashUsers.
     * @param N Número máximo de Users a serem devolvidos.
     * @return Lista dos Users ordenados de modo decrescente pela reputação.
     */
    public List<User> getNUsersMelhorReputacao(int N){
        List<User> lista = users.values().stream()
                .sorted(Comparator.comparing(User::getReputation).reversed())
                .limit(N)
                .collect(Collectors.toList());
        return lista;
    }

    /**
     * Método para adicionar um User à Hash dos Users.
     * @param newUser User a adicionar.
     */
    public void adicionarUser(User newUser) {
        this.users.put(newUser.getID(), newUser);
    }

    /**
     * Método para obter um User através do seu ID.
     * @param chave ID do User que se pretende obter.
     * @return O User em questão.
     */
    public User obtemUser(Long chave)  {
        return users.get(chave);
    }

    /**
     * Método que adiciona um User à Hash.
     * @param userID ID do User que se pretende adicionar.
     */
    public void adicionaUserNPost(long userID) {
        if (users.containsKey(userID)) {
            User user = users.get(userID);
            user.incrementaNposts();
        }
    }

    /**
     * Método que adiciona um Post à Tree de Posts de cada User.
     * @param post Post a ser adicionado.
     * @param ownerID User a quem pertence o Post.
     */
    public void adicionaPostUserTree(Post post, Long ownerID) {
        User user = users.get(ownerID);
        user.addMyPost(post);
    }

    /**
     * Método para transformar a informação das variáveis de instância em String.
     * @return Uma String com a info da Hash.
     */
    public String toString() {
        StringBuilder str = new StringBuilder();
        str.append("A estrutura contém os seguintes Users:"+"\n");
        str.append("\n");
        str.append("\n");

        for (User p : this.users.values()) {
            str.append(p).append("\n");
        }

        return str.toString();
    }

    /**
     * Método que liberta o conteúdo da Hash dos Users.
     */
    public void clear() {
        this.users.clear();
    }
}
