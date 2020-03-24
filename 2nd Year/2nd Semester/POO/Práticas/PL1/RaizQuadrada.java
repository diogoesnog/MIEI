
/**
 * Ler n reais e calcular as respetivas raízes quadradas.
 */

import java.util.Scanner;
import java.lang.Math;

public class RaizQuadrada
{
    public static void main(String[] args){
        int n, i;
        double x,r;
        
        Scanner input = new Scanner(System.in);
        
        System.out.println("Quantos números pretende analisar?");
        n = input.nextInt();
        
        for(i=0; i<n; i++){
            System.out.println("Digite um número");
            x = input.nextDouble();
            r = Math.sqrt(x);
            System.out.println("A raíz quadrada de "+x+" é "+r);
        }
        
        input.close();
    }
}
