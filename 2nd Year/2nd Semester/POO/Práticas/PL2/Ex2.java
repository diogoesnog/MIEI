import java.util.Scanner;
import java.util.Arrays;

/**
 * Programa que faz a leitura de N valores inteiros paraum array e determina qual o menor valor introduzido, e qual a sua posiçao no array.
 * 
 * @author Diogo Nogueira 
 * @version 27.05.2017
 */

public class Ex2
{
private static int[] lerArrayInt(int n) {
    Scanner scan = new Scanner(System.in);
    int array[] = new int[n];
    
    System.out.println("Introduza os elementos do seu array:");
    
    for(int i = 0; i < n; i++){ array[i] = scan.nextInt();};
    
    return array;
}

private static int minPos(int [] arr) {
    int posicao = 0;
    
    for(int i = 0; i < arr.length; i++){
        if (arr[posicao] > arr[i]) posicao = i;}
    
    return posicao;
} 
   
public static void main (String args[]){
    Scanner scan = new Scanner(System.in);
    
    System.out.println("Qual e o tamanho do seu array?");
    int tamanho;
    int array1[];
    int posmin;
    
    tamanho = scan.nextInt();
    array1 = lerArrayInt(tamanho);
    posmin = minPos(array1);
    
    System.out.println("A posicao menor do seu array e: " +  posmin);
}
}
