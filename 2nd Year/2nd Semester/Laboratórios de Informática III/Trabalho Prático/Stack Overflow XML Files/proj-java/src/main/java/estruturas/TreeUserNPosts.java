package estruturas;

import java.util.*;
import java.util.Map.Entry;

/**
 * Classe que define uma Tree com todos os Users. Esta Tree encontra-se
 * ordenada por número de Posts. Assim, se os Users tiverem o mesmo número
 * de Posts, estarão situados no mesmo List de Users.
 *
 * @author  André Peixoto; Diogo Nogueira; Diogo Araújo; Filipe Cunha.
 * @version 5.0
 * @since   2018-05-25
 */

public class TreeUserNPosts {

    private TreeMap<Integer, List<User>> tree;

    /**
     * Construtor de inicialização.
     */
    public TreeUserNPosts() {
        Comparator<Integer> comparador = (a1, a2) -> (a1.compareTo(a2));
        this.tree = new TreeMap<>(comparador.reversed());
    }

    /**
     * Construtor de cópia.
     * @param novaTreeUserNPosts TreeMap externa para fazer a cópia.
     */
    private TreeUserNPosts(TreeUserNPosts novaTreeUserNPosts) {
        this.tree = novaTreeUserNPosts.getTree();
    }

    /**
     * Get da Tree dos Users ordenados por número de Posts. Auxiliar aos construtores dai ser privado.
     * @return A Tree dos Users ordenados por número de Posts.
     */
    private TreeMap<Integer, List<User>> getTree() {
        Comparator<Integer> comparador = (a1, a2) -> (a1.compareTo(a2));
        TreeMap<Integer, List<User>> novaTree = new TreeMap<>(comparador.reversed());

        for (Entry <Integer,List<User>> entry: tree.entrySet()){
            List<User> aux = new ArrayList<>();
            for (User u : entry.getValue()){
                aux.add(u.clone());
            }
            novaTree.put(entry.getKey(), aux);
        }
        return novaTree;
    }

    /**
     * Set para definir os Users ordenados por número de Posts. Auxiliar aos construtores dai ser privado.
     * @param novaTree Nova Tree dos Users ordenados por número de Posts.
     */
    private void setTree(TreeMap<Integer, List<User>> novaTree) {
        Comparator<Integer> comparador = (a1, a2) -> (a1.compareTo(a2));
        TreeMap<Integer, List<User>> auxtree = new TreeMap<>(comparador.reversed());
        for (Entry <Integer,List<User>> entry: tree.entrySet()) {
            List<User> aux = new ArrayList<>();
            for (User u : entry.getValue()) {
                aux.add(u.clone());
            }
            auxtree.put(entry.getKey(), aux);
        }
        tree = auxtree;
    }

    /**
     * Método para adicionar um User à Tree dos Users ordenados por número de Posts.
     * @param user User a adicionar.
     */
    private void adicionarUser(User user) {
        if (tree.containsKey(user.getNposts())) {
            List<User> aux = tree.get(user.getNposts());
            aux.add(user);
        } else {
            List<User> aux = new ArrayList<>();
            aux.add(user);
            tree.put(user.getNposts(), aux);
        }
    }

    /**
     * Método que óbtem os primeiros N IDs dos Users da Tree de Users ordenados por número de Posts.
     * @param N Número máximo de IDs a obter.
     * @return Lista com os N primeiros IDs.
     */
    public List<Long> getFirstNKeys(int N){
        List<Long> nUsers = new ArrayList<>();
        for(List<User> list: tree.values()){
             for(User u : list) {
                 if (N <= 0) return nUsers;
                 nUsers.add(u.getID());
                 N--;
             }
        }
        return nUsers;
    }

    /**
     * Metodo que adiciona os elementos de uma HashUser para a Tree de Users ordenados por número de Posts.
     * @param users Hash de Users ser que contém os Users a serem adicionados.
     */
    public void usersToTreeUserNPosts(HashUsers users) {
        for (User u : users.getHashUsers().values()) {
            adicionarUser(u);
        }
    }

    /**
     * Método para clonar uma Tree de Users ordenados por número de Posts.
     * @return Uma Tree de Users ordenados por número de Posts clonada através do construtor de cópia.
     */
    public TreeUserNPosts clone() {
        return new TreeUserNPosts(this);
    }

    /** Método para transformar a informação das variáveis de instância em String.
     *  @return Uma String com a info dos da Tree dos Users ordenados por número de Posts.
     */
    public String toString() {
        StringBuilder str = new StringBuilder();
        str.append("A estrutura contém os seguintes Posts:" + "\n");
        str.append("\n");
        str.append("\n");

        for (List<User> list : this.tree.values())
            for (User u : list) {
                str.append(u).append("\n");
        }

        return str.toString();
    }

    /**
     * Método que liberta o conteúdo da Tree dos Users ordenados por número de Posts.
     */
    public void clear() {
        this.tree.clear();
    }
}