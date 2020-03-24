
/**
 * lê i insere n elementos ordenados por ordem decrescente num array
 */

import java.util.Scanner;
import java.util.Arrays;

public class OrdemDecrescente
{
    private static void insertOrd(int a[], int p, int v){ 
        int i;
        
        for(i=0; i<p && a[i]>v; i++);
        
        if(i != p) System.arraycopy(a, i, a, i+1, p-i);
        
        a[i] = v;
    }
    
    private static int[] lerArrayInt(int n){
        Scanner input = new Scanner(System.in);
        int arr1[];
        arr1 = new int [n];
        
        System.out.println("Digite o array:");
        
        for(int i=0; i<n; i++){
            insertOrd(arr1, i, input.nextInt());
        }
        
        input.close();
        
        return arr1;
    }
    
    public static void main(String[] args){
        Scanner in = new Scanner(System.in);
        int n, arr[];
        
        System.out.println("Qual o tamanho do array?");
        n = in.nextInt();
        
        in.close();
        
        arr = lerArrayInt(n);
        
        System.out.println("O array é:");
        System.out.println(Arrays.toString(arr));
    }
}
