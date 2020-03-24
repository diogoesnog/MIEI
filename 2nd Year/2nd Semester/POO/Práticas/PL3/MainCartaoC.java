import java.util.Scanner;

/**
 * Main para testar a Classe Complexo.
 * 
 * @author Diogo Nogueira.
 * @version 27.05.2017
 */

public class MainCartaoC
{
    public static Scanner scan = new Scanner(System.in);
    public static void main(String [] args){
        String nome;
        String menu;
        int pontos;
        
        CartaoCliente vazio = new CartaoCliente();
        
        System.out.println("Introduza o seu nome: ");
        nome = scan.nextLine();
        
        vazio.setNome(nome);
        
        System.out.println("Por aderir, acabou de ganhar 50 pontos.");
        vazio.setPontos(50);
        
        System.out.println("Introduza o menu que acabou de comer: ");
        menu = scan.nextLine();
        
        vazio.descontar(menu);
        
        System.out.println("Tem neste momento " + vazio.getPontos() + " pontos");
    }
}
