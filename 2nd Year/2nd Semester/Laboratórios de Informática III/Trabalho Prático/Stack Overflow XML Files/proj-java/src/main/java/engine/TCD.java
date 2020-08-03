package engine;

import common.Pair;
import estruturas.*;
import li3.TADCommunity;

import java.time.LocalDate;
import java.util.ArrayList;
import java.util.HashMap;
import java.util.List;
import java.util.Map.Entry;
import java.util.stream.Collectors;

import static engine.Parse.parseDocs;
import static java.util.Collections.reverseOrder;

/**
 * Classe onde são definidas todas as queries referentes ao projeto.
 *
 * @author  André Peixoto; Diogo Nogueira; Diogo Araújo; Filipe Cunha.
 * @version 6.0
 * @since   2018-05-25
 * @see LocalDate
 */

public class TCD implements TADCommunity {

    private HashPosts posts;
    private HashUsers users;
    private TreePosts treePerg;
    private TreePosts treeRes;
    private HashTags tags;
    private TreeUserNPosts treeUserNPosts;

    /**
     * Método que inicializa as várias estruturas.
     */
    public TCD() {
        //MyLog qelog = new MyLog("queryengine");
        this.posts = new HashPosts();
        this.users = new HashUsers();
        this.tags = new HashTags();
        this.treePerg = new TreePosts();
        this.treeRes = new TreePosts();
        this.treeUserNPosts = new TreeUserNPosts();
    }

    /**
     * Método que armazena nas estruturas tudo o que é lido no Parse.
     * @param dumpPath Caminho de cada ficheiro XMl necessário passar aos métodos do Parse.
     */
    public void load(String dumpPath) {

        String caminhoPosts = dumpPath + "/Posts.xml";
        String caminhoUsers = dumpPath + "/Users.xml";
        String caminhoTags = dumpPath + "/Tags.xml";

        parseDocs(caminhoUsers, posts, tags, users, treePerg, treeRes);
        System.out.println("Parse dos Users concluído com sucesso.\n");

        parseDocs(caminhoPosts, posts, tags, users, treePerg, treeRes);
        System.out.println("Parse dos Posts concluído com sucesso.\n");

        parseDocs(caminhoTags, posts, tags, users, treePerg, treeRes);
        System.out.println("Parse das Tags concluído com sucesso.\n");

        treeUserNPosts.usersToTreeUserNPosts(users);
        System.out.println("Load  da TreeUserNPosts completo.\n");

        System.out.println("Posts:" + posts.getHashPosts().size());
        System.out.println("users:" + users.getHashUsers().size());
        System.out.println("Tags:" + tags.getHashTags().size());
        System.out.println("Perguntas:" + treePerg.getTreePosts().size());
        System.out.println(treeRes.getTreePosts().lastKey()); //que sentido faz isto?
        System.out.println("Respostas:" + treeRes.getTreePosts().size());

    }

    /**
     * Query 1.
     * Dado o identificador de um post, retorna o título do Post e o nome (não o ID)
     * de utilizador do autor.
     * @param id Identificador do Post.
     * @return Título do Post e nome do autor.
     */
    public Pair<String,String> infoFromPost(long id) {

        Post post = posts.obtemPost(id);
        String titulo = null;
        String nome = null;

        if(post.getTypeID() == 1) {
            long ownerUserID = post.getOwnerUserID();
            User user = users.obtemUser(ownerUserID);

            titulo = post.getTitle();
            nome = user.getName();
        }

        if(post.getTypeID() == 2) {
            long parentID = post.getParentID();
            Post newPost = posts.obtemPost(parentID);

            long ownerUserID1 = newPost.getOwnerUserID();
            User user = users.obtemUser(ownerUserID1);

            titulo = newPost.getTitle();
            nome = user.getName();
        }

        return new Pair<>(titulo,nome);
    }

    /**
     * Query 2.
     * Devolve o top N de utilizadores com maior número de Posts de sempre.
     * @param N Número máximo de IDs a obter.
     * @return Lista com os IDs dos top N de Users com maior número de Posts de sempre.
     */
    public List<Long> topMostActive(int N) {
        return treeUserNPosts.getFirstNKeys(N);
    }

    /**
     * Query 3.
     * Obtém o número total de Posts num determinado período de tempo.
     * @param begin Início do período de tempo.
     * @param end Fim do período de tempo.
     * @return Lists com o número total perguntas e respostas.
     */
    public Pair<Long,Long> totalPosts(LocalDate begin, LocalDate end) {

        long perguntas  = treePerg.obtemNumero(begin,end);
        long respostas = treeRes.obtemNumero(begin,end);

        return new Pair<>(perguntas,respostas);
    }

    /**
     * Query 4.
     * Devolve o ID de todas as perguntas inseridas num dado intervalo de tempo e
     * que contêm uma determinada Tag.
     * @param tag Tag que a pergunta deve conter.
     * @param begin Início do período de tempo.
     * @param end Fim do período de tempo.
     * @return Lista dos IDs das perguntas ordenadas em cronologia inversa.
     */
    public List<Long> questionsWithTag(String tag, LocalDate begin, LocalDate end) {
        return treePerg.obtemTagsIntervalo(tag,begin,end);
    }

    /**
     * Query 5.
     * Devolve a informação do perfil de um dado User e os IDs dos seus últimos 10 Posts.
     * @param id ID do User.
     * @return Informação do perfil do User e uma lista com os IDs dos seus últimos 10 Posts,
     * ordenados por cronologia inversa.
     */
    public Pair<String, List<Long>> getUserInfo(long id) {
        String shortBio = users.obtemUser(id).getBio();
        List<Long> ids = users.obtemUser(id).obtemNPosts(10);
        return new Pair<>(shortBio,ids);
    }

    /**
     * Query 6.
     * Devolve os IDs das N respostas com mais votos.
     * @param N Número máximo de IDs a obter.
     * @param begin Início do período de tempo.
     * @param end Fim do período de tempo.
     * @return Lista dos IDs das N respostas, ordenadas em ordem decrescente do número
     * de votos.
     */
    public List<Long> mostVotedAnswers(int N, LocalDate begin, LocalDate end) {
        return treeRes.obtemIDsScore(N,begin,end);
    }

    /**
     * Query 7.
     * Devolve os IDs das N perguntas com mais respostas.
     * @param N Número máximo de IDs a obter.
     * @param begin Início do período de tempo.
     * @param end Fim do período de tempo.
     * @return Lista dos IDs das N perguntas com mais respostas, em ordem decrescente
     * do número de respostas.
     */
    public List<Long> mostAnsweredQuestions(int N, LocalDate begin, LocalDate end) {
        return treePerg.obtemIDsPerguntas(N,begin,end);
    }

    /**
     * Query 8.
     * Devolve os IDs das N perguntas cujos títulos contenham uma determinada
     * palavra.
     * @param N Número máximo de IDs a obter.
     * @param word Palavra que o título da pergunta deve conter.
     * @return Lista dos IDs das N perguntas, ordenadas por cronologia inversa.
     */
    public List<Long> containsWord(int N, String word) {
        return treePerg.obtemIDsPalavra(N,word);
    }

    /**
     * Query 9.
     * Devolver os IDs das últimas N perguntas em que dois utilizadores estiveram
     * envolvidos.
     * @param N Número máximo de IDs a obter.
     * @param id1 ID do primeiro utilizador.
     * @param id2 ID do segundo utilizador.
     * @return Lista com os IDs das N perguntas, ordenadas por cronologia inversa.
     */
    public List<Long> bothParticipated(int N, long id1, long id2) {
        User user1 = users.getUser(id1);
        User user2 = users.getUser(id2);

        TreePosts postsUser1 = user1.getMyposts();
        TreePosts postsUser2 = user2.getMyposts();

        return TreePosts.obtemIDsPerguntas(postsUser1,postsUser2,N);
    }

    /**
     * Query 10.
     * Obter o ID da melhor resposta baseando num dado cálculo.
     * @param id ID da pergunta para a qual se quer obter a melhor resposta.
     * @return ID da melhor pergunta.
     */
    public long betterAnswer(long id) {
        return posts.obtemMelhorResposta(id, users);
    }

    /**
     * Query 11.
     * Devolve os IDs das N Tags mais usadas pelos N utilizadores com melhor reputação.
     * @param N Número máximo de IDs a obter.
     * @param begin Início do período de tempo.
     * @param end Fim do período de tempo.
     * @return Lista dos IDs das N Tags mais usadas, em ordem decrescente do número
     * de vezes em que a Tag foi usada.
     */
    public List<Long> mostUsedBestRep(int N, LocalDate begin, LocalDate end) {
        HashMap<String,Integer> hashtags = new HashMap<>();
        List<User> listUserBestRep = users.getNUsersMelhorReputacao(N);
        for(User u : listUserBestRep){
            u.getMyTagsIntervalo(begin,end,hashtags);
        }
        hashtags.remove("");

        List<Entry<String, Integer>> entries = new ArrayList<>(hashtags.entrySet());
        entries.sort(reverseOrder(Entry.comparingByValue()));

        List<Long> result = new ArrayList<>();

        for (Entry<String,Integer> entry : entries){
            result.add(tags.obtemTag(entry.getKey()).getID());
        }
        result = result.stream().limit(N).collect(Collectors.toList());
    return result;
    }

    /**
     * Método que liberta o conteúdo de todas as estruturas inicializadas.
     */
    public void clear(){
        this.posts.clear();
        this.users.clear();
        this.tags.clear();
        this.treePerg.clear();
        this.treeRes.clear();
        this.treeUserNPosts.clear();
    }
}
