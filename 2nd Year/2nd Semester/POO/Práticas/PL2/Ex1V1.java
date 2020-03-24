/**
 * Declarar, inicializar e imprimir os elementos de um array. 
 * 
 * @author Diogo Nogueira 
 * @version 1.0
 */

public class Ex1V1
{
public static void main (String args[]){
    int[] lista = {1,2,3,5,6,8};
    
    System.out.println("Elementos do Array");
    for(int i = 0; i < lista.length; i++){System.out.println("Elemento " + i + "= " + lista[i]);}
}
}