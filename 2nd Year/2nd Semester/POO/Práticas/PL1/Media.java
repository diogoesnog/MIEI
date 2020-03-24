
/**
 * Lê 2 inteiros e apresenta-os por ordem decrescente, assim como a sua média.
 */

import java.util.Scanner;

public class Media
{
    public static void main(String[] args){
        int x, y, m;
        
        Scanner input = new Scanner(System.in);
        
        System.out.println("Digite o primeiro número");
        x = input.nextInt();
        
        System.out.println("Digit o segundo número");
        y = input.nextInt();
        
        m = (x + y) / 2;
        
        if (x > y) System.out.println("A média dos números "+x+" e "+y+" é "+m);
        else System.out.println("A média dos números "+y+" e "+x+" é "+m);
        
        input.close();
    }
}
