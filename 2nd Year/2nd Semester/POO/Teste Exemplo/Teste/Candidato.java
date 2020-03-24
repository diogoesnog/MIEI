import java.util.*;

/**
 * Classe Candidato.
 *
 * @author Diogo Nogueira.
 * @version 29.05.2017.
 */

public class Candidato
{
    private String nome;
    private int idade;

    public Candidato(Candidato c)
    {
        this.nome = c.getNome();
        this.idade = c.getIdade();
    }

    public String getNome(){return this.nome;}
    public int getIdade(){return this.idade;}
    
    public int compareTo(Candidato c) {
        return this.nome.compareTo(c.getNome());
    }
    
    public Candidato clone(){return new Candidato(this);}
}
