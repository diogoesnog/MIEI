package exercício.pkg4.tentativa.pkg1;

/**
 *
 * @author Diogo Nogueira
 */
public class Main {

    public static void main(String[] args) {
    
        // Criamos um Banco com 10 Contas.
        Banco banco = new Banco(10);
        // Depositamos na Conta0 os 1000EUR para ele poder ter dinheiro para os testes.
	banco.depositar(0,1000);
		
	Thread t1 = new Thread(new Cliente1(banco));
	Thread t2 = new Thread(new Cliente2(banco));
		
	t1.start();
		
        // Ao colocarmos este sleep estamos basicamente a obrigar que a Thread1 termine o seu trabalho.
        // Assim sabemos que aquele problema relatado na Classe Conta fica resolvido.
        // No entando não é uma solução.
        
	try {
            Thread.sleep(100);
	} catch (InterruptedException e1) {}

	t2.start();
		
	try {
            t1.join();
            t2.join();
	} catch (InterruptedException e) {}
    }
    
}
