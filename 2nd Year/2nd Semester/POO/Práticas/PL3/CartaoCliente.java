/**
 * Classe Cartao Cliente.
 * 
 * @author Diogo Nogueira.
 * @version 27.05.2017
 */


public class CartaoCliente
{
    /** Variáveis de Instância.*/
   
    private int valor;
    private int valorbonus;
    private int codigo;
    private int pontos;
    private String nome;
    private String menu1;
    private String menu2;
    
    /** Construtores. */
    
    /** Construtor vazio da classe CartaoCliente. */
    public CartaoCliente() {
        this.valor = 0;
        this.valorbonus = 0;
        this.codigo = 0;
        this.pontos = 0;
        this.nome = "NA";
    }
    
    
    /** Construtor parametrizado da classe CartaoCliente. */
    public CartaoCliente(int evalor, int evalorbonus, int ecodigo, int epontos, String enome) {
        this.valor = evalor;
        this.valorbonus = evalorbonus;
        this.codigo = ecodigo;
        this.pontos = epontos;
        this.nome = enome;
    }
    
    
    /** Construtor de cópia da classe CartaoCliente. */
    public CartaoCliente(CartaoCliente o) {
        this.valor = o.getValor();
        this.valorbonus = o.getValorBonus();
        this.codigo = o.getCodigo();
        this.pontos = o.getPontos();
        this.nome = o.getNome();
    }
       
    /** Métodos. */
    
    /** Métodos de Instância. */
    public int getValor() {return this.valor;}    
    public int getValorBonus() {return this.valorbonus;}
    public int getCodigo() {return this.codigo;}
    public int getPontos() {return this.pontos;}
    public String getNome() {return this.nome;}
    
    public void setNome(String enome) {this.nome = enome;}
    public void setValorBonus(int evalorbonus) {this.valorbonus = evalorbonus;}
    public void setPontos(int epontos) {this.pontos = epontos;}
    
    /** Métodos Complementares. */
    public CartaoCliente clone() {return new CartaoCliente(this);}
    public boolean equals(Object o) {
        if (this == o) {return true;}
        if(o == null || o.getClass() != this.getClass()) {return false;}
        CartaoCliente c = (CartaoCliente) o;
        return c.getNome() == nome;
    }
    
    /** Metodos Pedidos. */
    public void descontar(String menu) {
           if(menu.equals(this.menu1)) {this.pontos = this.pontos - 10;}
           else {this.pontos = this.pontos - 20;}}
}