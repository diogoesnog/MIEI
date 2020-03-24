import java.util.Scanner;

/**
 * Main para testar a Classe Pixel.
 * 
 * @author Diogo Nogueira.
 * @version 27.05.2017
 */

public class MainPixel
{
    public static Scanner scan = new Scanner(System.in);
    public static void main(String[] args){        
        double x;
        double y;
        int cor;
        
        System.out.println("Introduza a sua coordenada x: ");
        x = scan.nextDouble();
        
        System.out.println("Introduza a sua coordenada y: ");
        y = scan.nextDouble();
        
        System.out.println("Introduza a sua cor (de 0 a 15): ");
        cor = scan.nextInt();
        
        Pixel vazio = new Pixel();
        Pixel parametrizado = new Pixel(x, y, cor);
        
        vazio.desloca(2,4);
        System.out.println(vazio.toString());
        
        vazio.mudarCor(14);
        System.out.println(vazio.toString());
        System.out.println(vazio.nomeCor());
    }
}