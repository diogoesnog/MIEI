import java.io.*;

/**
 *  Classe que que contem a logica das principais funcoes que dao resposta aos topicos do projeto.
 * 
 * @author Diogo Araujo
 * @author Diogo Nogueira
 * @version 2.0
 */
public class UMeR implements Serializable
{
   /** Variaveis de Instancia. */
   private Cliente c;
   private ConjuntoCliente cc;
   private Motorista m;
   private ConjuntoMotorista mm;
   private ConjuntoViatura vv;
   private Taxi t;
   private Moto mt;
   private MonoVolume mv;
   
   /** Construtor vazio que produz uma instancia UMeR. */
   public UMeR(){
       this.c = new Cliente();
       this.cc = new ConjuntoCliente();
       this.m = new Motorista();
       this.mm = new ConjuntoMotorista();
       this.vv = new ConjuntoViatura();
       this.t = new Taxi();
       this.mt = new Moto();
       this.mv = new MonoVolume();
   }
   
   /** Metodo que regista um Cliente no serviço UMeR.
    * @param enome Nome do Cliente.
    * @param eemail Email do Cliente.
    * @param epassword Password do Cliente.
    * @param emorada Morada do Cliente.
    * @param ano O ano de nascimento do Cliente.
    * @param mes O mes de nascimento do Cliente.
    * @param dia O dia de nascimento do Cliente.
    * @see LocalDate
   */
   public void adicionarCliente(String enome, String eemail, String epassword, String emorada, int ano, int mes, int dia, float ex, float ey){
       c.setNome(enome);
       c.setEmail(eemail);
       c.setPassword(epassword);
       c.setMorada(emorada);
       c.setData(ano,mes,dia);
       cc.adiciona(c.clone());
       c.setLocalizacao(ex,ey);
   }
   
   /** Metodo que regista um Motorista no serviço UMeR.
    * @param enome Nome do Motorista.
    * @param eemail Email do Motorista.
    * @param epassword Password do Motorista.
    * @param emorada Morada do Motorista.
    * @param ano O ano de nascimento do Motorista.
    * @param mes O mes de nascimento do Motorista.
    * @param dia O dia de nascimento do Motorista.
    * @see LocalDate
   */
   public void adicionarMotorista(String enome, String eemail, String epassword, String emorada, int ano, int mes, int dia){
       m.setNome(enome);
       m.setEmail(eemail);
       m.setPassword(epassword);
       m.setMorada(emorada);
       m.setData(ano,mes,dia);
       mm.adiciona(m.clone());
   }
   
   /** Metodo que adiciona uma Viatura no serviço UMeR. 
    * @param tipoVeiculo O tipo da Viatura.
    * @param x A cordenada x (em km) da localizacao da Viatura.
    * @param y A coordenada y (em km) da localizacao da Viatura.
    * @param lucro O lucro obtido pela Viatura.
    * @param emotviatura O Motorista associado a Viatura.
    * @see Point2D.Float
   */
   public void adicionarViatura(String tipoVeiculo, float x, float y, double lucro, Motorista emotviatura) {
       if(tipoVeiculo.equalsIgnoreCase("Taxi")) {
           t.setLocViatura(x,y);
           t.setLucro(lucro);
           t.setMotorista(emotviatura.clone());
           vv.adiciona(t.clone());}
       if(tipoVeiculo.equalsIgnoreCase("Moto")) {
           mt.setLocViatura(x,y);
           mt.setLucro(lucro);
           mt.setMotorista(emotviatura.clone());
           vv.adiciona(mt.clone());}
       if(tipoVeiculo.equalsIgnoreCase("Monovolume")) {
           mv.setLocViatura(x,y);
           mv.setLucro(lucro);
           mv.setMotorista(emotviatura.clone());
           vv.adiciona(mv.clone());}       
   }
   
   /** Metodo que verfica se um Cliente foi registado no serviço consoante o seu email.
    * @param email Email do Cliente. 
   */
   public boolean verificarClienteCriado(String email) throws NaoRegistadoException {
       if (cc.existeCliente(email)) return true;
       else throw new NaoRegistadoException();
   }
   
   /** Metodo que verifica se a password introduzia pelo Cliente se encontra correta. 
    * @param email Email do Cliente.
    * @param password Password do Cliente.
   */
   public boolean verificarPassCliente(String email, String password) {
       return cc.passwordCorreta(email, password);
   }
   
   /** Metodo que verfica se um Motorista foi registado no serviço consoante o seu email.
    * @param email Email do Motorista. 
   */
   public boolean verificarMotoristaCriado(String email) throws NaoRegistadoException {
       if (mm.existeMotorista(email)) return true;
       else throw new NaoRegistadoException();
   }
   
   /** Metodo que verifica se a password introduzia pelo Motorista se encontra correta. 
    * @param email Email do Motorista.
    * @param password Password do Motorista.
   */
   public boolean verificarPassMotorista(String email, String password) {
       return mm.passwordCorreta(email, password);
   }
   
   /** Metodo que retorna o Motorista do conjunto dos Motoristas associado ao email passado como parametro.
    * @param Email do Motorista.
   */
   public Motorista recebeMotoristaConj(String email) throws NaoRegistadoException {
       if (mm.existeMotorista(email)) return mm.daMtEspecifico(email);
       else throw new NaoRegistadoException();
   }
   
   /** Metodo que retorna o Cliente do conjunto dos Clientes associado ao email passado como parametro.
    * @param Email do Cliente.
   */
   public Cliente recebeClienteConj(String email) throws NaoRegistadoException {
       if (cc.existeCliente(email)) return cc.daCEspecifico(email);
       else throw new NaoRegistadoException();
   }
   
   /** Metodo que retorna o historico das Viagens associadas a um Motorista passado como parametro.
    * @return String com o historico das Viagens.
   */
   public String historicoMotorista(Motorista mt) {
       return mt.clone().datasViagemString();
   }
   
   /** Metodo que retorna o historico das Viagens associadas a um Cliente passado como parametro.
    * @return String com o historico das Viagens.
   */
   public String historicoCliente(Cliente c) {
       return c.clone().datasViagemString();
   }
   
   /** Metodo que altera a disponibilidade de Motorista.
    * @param email Email do Motorista.
    * @param disponibilidade Disponibilidade atual do Motorista.
   */
   public void alterarDisponibilidade(String email, String disponibilidade) {
       mm.disponibilidade(email, disponibilidade);
       vv.disponibilidade(email, disponibilidade);
   }
   
   /** Metodo que elimina o perfil de um Motorista.
    * @param email Email do Motorista.
   */
   public void eliminarPerfilMotorista(String email) {
       mm.eliminaM(email);
   }
   
   /** Metodo que elimina o perfil de um Cliente.
    * @param email Email do Cliente.
   */
   public void eliminarPerfilCliente(String email) {
       cc.eliminaC(email);
   }
   
   public void viagemEspecifica(Cliente c, String email, float x, float y) throws NaoTemViaturaException {
       try {
           Viatura v = vv.temViaturaMotorista(email); // ele da a viatura e elimina do ArrayList pq depois e introduzido de novo
           
           Viagem nova = new Viagem(c,v,x,y);
           System.out.println(nova.toString());
           
           v.setLocViatura(x,y); //colocar viatura no destino
           v.setLucro(nova.getPreco()); // colocar na viatura o lucro
           Motorista m = mm.daMtEspecifico(email); // receber motorista da viagem
           m.adicionaViagem(nova.clone()); //colocar Viagem no historico do motorista
           m.setKmsFeitos(nova.getDistancia());  // coloca a distancia no motorista
           c.adicionaViagem(nova.clone()); //colocar Viagem no historico do cliente
           cc.adiciona(c.clone()); //colocar esse cliente no conjunto (map);
           mm.adiciona(m.clone()); //colocar esse motorista no conjunto (map);
           vv.adiciona(v.clone()); //colocar essa viatura no conjunto (arraylist);
       }
       catch (NaoTemViaturaException e)
       {throw new NaoTemViaturaException();}
   }
   
   public void colocarClassi(short classificacao, String email) {
       Motorista classificado = (mm.daMtEspecifico(email).clone());
       classificado.setClassificacao(classificacao);
       mm.adiciona(classificado.clone());
   }
   /** Metodo que guarda o estado do programa num ficheiro. 
    * @param nomeFicheiro Ficheiro.
   */
   public void guardaEstado(String nomeFicheiro) throws FileNotFoundException,IOException {
        FileOutputStream fos = new FileOutputStream(nomeFicheiro);
        ObjectOutputStream oos = new ObjectOutputStream(fos);
        oos.writeObject(this); //guarda-se todo o objecto de uma vez.
        oos.flush();
        oos.close();
    }
   
   /** Metodo que carrega o estado de um programa atraves da introducao de um ficheiro.
    * @param nomeFicheiro Ficheiro.
   */
   public static UMeR carregaEstado(String nomeFicheiro) throws FileNotFoundException,
                                            IOException,
                                            ClassNotFoundException {
        FileInputStream fis = new FileInputStream(nomeFicheiro);
        ObjectInputStream ois = new ObjectInputStream(fis);
        UMeR h = (UMeR) ois.readObject();
        ois.close();
        return h;
    }
}