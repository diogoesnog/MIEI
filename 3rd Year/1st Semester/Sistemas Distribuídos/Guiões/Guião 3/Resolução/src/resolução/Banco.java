package resolução;

import java.util.ArrayList;
import java.util.HashMap;
import java.util.concurrent.locks.ReentrantLock;

/**
 *
 * @author Diogo Nogueira
 */

// Nesta ficha vamos passar a usar lock explícitos. 
// Recorrendo à classe API Java ReentrantLock.

public class Banco {
    
    private final HashMap<Integer, Conta> contas;
    private final ReentrantLock lockBanco;
    
    public Banco() {
        this.contas = new HashMap<>();
        this.lockBanco = new ReentrantLock();
    }
    
    public int criarConta(double saldoInicial){
        
        /** Obviamente que o Lock terá de ser feito aqui para não se criarem duas
        * contas com o mesmo id. 
        */
        
        this.lockBanco.lock();
        
        /** Novo id tem de ser obtido dentro da secção crítica (depois de se ter
         * feito o lock) senão duas Threads podem criar a mesma conta.
         */
        int id = contas.size();

        try {
            Conta novaConta = new Conta(id,saldoInicial);
            this.contas.put(id,novaConta);
        } finally {
            this.lockBanco.unlock();
        }
        
        return id;
    }
    
    public double fecharConta(int idConta){
        
        double saldoConta = 0;
        
        /** Adquirimos aqui o lock do Banco porque evitamos que duas Threads estejam
         * a verificar ao mesmo tempo se aquela conta exista.
         * Assim, garantimos que não há lock caso essa conta não exista e evitamos
         * que duas contas adquiram o lock sem realmente ser necessário.
         */
        /**
         * É ainda necessário fazer o lock por Conta porque caso estejam concorrentemente
         * dois bancos diferentes a fazer operações, o lock por Banco não protege as alterações 
         * caso dois clientes estejam a operar sobre a mesma conta em bancos diferentes.
         */
        this.lockBanco.lock();
        
        if(!contas.containsKey(idConta)) {
            this.lockBanco.unlock();
            System.out.println("A conta que está a tentar encerrar não existe.");
        }
        
        else {
            Conta conta = this.contas.get(idConta);
            conta.lock();
            this.contas.remove(idConta);
            System.out.println("Conta fechada com sucesso.");
            this.lockBanco.unlock();
        }
        
        return saldoConta;
    }
    
    public double consultar(int idConta){
        
        double saldoConta = 0;
        
        this.lockBanco.lock();
        
        if(contas.containsKey(idConta)){
            Conta conta = this.contas.get(idConta);
            conta.lock();
            saldoConta = this.contas.get(idConta).consultar();
            conta.unlock();
            this.lockBanco.unlock();
        }
        
        else{ 
            this.lockBanco.unlock();
            System.out.println("A conta que está a tentar consultar não existe.");
        }
        
        return saldoConta;
    }
    
    public double consultarTotal(int[] contasBancarias){
        
        double saldoTotal = 0;
        
        /** Temos de criar um Array que vá armazenando as contas que irão obter lock
         * para depois podemos libertar essas mesmas contas.
         */
        ArrayList<Integer> contasLocked = new ArrayList(contasBancarias.length);
        
        this.lockBanco.lock();
        try {
            // Estamos a dar o lock de todas as contas que o Cliente quer consultar.
            for(int i = 0; i < contasBancarias.length; i++){
                int idConta = contasBancarias[i];
                
                if(contas.containsKey(idConta)){
                    Conta conta = this.contas.get(idConta);
                    conta.lock();
                    contasLocked.add(idConta);
                }
                
                else{
                    System.out.println("A conta não existe.");
                }
            }
        } finally {
            this.lockBanco.unlock();
        }
        
        for(int id: contasLocked){
            saldoTotal += contas.get(id).consultar();
            Conta conta = this.contas.get(id);
            conta.unlock();
        }
        
        return saldoTotal;
    }
    
    public void levantar(int idConta, double quantia){
        
        this.lockBanco.lock();
        
        if(contas.containsKey(idConta)){
            Conta conta = this.contas.get(idConta);
            conta.lock();
            
            if(conta.consultar() < quantia) {
                System.out.println("Saldo insuficiente para poder levantar quantia solicitada.");
            }
            else {
            conta.levantar(quantia);
            this.lockBanco.unlock();
            conta.unlock(); 
            }
        }
        else{
            this.lockBanco.unlock();
            System.out.println("A conta de onde quer levantar não existe.");
        }
    }

    public void depositar(int idConta, double quantia){
        
        this.lockBanco.lock();
        
        if(contas.containsKey(idConta)){
            Conta conta = this.contas.get(idConta);
            conta.lock();
            conta.depositar(quantia);
            System.out.println("Quantia depositada com sucesso.");
            this.lockBanco.unlock();
            conta.unlock(); 
        }
        else{
            this.lockBanco.unlock();
            System.out.println("A conta onde quer depositar não existe.");
        }
    }
    
    public void transferir(int contaOrigem, int contaDestino, int quantia){
        
        Integer contaNumeroMenor = Math.min(contaOrigem, contaDestino);
        Integer contaNumeroMaior = Math.max(contaOrigem, contaDestino);
        // Fazer o lock de todas as contas envolvidas na operação.

        this.lockBanco.lock();
        
        try {
            if(this.contas.containsKey(contaNumeroMenor)){
                this.contas.get(contaNumeroMenor).lock();
            }
            else{
                this.lockBanco.unlock();
                System.out.println("A conta de origem não existe.");
            }
            
            if(this.contas.containsKey(contaNumeroMaior)){
                this.contas.get(contaNumeroMaior).lock();
            }
            else{
                this.contas.get(contaNumeroMenor).unlock();
                this.lockBanco.unlock();
                System.out.println("A conta de destino não existe.");
            }
        } finally {
            this.lockBanco.unlock();
        }

        if(this.contas.get(contaOrigem).consultar() < quantia){
                this.contas.get(contaNumeroMenor).unlock();
                this.contas.get(contaNumeroMaior).unlock();
                System.out.println("A conta de origem não possui saldo suficiente para transferência.");
        }
        
        this.contas.get(contaOrigem).levantar(quantia);
        this.contas.get(contaDestino).depositar(quantia);
        
        this.contas.get(contaNumeroMenor).unlock();
        this.contas.get(contaNumeroMaior).unlock();   
    }
}