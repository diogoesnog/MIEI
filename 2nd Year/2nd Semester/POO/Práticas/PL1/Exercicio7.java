
/**
 * Exercício 7
 */

import java.time.LocalDateTime;
import java.math.*;
import java.text.*;

public class Exercicio7
{
   public static void main(String[] args){
       long dif;
       
       LocalDateTime instante1 = LocalDateTime.now();
       System.out.println(instante1.toString());
       
       System.out.println(factMillion(new BigDecimal("1E+6")));
       
       LocalDateTime instante2 = LocalDateTime.now();
       System.out.println(instante2.toString());
       
       dif = instante2.getNano() - instante1.getNano();
       
    }
    
   public static String factMillion(BigDecimal n){
      BigDecimal res = BigDecimal.ONE;

      DecimalFormat formatter = new DecimalFormat("0.###E0");

      while(n.compareTo(BigDecimal.ZERO)!=0){
          res=res.multiply(n);
          n=n.subtract(BigDecimal.ONE);

        }
      
      return formatter.format(res);
    }
}
