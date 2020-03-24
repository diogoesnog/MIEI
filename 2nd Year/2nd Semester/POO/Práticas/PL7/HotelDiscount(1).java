
/**
 * Escreva a descrição da classe HotelDiscount aqui.
 * 
 * @author (seu nome) 
 * @version (número de versão ou data)
 */
public class HotelDiscount extends HotelStandard
{
   private double ocupacao;
   
   public HotelDiscount(){
       super();
       this.ocupacao = 0;
   }
   
   public HotelDiscount(String codigo, String nome, String localidade, double precoBaseQuarto, int numQuartos, 
                         int estrelas, boolean epocaAlta, int pontos, double ocupacao){
       super(codigo, nome, localidade, precoBaseQuarto, numQuartos, estrelas, epocaAlta, pontos);
       this.ocupacao = ocupacao;
   }
   
   public HotelDiscount(HotelDiscount hd){
       super(hd);
       this.ocupacao = hd.getOcupacao();
   }
   
   public double getOcupacao(){
       return this.ocupacao;
   }
    
   public void setOcupacao(double o){
       this.ocupacao = ocupacao;
   }
   
   public HotelDiscount clone(){
       return new HotelDiscount(this);
   }
   
   public boolean equals(Object obj){
       if(obj == this) return true;
       if(obj == null || obj.getClass() != this.getClass()) return false;
        
       HotelDiscount o = (HotelDiscount) obj;
       return super.equals(o) && this.ocupacao == o.getOcupacao();
   }
   
   public String toString(){
       return super.toString()+"Ocupação: "+this.ocupacao;
   }
   
   public double precoQuarto(){
       float perc = (float) (1 - (super.getNumeroQuartos() - this.ocupacao));
       double pb = super.precoQuarto();
       return pb*0.5 + (perc>0.5 ? pb*0.8*(perc-0.5) : 0);
   }
}
