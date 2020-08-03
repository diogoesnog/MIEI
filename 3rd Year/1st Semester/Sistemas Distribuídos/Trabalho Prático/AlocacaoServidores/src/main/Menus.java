/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package main;

/**
 *
 * @author 
 */
public class Menus {
     public static void mainMenu(){
        System.out.println("Escolha uma das opções (1 a 3):");
        System.out.println("1.SIGN IN");
        System.out.println("2.LOGIN");
        System.out.println("3.SAIR");
    }
    
    public static void secondMenu(){
        System.out.println("Escolha uma das opções (1 a 3):");
        System.out.println("1.Alugar servidor");
        System.out.println("2.Ir a leilão");
        System.out.println("3.Depositar dinheiro");
        System.out.println("4.Consultar conta");
        System.out.println("5.Logout");
    }
    
    public static void presentigServers(){
        System.out.println("### Tipos de servidores ###");
        System.out.println("Escolha o tipo de servidor que pretende (1 a 3)");
        System.out.println("1.m5.large (1,00€/hora)");
        System.out.println("2.p4.normal (0,90€/hora)");
        System.out.println("3.t3.micro (0,75€/hora)");
        System.out.println("4.SAIR");
    }
    
    /**
     * Método que arrendonda um numero para o numero de casa decimais pretendidos
    */
    public static double roundTo(double valueToRound, int numberOfDecimalPlaces)
    {
        double multipicationFactor = Math.pow(10, numberOfDecimalPlaces);
        double interestedInZeroDPs = valueToRound * multipicationFactor;
        return Math.round(interestedInZeroDPs) / multipicationFactor;
    }

}
