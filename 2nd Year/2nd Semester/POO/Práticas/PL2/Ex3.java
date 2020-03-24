import java.util.Scanner;
import java.util.Arrays;

/**
 * Programa que faz a leitura de N valores inteiros para um array e determina qual o menor valor introduzido, e qual a sua posiçao no array.
 * 
 * @author Diogo Nogueira 
 * @version 27.05.17
 */

public class Ex3
{
    
private static void inserirOrd(int array[], int p, int v){
    
}

private static int[] lerArrayInt(int n) {
    Scanner scan = new Scanner(System.in);
    int array[] = new int[n];
    
    System.out.println("Introduza o seu array:");
    
    for(int i = 0; i < n; i++){inserirOrd(array, i, input.nextInt())};
    
    return array;
}
   
public static void main (String args[]){
    Scanner scan = new Scanner(System.in);
    
    int tamanho;
    int array1[];
    
    System.out.println("Qual e o tamanho do seu array?");
    tamanho = scan.nextInt();
    array1 = lerArrayInt(tamanho);
    
    
    System.out.println("O array e:");
    System.ou.println(Arrays.toString(array1);
}
}