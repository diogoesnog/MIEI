
/**
 * Lê um nome e um saldo e imprime um texto com os resultados
 */

import java.util.Scanner;

public class ApresentarSaldo
{
    public static void main(String[] args){
        Scanner scan = new Scanner(System.in);
        
        String nome;
        int saldo;
        
        System.out.println("Digite o seu nome");
        nome = scan.nextLine();
        
        System.out.println("Digite o seu saldo");
        saldo = scan.nextInt();
        
        System.out.println("Olá "+nome+", o seu saldo é "+saldo);
        
        scan.close();
    }
}
