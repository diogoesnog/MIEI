import java.util.Scanner;

/**
 * Main para testar a Classe Complexo.
 * 
 * @author Diogo Nogueira.
 * @version 27.05.2017
 */

public class MainComplexo
{
    public static Scanner scan = new Scanner(System.in);
    public static void main(String[] args){        
        int real;
        int img;
        
        System.out.println("Introduza o seu numero real: ");
        real = scan.nextInt();
        
        System.out.println("Introduza o seu numero imaginario: ");
        img = scan.nextInt();
       
        Complexo vazio = new Complexo();
        Complexo parametrizado = new Complexo(real, img);
        
        Complexo soma = vazio.soma(parametrizado);
        Complexo produto = vazio.produto(parametrizado);
        Complexo reciproco = vazio.reciproco(parametrizado);
        
        System.out.println(soma.toString());
        System.out.println(produto.toString());
        System.out.println(reciproco.toString());
    }
}
