package exercício.pkg2;

import java.util.HashMap;

public class Warehouse {

    private final HashMap<String, Item> stockArmazem;

    public Warehouse(){
	this.stockArmazem = new HashMap<>();
    }

    // Adicionar novo item ao stock do Armazém.
    public void supply(String nomeItem, int quantidade){

        synchronized(this){
            if(this.stockArmazem.containsKey(nomeItem)){
                System.out.println("Armazém já contém o Item que pretende consumir. Vamos adicionar quantidade ao mesmo.");
                this.stockArmazem.get(nomeItem).aumentaCapacidade(quantidade);
            } else {
                this.stockArmazem.put(nomeItem, new Item());
            }
	}
    }

    // Consome uma unidade a todos os itens passado no Array.
    public void consume(String[] itemsConsumir){	

        for (String item : itemsConsumir) {
            if (this.stockArmazem.containsKey(item)) {
                this.stockArmazem.get(item).consomeQuantidade();
            } else {
            }
        }
    }
}
