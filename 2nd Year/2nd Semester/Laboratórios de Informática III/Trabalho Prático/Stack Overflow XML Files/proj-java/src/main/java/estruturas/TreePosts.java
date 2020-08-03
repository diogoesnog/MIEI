package estruturas;

import java.time.LocalDate;
import java.util.*;
import java.util.Map.Entry;
import java.util.stream.Collectors;

/**
 * Classe que define uma Tree com todos os Posts. Esta Tree encontra-se
 * ordenada por datas. Assim, se os Posts tiverem a mesma data, estarão
 * situados no mesmo List de Posts.
 *
 * @author  André Peixoto; Diogo Nogueira; Diogo Araújo; Filipe Cunha.
 * @version 5.0
 * @since   2018-05-25
 * @see LocalDate
 */

public class TreePosts {

    private TreeMap<LocalDate, List<Post>> tree;

    /**
     * Construtor de inicialização.
     */
    public TreePosts() {
        Comparator<LocalDate> comparador = (a1, a2) -> (a1.compareTo(a2));
        this.tree = new TreeMap<>(comparador);
    }

    /**
     * Construtor de cópia.
     * @param novaTreePosts TreeMap externa para fazer a cópia.
     */
    private TreePosts(TreePosts novaTreePosts) {
        this.tree = novaTreePosts.getTreePosts();
    }

    /**
     * Get da Tree dos Posts. Auxiliar aos construtores daí ser privado.
     * @return A Tree dos Posts.
     */
    public TreeMap<LocalDate, List<Post>> getTreePosts() {
        Comparator<LocalDate> comparador = (a1, a2) -> (a1.compareTo(a2));
        TreeMap<LocalDate, List<Post>> novaTree = new TreeMap<>(comparador);

        for (Entry<LocalDate, List<Post>> entrySet : tree.entrySet()) {
            List<Post> aux = new ArrayList<>();
            for (Post p : entrySet.getValue()) {
                aux.add(p.clone());
            }
            novaTree.put(entrySet.getKey(), aux);
        }

        return novaTree;
    }

    /**
     * Método que adiciona a um HasMap as Tags dos Post da Tree usadas num determinado intervalo de tempo.
     * @param inicio Início do intervalo de tempo.
     * @param fim Fim do intervalo de tempo.
     * @param hashtags HashMap para a adição das Tags.
     */
    public void getTagsUsadasIntervalo(LocalDate inicio,LocalDate fim,HashMap<String,Integer> hashtags) {
        String[] tags;
        for (Entry<LocalDate, List<Post>> entry : tree.entrySet()) {
            if (entry.getKey().isAfter(fim))
                break;
            if (!entry.getKey().isBefore(inicio)) {
                for (Post p : entry.getValue()) {
                    if (p.getTypeID() == 1) {
                        tags = p.getTags().split("<|>");

                        for (String tag : tags) {
                            if (hashtags.containsKey(tag)) {
                                hashtags.put(tag, hashtags.get(tag) + 1);
                            } else
                                hashtags.put(tag, 1);
                        }
                    }
                }
            }
        }
    }

    /**
     * Set para definir os Posts. Auxiliar aos construtores daí ser privado.
     * @param novaTree Nova Tree de Posts.
     */
    private void setTreePosts(TreeMap<LocalDate, List<Post>> novaTree) {
        Comparator<LocalDate> comparador = (a1, a2) -> (a1.compareTo(a2));
        TreeMap<LocalDate, List<Post>> auxtree = new TreeMap<>(comparador);
        for (Entry<LocalDate, List<Post>> entry : novaTree.entrySet()) {
            List<Post> aux = new ArrayList<>();
            for (Post p : entry.getValue()) {
                aux.add(p.clone());
            }
            auxtree.put(entry.getKey(), aux);
        }
        tree = auxtree;
    }

    /**
     * Método para adicionar um Post à Tree dos Posts.
     * @param post Post a adicionar.
     */
    public void adicionarPost(Post post) {
        if (tree.containsKey(post.getDate())) {
            List<Post> aux = tree.get(post.getDate());
            aux.add(post);
        } else {
            List<Post> aux = new ArrayList<>();
            aux.add(post);
            tree.put(post.getDate(), aux);
        }
    }

    /**
     * Método que retorna uma Colection de Posts.
     * @return Uma Collection de Posts.
     */
    public Collection<Post> values() {
        Collection<Post> aux = new ArrayList<>();
        for (List<Post> list : tree.values()) {
            for (Post p : list) {
                aux.add(p.clone());
            }
        }
        return aux;
    }

    /**
     * Método que retorna um Set de um TreeMap.
     * @return Um Set de um TreeMap.
     */
    private Set<Entry<LocalDate, List<Post>>> entrySet() {return tree.entrySet();}

    /**
     * Método para retornar o tamanho da Tree de Posts.
     * @return Tamanho da Tree de Posts em questão.
     */
    private int tamanhoTree() {
        int result = 0;
        for (List<Post> list : tree.values()) {
            result += list.size();
        }
        return result;
    }

    /**
     * Método que obtém o número de perguntas/respostas da Tree em causa dentro de um dado período de tempo.
     * @param inicio Data de início do período.
     * @param fim Data de fim do período.
     * @return Número total de perguntas.
     */
    public Long obtemNumero(LocalDate inicio, LocalDate fim) {

        return tree.entrySet().stream().takeWhile(entry -> !entry.getKey().isAfter(fim)).filter(entry -> !entry.getKey().isBefore(inicio)).mapToLong(entry -> entry.getValue().size()).sum();
    }

    /**
     * Método que obtém uma Lista de IDs das perguntas que contenham uma determinada Tag num dado intervalo de tempo.
     * @param inicio Data de início do período.
     * @param fim Data de fim do período.
     * @param tag A tag para filtro das perguntas
     * @return Lista dos IDs ordenada por cronologia inversa.
     */
    public ArrayList<Long> obtemTagsIntervalo(String tag, LocalDate inicio, LocalDate fim) {

        ArrayList<Long> listaIDS = new ArrayList<>();

        for (Entry<LocalDate, List<Post>> entry : tree.entrySet()) {

            if (entry.getKey().isAfter(fim))
                break;
            if (!entry.getKey().isBefore(inicio)) {
                for (Post p : entry.getValue()) {
                    if (p.getTags().contains(tag)) {
                        listaIDS.add(p.getID());
                    }
                }
            }
        }

        Collections.reverse(listaIDS);
        return listaIDS;
    }

    /**
     * Método que obtém uma Lista de IDs das respostas com maior número de score num dado intervalo de tempo.
     * @param numero Valor máximo de elementos da lista a obter.
     * @param inicio Data de início do período.
     * @param fim Data de fim do período.
     * @return Lista dos IDs ordenada por ordem decrescente do score das respostas em causa.
     */
    public ArrayList<Long> obtemIDsScore(int numero, LocalDate inicio, LocalDate fim) {

        ArrayList<Post> listaPosts = new ArrayList<>();
        ArrayList<Long> listaIDS = new ArrayList<>();

        int indiceIDs = 0;

        for (Entry<LocalDate, List<Post>> entry : tree.entrySet()) {

            if (entry.getKey().isAfter(fim))
                break;
            if (!entry.getKey().isBefore(inicio))
                listaPosts.addAll(entry.getValue());
        }

        Comparator<Post> comparador = (Post1, Post2) -> (Post1.compararDoisPosts(Post2));
        listaPosts.sort(comparador);

        while (numero > 0) {
            Post p = listaPosts.get(indiceIDs);
            listaIDS.add(indiceIDs,p.getID());
            numero--;
            indiceIDs++;
        }

        return listaIDS;
    }

    /**
     * Método que obtém uma Lista de IDs das perguntas que contenham no seu título uma determinada palavra.
     * @param numero Valor máximo de elementos da lista a obter.
     * @param palavra Palavra que o título da pergunta tem de conter.
     * @return Lista dos IDs ordenada por cronologia inversa.
     */
    public ArrayList<Long> obtemIDsPalavra(int numero, String palavra) {

        ArrayList<Post> listaPosts = new ArrayList<>();
        ArrayList<Long> listaIDS = new ArrayList<>();

        int indiceIDs = 0;

        for (List<Post> list : tree.values()) {
            for (Post p : list) {
                if (p.getTitle().contains(palavra)) {
                    listaPosts.add(p);
                }
            }
        }

        Collections.reverse(listaPosts);

        while (numero > 0) {
            Post p = listaPosts.get(indiceIDs);
            listaIDS.add(indiceIDs,p.getID());
            numero--;
            indiceIDs++;
        }

        return listaIDS;
    }

    /**
     * Método que devolve o ID da melhor resposta.
     * @param users Hash dos Users.
     * @return ID da melhor resposta.
     */
    public long obtemMelhorResposta(HashUsers users) {

        double result = 0;
        long id = 0;

        for (List<Post> list : tree.values()) {
            for (Post p : list) {

                User user = users.getUser(p.getOwnerUserID());
                int reputation = user.getReputation();

                double calculo = (p.getScore() * 0.65) + (reputation * 0.25) + (p.getCommentCount() * 0.1);

                if (calculo > result) {
                    result = calculo;
                    id = p.getID();
                }
            }
        }
        return id;
    }

    /**
     * Método que obtém os IDs das N perguntas com mais respostas dentro de um dado intervalo de tempo.
     * @param numero Número máximo de IDs a obter.
     * @param inicio Data de início do período.
     * @param fim Data de fim do período.
     * @return Lista com os N IDs em ordem do número decrescente de respostas.
     */
    public List<Long> obtemIDsPerguntas(int numero, LocalDate inicio, LocalDate fim) {
        Comparator<Integer> compaux = (a1,a2)->(a1.compareTo(a2));
        TreeMap<Integer,List<Long>> treeaux = new TreeMap<>(compaux.reversed());

        for (Entry<LocalDate, List<Post>> entry : tree.entrySet()) {

            if (entry.getKey().isAfter(fim))
                break;
            if (!entry.getKey().isBefore(inicio)) {
                for (Post p : entry.getValue()) {
                    int tamanho = p.getRespostas().tamanhoTree();
                    if(treeaux.containsKey(tamanho)) {
                        List<Long> listaux = treeaux.get(tamanho);
                        listaux.add(p.getID());
                    }
                    else{
                        List<Long> listaux = new ArrayList<>();
                        listaux.add(p.getID());
                        treeaux.put(tamanho,listaux);
                    }
                }
            }
        }
        List<Long> ids = new ArrayList<>();
        for(List<Long> list : treeaux.values()){
            for (Long id : list){
                if(numero<=0) return ids;
                ids.add(id);
                numero --;
            }
        }
        return ids;

    }

    /**
     * Método que verifica se um Post é resposta a uma pergunta.
     * @param p1 Pergunta.
     * @param p2 Post para verificação.
     * @return Boolean. Verdadeiro se o segundo Post for uma resposta do primeiro.
     */
    private static boolean pergunta(Post p1, Post p2) {
        return p2.getParentID() == p1.getID();
    }

    /**
     * Método que verifica se dois posts correspondem à mesma pergunta.
     * @param p1 Primeiro Post.
     * @param p2 Segundo Post.
     * @return Boolean. Verdadeiro se os dois Posts corresponderem à mesma pergunta. Falso caso contrário.
     */
    private static boolean resposta(Post p1, Post p2) {
        return p2.getParentID() == p1.getParentID();
    }

    /**
     * Método que obtém os IDs das N perguntas entre o conjunto de Posts em que dois Users participam.
     * @param postsUser1 Tree de Posts do primeiro User.
     * @param postsUser2 Tree de Posts do segundo User.
     * @param numero Número máximo de IDs de perguntas a obter.
     * @return Lista das últimas N perguntas em que participaram os dois Users em comum.
     */
     public static List<Long> obtemIDsPerguntas (TreePosts postsUser1, TreePosts postsUser2, int numero) {

        HashSet<Long> perguntas = new HashSet<>();

         for (Entry<LocalDate, List<Post>> entrada1 : postsUser1.entrySet()) {

             for (Post p1 : entrada1.getValue()) {

                 for (Entry<LocalDate, List<Post>> entrada2 : postsUser2.entrySet()) {

                     for (Post p2 : entrada2.getValue()) {
                         if (p1.getTypeID()==1 && pergunta(p1,p2)) perguntas.add(p1.getID());
                         if (p2.getTypeID()==1 && pergunta(p2,p1)) perguntas.add(p2.getID());
                         if (p1.getTypeID()==2 && p2.getTypeID()==2 && resposta(p1,p2)) perguntas.add(p1.getParentID());

                     }
                 }
             }
         }
         return perguntas.stream().limit(numero).collect(Collectors.toList());
    }

    /**
     * Método para clonar uma Tree de Posts.
     * @return Uma Tree de Posts clonada através do construtor de cópia.
     */
    public TreePosts clone() {
        return new TreePosts(this);
    }

    /**
     * Método para transformar a informação das variáveis de instância em String.
     * @return Uma String com a info da Tree.
     */
    public String toString() {
        StringBuilder str = new StringBuilder();
        str.append("A estrutura contém os seguintes Posts:"+"\n");
        str.append("\n");
        str.append("\n");

        for (List<Post> list : this.tree.values())
            for (Post p : list) {
            str.append(p).append("\n");
        }

        return str.toString();
    }

    /**
     * Método que liberta o conteúdo da Tree dos Posts.
     */
    public void clear() {
        this.tree.clear();
    }
}


