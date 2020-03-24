package estruturas;

import java.util.HashMap;

/**
 * Classe que define uma Hash com todas as Tags obtidas do
 * ficheiro Tags.xml aquando da realização do parse.
 *
 * @author  André Peixoto; Diogo Nogueira; Diogo Araújo; Filipe Cunha.
 * @version 3.0
 * @since   2018-05-25
 */

public class HashTags {

    private HashMap<String, Tag> tags;

    /**
     * Construtor de inicialização.
     */
    public HashTags() {
        this.tags = new HashMap<>();
    }

    /**
     * Get da Hash das Tags. Auxiliar aos construtores dai ser privado.
     * @return A Hash das Tags.
     */
    public HashMap<String, Tag> getHashTags() {
        HashMap<String, Tag> novoHashTags = new HashMap<>();

        for (Tag p : this.tags.values())
            novoHashTags.put(p.getName(), p.clone());

        return novoHashTags;
    }

    /**
     * Set para definir as Tags. Auxiliar aos construtores dai ser privado.
     * @param novoHashTags A nova Hash das Tags.
     */
    private void setHashTags(HashMap<String, Tag> novoHashTags) {
        for (Tag p : novoHashTags.values())
            this.tags.put(p.getName(), p.clone());
    }

    /**
     * Método para adicionar uma Tag à Hash das Tags.
     * @param tag Tag a adicionar.
     */
    public void adicionarTag(Tag tag) {
        this.tags.put(tag.getName(), tag.clone());
    }

    /**
     * Método para obter uma Tag através do seu ID.
     * @param chave ID da Tag que se pretende obter.
     * @return A Tag em questão.
     */
    public Tag obtemTag(String chave)  {
        return tags.get(chave);
    }

    /**
     * Método para transformar a informação das variáveis de instância em String.
     * @return Uma String com a info da Hash.
     */
    public String toString() {
        StringBuilder str = new StringBuilder();
        str.append("A estrutura contém os seguintes Tags:"+"\n");
        str.append("\n");
        str.append("\n");

        for (Tag p : this.tags.values()) {
            str.append(p).append("\n");
        }

        return str.toString();
    }

    /**
     * Método que liberta o conteúdo da Hash das Tags.
     */
    public void clear() {
        this.tags.clear();
    }
}
