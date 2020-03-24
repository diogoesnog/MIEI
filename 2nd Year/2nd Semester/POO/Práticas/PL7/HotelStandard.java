
/**
 * Escreva a descrição da classe HotelStandard aqui.
 * 
 * @author (seu nome) 
 * @version (número de versão ou data)
 */
public class HotelStandard extends Hotel implements CartaoPonto
{
    private boolean epocaAlta;
    private int pontos;
    
    public HotelStandard(){
        super();
        this.epocaAlta = false;
    }
    
    public HotelStandard(HotelStandard hs){
        super(hs);
        this.epocaAlta = hs.getEpocaAlta();
        this.pontos = 0;
    }
    
    public HotelStandard(String codigo, String nome, String localidade, double precoBaseQuarto, int numQuartos, 
                         int estrelas, boolean epocaAlta, int pontos){
        super(codigo, nome, localidade, precoBaseQuarto, numQuartos, estrelas);
        this.epocaAlta = epocaAlta;
        this.pontos = pontos;
    }
    
    public boolean getEpocaAlta(){
        return this.epocaAlta;
    }
    
    public void setEpocaAlta(boolean e){
        this.epocaAlta = e;
    }
    
    public int getPontos(){
        return this.pontos;
    }
    
    public void setPontos(int p){
        this.pontos = pontos;
    }
    
    public double precoQuarto(){
        if(this.epocaAlta)  return (super.getPrecoBaseQuarto() + 20);
        
        else  return super.getPrecoBaseQuarto();
        
        // return super.getPrecoBaseQuarto() + (epocaAlta? 20 : 0);
    }
    
    public boolean equals(Object obj){
        if(obj == this) return true;
        if(obj == null || obj.getClass() != this.getClass()) return false;
        
        HotelStandard o = (HotelStandard) obj;
        return super.equals(o) && this.epocaAlta == o.getEpocaAlta() && this.pontos == o.getPontos();
    }
    
    public HotelStandard clone(){
        return new HotelStandard(this);
    }
    
    public String toString(){
        return super.toString()+"Época Alta: "+this.epocaAlta+"\n"+"Pontos: "+this.pontos;
    }
    
    public int compareTo(HotelStandard hs){
        int r = super.compareTo(hs);
        if(r == 0 && this.epocaAlta != hs.getEpocaAlta()) r = this.epocaAlta ? 1 : -1;
        
        return r;
    }
}
