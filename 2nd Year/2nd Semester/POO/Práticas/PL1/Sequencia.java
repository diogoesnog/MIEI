
/**
 * Exercício 5
 */

import java.util.Scanner;

public class Sequencia
{
    public static void main(String[] args){
        int soma=0, x;
        int maior, menor;
        
        Scanner input = new Scanner(System.in);
        
        System.out.println("Digite os números");
        
        maior = menor = x = input.nextInt();
        
        while(x!=0){
            soma += x;
            if(x > maior) maior = x;
            if(x < menor) menor = x;
            
            x = input.nextInt();
        }
        
        System.out.println("A soma é: "+soma+". O número maior é "+maior+" e o menor é "+menor);
        
        input.close();
    }
}
