package estruturas;

import java.util.*;

/**
 * Classe que define uma Hash com todos os Posts obtidos do
 * ficheiro Posts.xml aquando da realização do parse.
 *
 * @author  André Peixoto; Diogo Nogueira; Diogo Araújo; Filipe Cunha.
 * @version 5.0
 * @since   2018-05-25
 */

public class HashPosts {

    private HashMap<Long, Post> posts;

    /**
     * Construtor de inicialização.
     */
    public HashPosts() {
        this.posts = new HashMap<>();
    }

    /**
     * Get da Hash dos Posts. Auxiliar aos construtores dai ser privado.
     * @return A Hash dos Posts.
     */
    public HashMap<Long, Post> getHashPosts() {
        HashMap<Long, Post> novoHashPosts = new HashMap<>();

        for (Post p : this.posts.values())
            novoHashPosts.put(p.getID(), p.clone());

        return novoHashPosts;
    }

    /**
     * Método para adicionar um Post à Hash dos Posts.
     * @param post Post a adicionar.
     */
    public void adicionarPost(Post post) {
        this.posts.put(post.getID(), post);
    }

    /**
     * Método para obter um Post através do seu ID.
     * @param chave ID do Post que se pretende obter.
     * @return O Post em questão.
     */
    public Post obtemPost(Long chave)  {
        return posts.get(chave);
    }

    /**
     * Método que adiciona uma resposta à Tree de respostas do Post da pergunta correspondente.
     * @param postres Resposta a ser adicionada.
     */
    public void adicionaPostResTree(Post postres) {

        Post perg = new Post();

        if (posts.containsKey(postres.getParentID())) {
            perg = posts.get(postres.getParentID());
            perg.adicionaResposta(postres);
        } else {
            perg.setID(postres.getParentID());
            perg.adicionaResposta(postres);
            adicionarPost(perg);
        }
    }

    /**
     * Método que obtém a Tree de respostas de um determinado Post.
     * @param postid Post do ID que se pretende obter as respostas.
     * @param users Hash dos Users.
     * @return A melhor resposta consoante o pedido.
     */
    public long obtemMelhorResposta(long postid, HashUsers users) {
        Post post = obtemPost(postid);
        return post.getRespostas().obtemMelhorResposta(users);
    }

    /**
     * Método que verifica se um determinado Post existe na Hash.
     * @param post Post a verificar.
     * @return Boolean. Verdadeiro se existe. Falso se não.
     */
    public boolean contemPost(Post post) {
        return posts.containsKey(post.getID());
    }

    /**
     * Método para transformar a informação das variáveis de instância em String.
     * @return Uma String com a info da Hash.
     */
    public String toString() {
        StringBuilder str = new StringBuilder();
        str.append("A estrutura contém os seguintes Posts:"+"\n");
        str.append("\n");
        str.append("\n");

        for (Post p : this.posts.values()) {
            str.append(p).append("\n");
        }

        return str.toString();
    }

    /**
     * Método que liberta o conteúdo da Hash dos Posts.
     */
    public void clear() {
        this.posts.clear();
    }
}