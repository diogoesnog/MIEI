package cesium;


public class Aluno 
{
    
    // Variáveis de Instância
    private String nome;
    private String numero;
    private String curso;
    private int ano;
    
    
    // Construtores
    
    // Construtor Vazio
    public Aluno() {
       this.nome = new String();
       this.numero = new String();
       this.curso = new String();
       this.ano = 0;
    }
    
    // Construtor Parametrizado
    public Aluno(String enumero, String enome, String ecurso, int eano) {
        this.numero = enumero;
        this.nome = enome;
        this.curso = ecurso;
        this.ano = eano;
     }


    // Métodos de Instância
    
    // Gets
    public String getNome() {
        return this.nome;
    }

    public String getNumero() {
        return this.numero;
    }

    public String getCurso() {
        return this.curso;
    }

    public int getAno() {
        return this.ano;
    }


    // Equals, Clone, toString
    public boolean equals(Object o) {
        boolean b=false;

        if (o!= null && o instanceof Aluno) {
            Aluno a = (Aluno)o;
            b = this.numero.equals(a.getNumero()) &&
                this.nome.equals(a.getNome()) &&
                this.curso.equals(a.getCurso())&&
                this.ano == a.getAno();
        }
        return b;
    }
    
    public Object clone() {
        return new Aluno(this.numero, this.nome, 
                                      this.curso, this.ano);
    }

    @Override
    public String toString() {
        StringBuilder sb = new StringBuilder("Aluno(");
        sb.append(this.numero);
        sb.append(",");
        sb.append(this.nome);
        sb.append(",");
        sb.append(this.curso);
        sb.append(",");
        sb.append(this.ano);
        sb.append(")");
        return sb.toString();
    }
}

