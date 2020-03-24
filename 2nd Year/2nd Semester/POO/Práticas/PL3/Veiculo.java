 /**
 * Classe Veiculo.
 * 
 * @author Diogo Nogueira.
 * @version 27.05.2017
 */

public class Veiculo
{
    /** Variáveis de Instância.*/
    
    private String matricula;
    private double kmtotais, kmparciais, consumomedio;
    private int capacidadedeposito, depositoatual;

    /** Construtores. */
    
    /** Construtor vazio da classe Veículo. */
    public Veiculo ()
    {
        this.matricula = "00-AA-00";
        this.kmtotais = 0;
        this.kmparciais = 0;
        this.capacidadedeposito = 0;
        this.depositoatual = 0;
        this.consumomedio = 0;
    }
    
    /** Construtor parametrizado da classe Veículo. */
    public Veiculo (String nmatricula, double nkmtotais, double nkmparciais, int ncapacidadedeposito, int ndepositoatual, double nconsumomedio) {
        this.matricula = nmatricula;
        this.kmtotais = nkmtotais;
        this.kmparciais = nkmparciais;
        this.capacidadedeposito = ncapacidadedeposito;
        this.depositoatual = ndepositoatual;
        this.consumomedio = nconsumomedio;
    }
    
    /** Construtor de cópia da classe Veículo. */
    public Veiculo(Veiculo a) {
        this.matricula = a.getMatricula();
        this.kmtotais = a.getKmTotais();
        this.kmparciais = a.getKmParciais();
        this.capacidadedeposito = a.getCapacidadeDeposito();
        this.depositoatual = a.getDepositoAtual();
        this.consumomedio = a.getConsumoMedio();
    }

    /** Métodos. */
    
    /** Métodos de Instância. -> Gets e Sets. */
    public String getMatricula() {return matricula;}    
    public double getKmTotais() {return kmtotais;}
    public double getKmParciais() {return kmparciais;}
    public int getCapacidadeDeposito() {return capacidadedeposito;}
    public int getDepositoAtual() {return depositoatual;}
    public double getConsumoMedio() {return consumomedio;}
    
    public void setMatricula(String nmatricula) {this.matricula = nmatricula;}
    public void setKmTotais(double nkmtotais) {this.kmtotais = nkmtotais;}
    public void setKmParciais(double nkmparciais) {this.kmparciais = nkmparciais;}
    public void setCapacidadeDeposito(int ncapacidadedeposito) {this.capacidadedeposito = ncapacidadedeposito;}
    public void setDepositoAtual(int ndepositoatual) {this.depositoatual = ndepositoatual;}
    public void setConsumoMedio(double nconsumomedio) {this.consumomedio = nconsumomedio;}
    
    /** Métodos Complementares. */
    public Veiculo clone() {return new Veiculo(this);} // O clone não muda. É sempre isto. Faz uma cópia.
    public String toString() {return "Este Veículo tem a matrícula:" + matricula + "com" + kmtotais + "km totais," + kmparciais + "km parciais," + capacidadedeposito + "de capacidade de depósito (L) e" + depositoatual + "de deposito atual (L).";}
    public boolean equals(Object o) {
        if (this == o) {return true;}
        if (o == null || o.getClass() != this.getClass()) {return false;}
        Veiculo teste = (Veiculo) o;
        return teste.getMatricula() == matricula;
    }   
    
    /** Métodos Pedidos. */
    public void abastecer(int litros){
        if ((capacidadedeposito - depositoatual) > litros) {depositoatual += litros;}
    }
    
    public void resetKms(){
        kmparciais = 0;
        consumomedio = 0;
    }
    
    public double autonomia() {
        double kmpossiveis;
        
        kmpossiveis = (depositoatual * 100) / consumomedio;
        
        return kmpossiveis;
    }
    
    public void registarViagem(int kms, double consumo) {
        kmtotais += kms;
        kmparciais = kms;
        consumomedio = consumo / kms;
        depositoatual -= consumo;
    }
    
    public boolean naReserva() {
        if (depositoatual <= 10) {return true;}
        else {return false;}
    }
    
    public double totalCombustivel (double custoLitro) {
        double gasto;
        
        gasto = depositoatual * custoLitro;
        
        return gasto;
    }
    
    public double custoMedioKm(double custoLitro) {
        double custo;
        
        custo = this.totalCombustivel(custoLitro) / kmparciais;
        
        return custo;
    }
}