public class Run implements Runnable {  
    
    int maximo;

    public Run(int maximo) {
        this.maximo = maximo;
    }
    
    public void run(){

        for (int numero = 1; numero <= maximo; numero++) {
            System.out.println(numero); 
        }
    }

}