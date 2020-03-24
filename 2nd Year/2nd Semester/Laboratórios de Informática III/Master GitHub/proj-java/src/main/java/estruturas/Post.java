package estruturas;

import java.time.LocalDate;

/**
 * Classe que define aquilo que é um Post referente ao
 * ficheiro Posts.xml.
 *
 * @author  André Peixoto; Diogo Nogueira; Diogo Araújo; Filipe Cunha.
 * @version 5.0
 * @since   2018-05-25
 * @see LocalDate
 */

public class Post {

    private long id;
    private int typeID;
    private long ownerUserID;
    private long parentID;
    private String title;
    private LocalDate date;
    private String tags;
    private long score;
    private int commentCount;
    private TreePosts respostas;


    /**
     * Construtor de inicialização.
     */
    public Post() {
        this.id = 0;
        this.typeID = 0;
        this.ownerUserID = 0;
        this.parentID = 0;
        this.title = null;
        this.date = null;
        this.tags = null;
        this.score = 0;
        this.commentCount = 0;
        respostas = new TreePosts();
    }

    /**
     * Construtor de cópia.
     * @param novoPost Post externo para fazer a cópia.
     */
    private Post(Post novoPost) {
        this.id = novoPost.getID();
        this.typeID = novoPost.getTypeID();
        this.ownerUserID = novoPost.getOwnerUserID();
        this.parentID = novoPost.getParentID();
        this.title = novoPost.getTitle();
        this.date = novoPost.getDate();
        this.tags = novoPost.getTags();
        this.score = novoPost.getScore();
        this.commentCount = novoPost.getCommentCount();
        this.respostas = novoPost.getRespostas();
    }

    /**
     * Get do ID.
     * @return O ID do Post.
     */
    public long getID() {
        return this.id;
    }

    /**
     * Set do ID
     *
     * @param x Novo ID do Post.
     */

    public void setID(long x){
        id = x;
    }

    /**
     * Get das Respostas.
     *
     * @return a Tree de respsotas do Post.
     */
    public TreePosts getRespostas() {
        return respostas.clone();
    }

    /**
     * Set da Tree de respostas do Post.
     *
     * @param c Nova Tree de resposta do Post.
     */
    public void setRespostas(TreePosts c) {
        respostas = c.clone();
    }

    /**
     * Get do CommentCount
     * @return O CommentCount do Post.
     */
    public int getCommentCount(){
        return commentCount;
    }

    /**
     * Set do CommentCount.
     *
     * @param x Novo ComentCount do Post.
     */
    public void setCommentCount(int x){
        commentCount = x;
    }

    /**
     * Get do TypeID.
     * @return O TypeID do Post.
     */
    public int getTypeID() {
        return this.typeID;
    }

    /**
     * Set do TypeID.
     *
     * @param x Novo TypeID do Post.
     */
    public void setTypeID(int x){
        typeID = x;
    }
    /**
     * Get do OwnerUserID.
     * @return O OwnerUserID do Post.
     */
    public long getOwnerUserID() {
        return this.ownerUserID;
    }

    /**
     * Set do OwnerUserID
     *
     * @param x Novo OwnerUserID do Post.
     */
    public void setOwnerUserID(long x) {
        ownerUserID = x;
    }

    /**
     * Get do ParentID.
     * @return O ParentID do Post.
     */
    public long getParentID() {
        return this.parentID;
    }

    /**
     * Set do ParentID
     *
     * @param x Novo ParentID do Post.
     */
    public void setParentID(long x){
        parentID = x;
    }

    /**
     * Get do Title.
     * @return O Title do Post.
     */
    public String getTitle() {
        return this.title;
    }

    /**
     * Set do Title do Post.
     * @param x Novo Title do Post.
     */
    public void setTitle(String x) {
        title = x;
    }

    /**
     * Get do Date.
     * @return A data do Post.
     */
    public LocalDate getDate() {
        return this.date;
    }

    /**
     * Set da Date.
     * @param x Nova Date do Post.
     */
    public void setDate(LocalDate x) {
        date = x;
    }
    /**
     * Get das Tags.
     * @return As tags do Post.
     */
    public String getTags() {
        return this.tags;
    }

    /**
     * Set das Tags.
     * @param tags Novas Tags do Post.
     */
    public void setTags(String tags) {
        this.tags = tags;
    }

    /**
     * Get do Score.
     * @return O Score do Post.
     */
    public long getScore() {
        return this.score;
    }

    /**
     * Set do Score
     * @param score Novo Score do Post.
     */
    public void setScore(long score) {
        this.score = score;
    }

    /**
     * Metodo que Adiciona uma Resposta à Tree de Respostas do Post.
     * @param res Resposta a Adicionar.
     */
    public void adicionaResposta(Post res) {
        respostas.adicionarPost(res);
    }

    /**
     * Método para clonar um Post.
     * @return Um Post clonado através do construtor de cópia.
     */
    public Post clone() {
        return new Post(this);
    }

    /** Método para transformar a informação das variáveis de instância em String.
     *  @return Uma String com a info do Post.
     */
    public String toString() {
        return ("O Post tem as seguintes informações:" + "\n") +
                "ID: " + this.getID() + "\n" +
                "Type ID: " + this.getTypeID() + "\n" +
                "Owner User ID: " + this.getOwnerUserID() + "\n" +
                "Parent ID: " + this.getParentID() + "\n" +
                "Title: " + this.getTitle() + "\n" +
                "Date: " + this.getDate() + "\n" +
                "Tags: " + this.getTags() + "\n" +
                "Score: " + this.getScore() +"\n";
    }


    public int compararDoisPosts(Post p1) {
        return Long.compare(p1.getScore(), this.getScore());
    }

    /** Método para verificar se dois Posts são iguais.
     *  @return Um boolean (true ou false).
     */
    public boolean equals(Object o) {
        if (this == o) {return true;}
        if (o == null || o.getClass() != this.getClass()) {return false;}
        Post teste = (Post) o;
        return teste.getID()==(this.getID());
    }

    /**
     * Método que devolve o código hash de um Post. Usado para otimizar a procura nas Collections.
     * @return Código hash de um Post.
     */
    public int hashCode() {
        int hash = 7;

        hash = 31*hash + (int)(id^(id>>>32));
        hash = 31*hash + typeID;
        hash = 31*hash + (int)(ownerUserID^(ownerUserID>>>32));
        hash = 31*hash + (int)(parentID^(parentID>>>32));
        hash = 31*hash + title.hashCode();

        return hash;
    }
}
