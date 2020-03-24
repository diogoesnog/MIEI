
/**
 * Escreva a descrição da classe HotelPremium aqui.
 * 
 * @author (seu nome) 
 * @version (número de versão ou data)
 */
public class HotelPremium extends Hotel implements CartaoPonto
{
    private double taxaLuxo;
    private int pontos;
    
    public HotelPremium(){
        super();
        this.taxaLuxo = 0;
        this.pontos = 0;
    }
    
    public HotelPremium(String codigo, String nome, String localidade, double precoBaseQuarto, 
                        int numQuartos, int estrelas, double taxaLuxo, int pontos){
        super(codigo, nome, localidade, precoBaseQuarto, numQuartos, estrelas);
        this.taxaLuxo = taxaLuxo;
        this.pontos = pontos;
    }
    
    public HotelPremium(HotelPremium hp){
        super(hp);
        this.taxaLuxo = hp.getTaxaLuxo();
        this.pontos = hp.getPontos();
    }
    
    public double getTaxaLuxo(){
        return this.taxaLuxo;
    }
    
    public void setTaxaLuxo(double tl){
        this.taxaLuxo = tl;
    }
    
    public int getPontos(){
        return this.pontos;
    }
    
    public void setPontos(int p){
        this.pontos = p;
    }
    
    public double precoQuarto(){
        return this.getPrecoBaseQuarto() + this.taxaLuxo;
    }
    
    public boolean equals(Object obj){
        if(obj == this) return true;
        if(obj == null || obj.getClass() != this.getClass()) return false;
        
        HotelPremium o = (HotelPremium) obj;
        return super.equals(o) && this.taxaLuxo == o.getTaxaLuxo() && this.pontos == o.getPontos();
    }
    
    public String toString(){
        return super.toString()+"Taxa de Luxo: "+this.taxaLuxo+"\n"+"Pontos: "+this.pontos;
    }
    
    public HotelPremium clone(){
        return new HotelPremium(this);
    }
}