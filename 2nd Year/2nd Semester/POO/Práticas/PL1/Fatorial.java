
/**
 * Calcula o fatorial de um inteiro recebido na main
 */

import java.lang.Integer;

public class Fatorial
{
    public static void main(String[] args){
        Integer x = Integer.valueOf(args[0]);
        int fact;
        
        fact = fatorial(x);
        
        System.out.println("O fatorial de "+x+" é "+fact);
        
    }
    
    public static int fatorial(int n){
        if(n == 1) return 1;
        else return (n * fatorial(n-1));
    }
}
