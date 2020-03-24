/**
 * Classe Complexo.
 * 
 * @author Diogo Nogueira.
 * @version 27.05.2017
 */


public class Complexo
{
    /** Variáveis de Instância.*/
   
    private double real;
    private double img;
    
    /** Construtores. */
    
    /** Construtor vazio da classe Veículo. */
    public Complexo() {
        this.real = 1;
        this.img = 1;
    }
    
    
    /** Construtor parametrizado da classe Veículo. */
    public Complexo(double creal, double cimaginario) {
        this.real = creal;
        this.img = cimaginario;
    }
    
    
    /** Construtor de cópia da classe Veículo. */
    public Complexo(Complexo o) {
        this.real = o.getReal();
        this.img = o.getImg();
    }
       
    /** Métodos. */
    
    /** Métodos de Instância. */
    public double getReal() {return real;}    
    public double getImg() {return img;}
    
    public void setReal(double creal) {this.real = creal;}
    public void setImg(double cimg) {this.img = cimg;}
    
    /** Métodos Complementares. */
    public Complexo clone() {return new Complexo(this);}
    public String toString() {return "Complexo:" + real + " " + img;}
    public boolean equals(Object o) {
        if (this == o) {return true;}
        if(o == null || o.getClass() != this.getClass()) {return false;}
        Complexo c = (Complexo) o;
        return c.getReal() == real  &&  c.getImg() == img;
    }
    
    /** Metodos Pedidos. */
    public Complexo conjugado() {
        double newreal = this.real;
        double newimg = -this.img;
        
        return new Complexo(newreal, newimg);
    }
    
    public Complexo soma(Complexo ecomplexo) {
        double newreal = this.real + ecomplexo.getReal();
        double newimg = this.img + ecomplexo.getImg();
        
        return new Complexo(newreal, newimg);
    }
    
    public Complexo produto(Complexo ecomplexo) {
        double newreal = (this.real * ecomplexo.getReal()) - (this.img * ecomplexo.getImg());
        double newimg = (this.img * ecomplexo.getReal()) - (this.real * ecomplexo.getImg());
        
        return new Complexo(newreal, newimg);
    }
    
    public Complexo reciproco(Complexo ecomplexo) {
        double newreal = (this.real) / ((this.real * this.real) + (this.img * this.img));
        double newimg = (this.img) / ((this.real * this.real) + (this. img * this.img));
        
        return new Complexo(newreal, -newimg);        
    }
}