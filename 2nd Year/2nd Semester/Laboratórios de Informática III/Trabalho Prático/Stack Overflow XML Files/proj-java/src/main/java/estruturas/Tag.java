package estruturas;

/**
 * Classe que define aquilo que é uma Tag referente ao
 * ficheiro Tags.xml.
 *
 * @author  André Peixoto; Diogo Nogueira; Diogo Araújo; Filipe Cunha.
 * @version 3.0
 * @since   2018-05-25
 */

public class Tag {

    private long id;
    private String name;

    /**
     * Construtor de inicialização.
     */
    public Tag() {
        this.id = 0;
        this.name = null;
    }

    /**
     * Construtor de cópia.
     * @param novaTag Tag externa para fazer a cópia.
     */
    private Tag(Tag novaTag) {
        this.id = novaTag.getID();
        this.name = novaTag.getName();
    }

    /**
     * Get do ID.
     * @return O ID da Tag.
     */
    public long getID() {
        return this.id;
    }

    /**
     * Set do ID.
     * @param newID Novo ID a atribuir à Tag.
     */
    public void setID(long newID) {
        this.id = newID;
    }

    /**
     * Get do Name.
     * @return O Name do User.
     */
    public String getName() {
        return this.name;
    }

    /**
     * Set do Name.
     * @param newName Novo Name a atribuir à Tag.
     */
    public void setName(String newName) {
        this.name = newName;
    }

    /**
     * Método para clonar uma Tag.
     * @return Uma Tag clonada através do construtor de cópia.
     */
    public Tag clone() {
        return new Tag(this);
    }

    /**
     * Método para transformar a informação das variáveis de instância em String.
     * @return Uma String com a info da Tag.
     */
    public String toString() {
        return ("A Tag tem as seguintes informações:" + "\n") +
                "ID: " + this.getID() + "\n" +
                "Name: " + this.getName() + "\n";
    }

    /**
     * Método para verificar se duas Tags são iguais.
     * @return Um boolean (true ou false).
     */
    public boolean equals(Object o) {
        if (this == o) {
            return true;
        }
        if (o == null || o.getClass() != this.getClass()) {
            return false;
        }
        Tag teste = (Tag) o;
        return teste.getID() == (this.getID()) && teste.getName().equals(name);
    }

    /**
     * Método que devolve o código hash de uma Tag. Usado para otimizar a procura nas Collections.
     * @return Código hash de uma Tag.
     */
    public int hashCode() {
        int hash = 7;

        hash = 31 * hash + (int) (id ^ (id >>> 32));
        hash = 31 * hash + name.hashCode();
        hash = 31 * hash + name.hashCode();

        return hash;
    }
}