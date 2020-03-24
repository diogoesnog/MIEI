import java.util.Scanner;

/**
 * Main para testar a Classe Complexo.
 * 
 * @author Diogo Nogueira.
 * @version 27.05.2017
 */

public class MainVeiculo
{
     public static void main(String [] args){
        double aut, custoLitro, custoKm;
        boolean reserva;
        
        Veiculo v1 = new Veiculo();
        Veiculo v2 = new Veiculo("00-02-BB",2000,500,4,80,60);
        
        System.out.println("Veículo 1: "+v1.toString());
        System.out.println("Veículo 2: "+v2.toString());
        
        v1.abastecer(16);
        System.out.println("Veículo 1: "+v1.toString());
        
        aut = v1.autonomia();
        System.out.println("Autonomia do veículo 1 : "+aut);
        
        v1.resetKms();
        System.out.println("Veículo 1: "+v1.toString());
        
        v1.registarViagem(100,4);
        System.out.println("Veículo 1: "+v1.toString());
        
        reserva = v1.naReserva();
        System.out.println("O veículo 1 encontra-se na reserva: "+reserva);
        
        custoLitro = v1.totalCombustivel(1.50);
        System.out.println("Custo total combustível do veículo 1: "+custoLitro);
        
        custoKm = v1.custoMedioKm(1.50);
        System.out.println("Custo medio por km do veículo 1: "+custoKm);
    }
}
