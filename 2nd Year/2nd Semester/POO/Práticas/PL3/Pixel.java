/**
 * Classe Pixel.
 * 
 * @author Diogo Nogueira.
 * @version 27.05.2017
 */


public class Pixel
{
    /** Variáveis de Instância.*/
   
    private double x, y;
    private int cor;
    
    /** Construtores. */
    
    /** Construtor vazio da classe Pixel. */
    public Pixel() {
        this.x = 0;
        this.y = 0;
        this.cor = 0;
    }
    
    
    /** Construtor parametrizado da classe Pixel. */
    public Pixel(double ex, double ey, int ecor) {
        this.x = ex;
        this.y = ey;
        this.cor = ecor;
    }
    
    /** Construtor de cópia da classe Pixel. */
    public Pixel(Pixel o) {
        this.x = o.getX();
        this.y = o.getY();
        this.cor = o.getCor();
    }
       
    /** Métodos. */
    
    /** Métodos de Instância. */
    public double getX() {return this.x;}
    public double getY() {return this.y;}
    public int getCor() {return this.cor;}
    
    public void setX(double ex) {this.x = ex;}
    public void setY(double ey) {this.y = ey;}
    public void setCor(int ecor) {this.cor = ecor;}
    
    /** Métodos Complementares. */
    public Pixel clone() {return new Pixel(this);}
    public String toString() {return "Pixel:" + this.x + " " + this.y + " " + this.cor;}
    public boolean equals(Object o) {
        if (this == o) {return true;}
        if(o == null || o.getClass() != this.getClass()) {return false;}
        Pixel c = (Pixel) o;
        return c.getX() == x  &&  c.getY() == y && c.getCor() == cor;
    }
    
    /** Metodos Pedidos. */
    public void desloca(double ex, double ey) {
        this.x = this.x + ex;
        this.y = this.y + ey;
    }
    
    public void mudarCor(int ecor) {
        if(ecor >= 0 && ecor <= 15) this.cor = ecor;
    }
   
    public String nomeCor() {
        if(this.cor == 0) return ("Pixel preto");
        if(this.cor == 1) return ("Pixel azul marinho");
        if(this.cor == 2) return ("Pixel verde escuro");
        if(this.cor == 3) return ("Pixel azul petróleo");
        if(this.cor == 4) return ("Pixel castanho");
        if(this.cor == 5) return ("Pixel púrpura");
        if(this.cor == 6) return ("Pixel verde oliva");
        if(this.cor == 7) return ("Pixel cinza claro");
        if(this.cor == 8) return ("Pixel cinza escuro");
        if(this.cor == 9) return ("Pixel azul");
        if(this.cor == 10) return ("Pixel verde");
        if(this.cor == 11) return ("Pixel azul turquesa");
        if(this.cor == 12) return ("Pixel vermelho");
        if(this.cor == 13) return ("Pixel fúscia");
        if(this.cor == 14) return ("Pixel amarelo");
        if(this.cor == 15) return ("Pixel branco");
        
        else return("A cor atual do Pixel não está no sistema.");
    }
}