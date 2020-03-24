
/**
 * Lê 10 inteiros e determina quantos são maior que 5,
 */

import java.util.Scanner;

public class QuantidadeMaior5
{
    public static void main(String[] agrs){
        int x, i, n=10, soma=0;
        
        Scanner input = new Scanner(System.in);
        
        for(i=0; i<n; i++){
            System.out.println("Digite um número");
            
            x = input.nextInt();
            
            if (x > 5) soma++;
        }
        
        System.out.println("Dos números apresentados, "+soma+" são superiores a 5");
        
        input.close();
    }
}
