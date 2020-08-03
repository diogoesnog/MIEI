package configurafacil.business;

/**
 *
 * @author Todos
 */
public class Cliente {
    
    private String nome;
    private int NIF;
    private String morada;

    
    public Cliente(int NIF, String nome, String morada) {
        this.nome = nome;
        this.NIF = NIF;
        this.morada = morada;
    }

    
    public void setNome(String nome) {
        this.nome = nome;
    }

    public void setNIF(int NIF) {
        this.NIF = NIF;
    }

    public void setMorada(String morada) {
        this.morada = morada;
    }

    public String getNome() {
        return nome;
    }

    public int getNIF() {
        return NIF;
    }

    public String getMorada() {
        return morada;
    }
}
