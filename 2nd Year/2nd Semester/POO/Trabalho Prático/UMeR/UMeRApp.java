import java.io.*;
import java.util.Scanner;

/**
 * Exemplo de aplicacao com menu em modo texto.
 * 
 * @author Diogo Araujo
 * @author Diogo Nogueira
 * @version 3.0
 */


public class UMeRApp {
    /** Variaveis de Instancia. */

    private UMeR umer;
    private Menu menuPrincipal;
    private Menu menuMotorista;
    private Menu menuCliente;
    private Menu menuViagem;
    
    /** O metodo main que cria a aplicacao e invoca o metodo run. */
    public static void main(String[] args) {
        new UMeRApp().run();
    }
 
    /** Construtor que cria os menus e a parte logica do UMeR. */
    private UMeRApp() {
        // Criar o menu 
        String[] opcoes = {"Criar Cliente",
                           "Criar Motorista",
                           "Criar Viatura",
                           "Login Cliente",
                           "Login Motorista"};
        this.menuPrincipal = new Menu(opcoes);
        this.umer = new UMeR();
        try {
            umer = umer.carregaEstado("estadoUMeR.obj");}
        catch (FileNotFoundException e) {
            System.out.println("Ficheiro nao encontrado!");
            umer = new UMeR();}
        catch (IOException e) {System.out.println("Erro a aceder a ficheiro!");}
        catch (ClassNotFoundException e) {System.out.println("Erro a aceder a ficheiro!");}
    }

    /** Executa o menu principal e invoca o metodo correspondente a opcao seleccionada. */
    private void run() {
        do {
            menuPrincipal.executa();
            switch (menuPrincipal.getOpcao()) {
                case 1: introduzCliente();
                        break;
                case 2: introduzMotorista();
                        break;
                case 3: introduzViatura();
                        break;
                case 4: verLoginCliente();
                        break;
                case 5: verLoginMotorista();
                        break;
            }
        } while (menuPrincipal.getOpcao()!=0); // A opcao usada para sair do menu.
        try {
           umer.guardaEstado("estadoUMeR.obj");
        }
        catch (FileNotFoundException e) {System.out.println("Ficheiro nao encontrado!");}
        catch (IOException e) {System.out.println("Erro a aceder a ficheiro!");}
        System.out.println("Obrigado por utilizar o UMeR.");     
    }
          
    /** Metodo que adiciona um Cliente a aplicacao, pedindo a insercao dos seus respetivos dados. */
    public void introduzCliente() {
        Scanner scan = new Scanner(System.in);
        String nome, email, password, confirmarPassword, morada;
        int ano, mes, dia;
        float x, y;
    
            System.out.println("Introduza o seu nome:");
            nome = scan.nextLine();
            
            System.out.println("Introduza o seu email:");
            email = scan.nextLine();
        do{
             System.out.println("Introduza a sua password:");
             password = scan.nextLine();
                      
             System.out.println("Confirme a sua password:");
             confirmarPassword = scan.nextLine();
             
             if(!password.equals(confirmarPassword)) System.out.println("A sua password foi introduzida incorretamente.");
        }
        while(!password.equals(confirmarPassword));
         
            System.out.println("Introduza a sua morada:");
            morada = scan.nextLine();
            
            System.out.println("Introduza os dados referentes a sua data de nascimento:");
            System.out.println("Ano:");
            ano = scan.nextInt();
            System.out.println("Mes:");
            mes = scan.nextInt();
            System.out.println("Dia:");
            dia = scan.nextInt();
            
            System.out.println("Introduza a coordenada x onde se encontra:");
            x = scan.nextFloat();
            
            System.out.println("Introduza a coordenada y onde se encontra:");
            y = scan.nextFloat();
            
        umer.adicionarCliente(nome, email, password, morada, ano, mes, dia, x, y);
        scan.close();
    }
    
    /** Metodo que adiciona um Motorista a aplicacao, pedindo a insercao dos seus respetivos dados. */
    public void introduzMotorista() {
        Scanner scan = new Scanner(System.in);
        String nome, email, password, confirmarPassword, morada;
        int ano, mes, dia;
        
            System.out.println("Introduza o seu nome:");
            nome = scan.nextLine();
            
            System.out.println("Introduza o seu email:");
            email = scan.nextLine();
            
        do{
             System.out.println("Introduza a sua password:");
             password = scan.nextLine();
                      
             System.out.println("Confirme a sua password:");
             confirmarPassword = scan.nextLine();
            
             if(!password.equals(confirmarPassword)) System.out.println("A sua password foi introduzida incorretamente.");
        }
        while(!password.equals(confirmarPassword));   
        
             System.out.println("Introduza a sua morada:");
             morada = scan.nextLine();
             
            System.out.println("Introduza os dados referentes a sua data de nascimento:");
            System.out.println("Ano:");
            ano = scan.nextInt();
            System.out.println("Mes:");
            mes = scan.nextInt();
            System.out.println("Dia:");
            dia = scan.nextInt();
            
        umer.adicionarMotorista(nome, email, password, morada, ano, mes, dia);
        scan.close();
    }
    
    /** Metodo que adiciona uma Viatura, requisitando a insercao dos dados do veiculo. */
    public void introduzViatura() {
        Scanner scan = new Scanner(System.in);
        String tipoVeiculo, email;
        float x, y;
        double lucro;
        
        do{
             System.out.println("Que tipo de Viatura pretende registar? (Moto, Taxi, Monovolume)");
             tipoVeiculo = scan.nextLine();
                     
             if(!tipoVeiculo.equalsIgnoreCase("Moto") && !tipoVeiculo.equalsIgnoreCase("Taxi") && !tipoVeiculo.equalsIgnoreCase("Monovolume")) System.out.println("A sua Viatura foi introduzida incorretamente.");
        }
        while(!tipoVeiculo.equalsIgnoreCase("Moto") && !tipoVeiculo.equalsIgnoreCase("Taxi") && !tipoVeiculo.equalsIgnoreCase("Monovolume")); 

            System.out.println("Introduza a coordenada x onde o Viatura se encontra:");
            x = scan.nextFloat();
            
            System.out.println("Introduza a coordenada y onde a Viatura se encontra:");
            y = scan.nextFloat();
        
            System.out.println("Introduza o lucro da Viatura:");
            lucro = scan.nextDouble();
            
            scan.nextLine();
            System.out.println("Introduza o email do Motorista:");
            email = scan.nextLine();
            
            try {
                if (umer.verificarMotoristaCriado(email)) {      
                   Motorista motViatura = umer.recebeMotoristaConj(email);
                   umer.adicionarViatura(tipoVeiculo, x, y, lucro, motViatura);
                }
            }
            catch (NaoRegistadoException e) {
                System.out.println("Nao esta registado na UMeR. Por favor registe-se.");
            }
        
        scan.close();        
    }
    
    /** Metodo para verficar se o Cliente esta no UMeR dando um novo menu. */
    private void verLoginCliente() {
        Scanner scan = new Scanner(System.in);
        String email, password;
        System.out.println("Introduza o seu email:");
        email = scan.nextLine();
        try { 
            if (umer.verificarClienteCriado(email)) {
                System.out.println("Introduza a sua password:");
                password = scan.nextLine();
                if(umer.verificarPassCliente(email, password)) {
                    System.out.println("\n Bem-vindo de volta ao UMeR. Boas viagens!\n O seu perfil de Cliente:\n"); 
                    perfilCliente(umer.recebeClienteConj(email)); 
                    System.out.println("\n De volta ao menu principal do UMeR.");}
                else {do { 
                        System.out.println("A sua password foi introduzida incorretamente.");
                        System.out.println("Introduza a sua password:");
                        password = scan.nextLine();}
                      while(!umer.verificarPassCliente(email, password));}
            }
            }
        catch (NaoRegistadoException e)
        {
            System.out.println("Nao esta registado na UMeR. Por favor registe-se.");
        } 
    }
    
    /** Metodo para verficar se o Motorista esta no UMeR dando um novo menu. */
    private void verLoginMotorista() {
        Scanner scan = new Scanner(System.in);
        String email, password;
        System.out.println("Introduza o seu email:");
        email = scan.nextLine();
        try { 
            if (umer.verificarMotoristaCriado(email)) {
                System.out.println("Introduza a sua password:");
                password = scan.nextLine();
                if(umer.verificarPassMotorista(email, password)) {
                    System.out.println("\n Bem-vindo de volta ao UMeR. Boas viagens!\n O seu perfil de Motorista:"); 
                    perfilMotorista(umer.recebeMotoristaConj(email)); 
                    System.out.println("\n De volta ao menu principal do UMeR.\n");}
                else {do { 
                        System.out.println("A sua password foi introduzida incorretamente.");
                        System.out.println("Introduza a sua password:");
                        password = scan.nextLine();}
                      while(!umer.verificarPassMotorista(email, password));}
            }
            }
        catch (NaoRegistadoException e)
        {
            System.out.println("\nNao esta registado na UMeR. Por favor registe-se.\n");
        } 
    }
        
    /** Metodo que cria o perfil/menu do Motorista e as suas opcoes variadas. */
    private void perfilMotorista(Motorista mt) {
        String[] opcoes = {"Historico Viagens",
                         "Alterar Disponibilidade",
                         "Eliminar o perfil"};
        this.menuMotorista = new Menu(opcoes);
        do {
            menuMotorista.executa();
            switch (menuMotorista.getOpcao()) {
                case 1: verhistoricoMotorista(mt);
                        break;
                case 2: alteraDisponibilidade(mt.getEmail());
                        break;
                case 3: eliminaPerfilMotorista(mt.getEmail());
                        break;
            }
        }
        while (menuMotorista.getOpcao()!=0);
    }
    
    /** Metodo que imprime o historico das Viagens de um Motorista.
     * @param mt Motorista.
    */
    public void verhistoricoMotorista(Motorista mt) {
        System.out.println(umer.historicoMotorista(mt.clone()));
    }
    
    /** Metodo que permite a alteracao da diponiblidade de um Motorista.
     * @param email Email do Motorista.
    */
    public void alteraDisponibilidade(String email) {
        Scanner scan = new Scanner(System.in);
        String disponibilidade;
        
        System.out.println("Mude a sua disponiblidade:");
        System.out.println("Esta disponivel neste momento? (S/N)");
        disponibilidade = scan.nextLine();
        umer.alterarDisponibilidade(email, disponibilidade);
    }
   
    /** Metodo que permite a eliminacao do perfil de um Motorista.
    * @param email Email do Motorista.
    */
    public void eliminaPerfilMotorista(String email) {
        umer.eliminarPerfilMotorista(email);
    }
    
    /** Metodo que cria o perfil/menu do Cliente e as suas opcoes variadas. */
    private void perfilCliente(Cliente c) {
        String[] opcoes = {"Requisitar Viagem",
                           "Historico Viagens",
                           "Eliminar o perfil"};
        this.menuCliente = new Menu(opcoes);
        do {
            menuCliente.executa();
            switch (menuCliente.getOpcao()) {
                case 1: System.out.println("\nQue tipo de Viagem deseja fazer com o UMeR?\n");
                        novaViagem(c);
                        break;
                case 2: verhistoricoCliente(c);
                        break;
                case 3: eliminaPerfilCliente(c.getEmail());
                        break;
            }
        }
        while (menuCliente.getOpcao()!=0);
    }
    
    /** Metodo que imprime o historico das Viagens de um Cliente.
     * @param c Cliente.
    */
    public void verhistoricoCliente(Cliente c) {
        System.out.println(umer.historicoCliente(c.clone()));
    }
    
    /** Metodo que permite a eliminacao do perfil de um Cliente.
    * @param email Email do Cliente.
    */
    public void eliminaPerfilCliente(String email) {
        umer.eliminarPerfilCliente(email);
    }
        
    /** Metodo que cria o perfil/menu de uma nova Viagem e as suas opcoes variadas. */
    public void novaViagem(Cliente c) {
        String[] opcoes = {"Selecionar o Veiculo mais proximo",
                           "Selecionar um Veiculo especifico do serviço UMeR"};
        this.menuViagem = new Menu(opcoes);
        do{
            menuViagem.executa();
            switch (menuViagem.getOpcao()) {
                case 1: viagemVeiculoEspecifico(c);;
                        break;
                case 2: viagemVeiculoEspecifico(c);
                        break;
            }
        }
        while (menuViagem.getOpcao()!=0);
    }
    
    //public void viagemVeiculoProximo(Cliente c) {}
        /*Scanner scan = new Scanner(System.in);
        double x,y;
        Veiculo v;
        
        System.out.println("Digite a coordenada x onde se encontra:");
        x = input.nextDouble();
       
        System.out.println("Digite a coordenada y onde se encontra:");
        y = input.nextDouble();
     */
    
    /** Metodo que solicita uma Viatura em especifico de acordo com o email do Motorista associado a mesma.  */
    public void viagemVeiculoEspecifico(Cliente c) {
        String email;
        float x,y;
        short classificacao;
        Scanner scan = new Scanner(System.in);
        
        System.out.println("Digite a coordenada x para onde quer ir: ");
        x = scan.nextFloat();
        
        System.out.println("Digite a coordenada y para onde quer ir: ");
        y = scan.nextFloat();
        scan.nextLine();
        
        try {
            System.out.println("Digite o email do Motorista da Viatura pretendida: ");
            email = scan.nextLine();
            if(!umer.verificarMotoristaCriado(email)) {}
            else {
                System.out.println("\n");
                umer.viagemEspecifica(c.clone(),email, x, y);
        
                System.out.println("\n Viagem concluida \n Qual a classificacao do Motorista? (Coloque de 0 a 100) \n");
                classificacao = scan.nextShort();
                umer.colocarClassi(classificacao, email);}}
        catch (NaoRegistadoException e) {
            System.out.println("Esse email nao esta associado a um motorista");
        }
        catch (NaoTemViaturaException e) {
            System.out.println("Essa Viatura nao existe ou nao se encontra disponivel");
        }
    }
}