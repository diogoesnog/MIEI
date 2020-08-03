package configurafacil.test;

import configurafacil.business.Componente;
import java.io.*;
import java.io.Serializable;

/**
 * 
 * @author Todos
 */
public class Stock implements Serializable{
        
    private Exterior componentesEx;
    private Interior componentesInt;
    private Base componentesBase;

       
    public Stock(){
        this.componentesBase = new Base();
        this.componentesEx = new Exterior();
        this.componentesInt = new Interior();
        stockBase();
        stockExterior();
        stockInterior();
    }
    
    private void stockBase() {
        Componente pinturaAzul = new Componente("Pintura Azul", 3500, 10);
        Componente pinturaBranca = new Componente("Pintura Branca", 2500, 10);
        Componente pinturaPreta = new Componente("Pintura Preta", 2500, 10);
        Componente pinturaVermelha = new Componente("Pintura Vermelha", 3500, 10);
        
        this.componentesBase.adicionaPintura(pinturaAzul);
        this.componentesBase.adicionaPintura(pinturaBranca);
        this.componentesBase.adicionaPintura(pinturaPreta);
        this.componentesBase.adicionaPintura(pinturaVermelha);
        
        Componente Diesel = new Componente("Motor Diesel", 2000, 10);
        Componente Gasolina = new Componente("Motor Gasolina", 1000, 10);
        Componente Eletrico = new Componente("Motor Elétrico", 0, 10);
        Componente Hibrido = new Componente("Motor Híbrido", 1500, 10);
        
        this.componentesBase.adicionaMotorizacao(Eletrico);
        this.componentesBase.adicionaMotorizacao(Diesel);
        this.componentesBase.adicionaMotorizacao(Gasolina);
        this.componentesBase.adicionaMotorizacao(Hibrido);
    }  
    
    private void stockInterior() {
        Componente estofoPele = new Componente("Estofo Pele Preto", 1255, 10);
        Componente estofoTecido = new Componente("Estofo Tecido Preto", 0, 10);
        Componente estofoSport = new Componente("Estofo Sport Cinzento", 1765, 10);
        Componente estofoPeleC = new Componente("Estofo Pele Camel",1855,10 );
        
        this.componentesInt.adicionaEstofos(estofoPele);
        this.componentesInt.adicionaEstofos(estofoTecido);
        this.componentesInt.adicionaEstofos(estofoSport);
        this.componentesInt.adicionaEstofos(estofoPeleC);
        
        Componente frisosPrata = new Componente("Frisos em Prata", 0, 10);
        Componente frisosPretoB = new Componente("Frisos Preto Brilhante", 170, 10);
        Componente frisosCromado = new Componente("Frisos Pérola Cromado",180,10);
        Componente frisosCarbono = new Componente("Frisos Liga de Carbono",200,10);
        
        this.componentesInt.adicionaFrisos(frisosPrata);
        this.componentesInt.adicionaFrisos(frisosPretoB);
        this.componentesInt.adicionaFrisos(frisosCromado);
        this.componentesInt.adicionaFrisos(frisosCarbono);
        
        Componente luzesBrancas = new Componente("Luzes Normais Brancas", 0, 10);
        Componente luzesCorConfort = new Componente("Luzes Vermelhas", 115, 10);
        Componente luzesAzul = new Componente("Luzes Azuis",115,10);
        Componente luzesMultC = new Componente("Luzes Personalizáveis",155,10);
        
        this.componentesInt.adicionaLuzes(luzesBrancas);
        this.componentesInt.adicionaLuzes(luzesCorConfort);
        this.componentesInt.adicionaLuzes(luzesAzul);
        this.componentesInt.adicionaLuzes(luzesMultC);
    }
    
    private void stockExterior() {
        Componente tetoAbrir = new Componente("Teto de Abrir Automático", 1950, 10);
        Componente tetoPanoramico = new Componente("Teto Panorâmico", 1755, 10);
        Componente tetoNormal = new Componente("Teto Normal",0,10);
        Componente tetoAbrirT = new Componente("Teto de Abrir em Tecido",1630,10);
        this.componentesEx.adicionaTetos(tetoAbrir);
        this.componentesEx.adicionaTetos(tetoPanoramico);
        this.componentesEx.adicionaTetos(tetoNormal);
        this.componentesEx.adicionaTetos(tetoAbrirT);
        
        Componente janteLigaLeve = new Componente("Jantes Liga-Leve Ferric",856, 10);
        Componente janteNormal = new Componente("Jantes Normais", 0, 10);
        Componente janteBi = new Componente("Jantes Bicolores em Preto",945,10);
        Componente janteP = new Componente("Jantes em Preto",745,10); 
        
        this.componentesEx.adicionaJantes(janteLigaLeve);
        this.componentesEx.adicionaJantes(janteNormal);
        this.componentesEx.adicionaJantes(janteBi);
        this.componentesEx.adicionaJantes(janteP);
        
        Componente pneuMichelin = new Componente("Pneu Michelin", 1555, 10);
        Componente pneuContinental = new Componente("Pneu Continental", 0, 10);
        
        this.componentesEx.adicionaPneus(pneuMichelin);
        this.componentesEx.adicionaPneus(pneuContinental);
        
        Componente vidroEscurecido = new Componente("Vidro Escurecido", 2069, 10);
        Componente vidroNormal = new Componente("Vidro Normal", 0, 10);
        
        this.componentesEx.adicionaVidros(vidroEscurecido);
        this.componentesEx.adicionaVidros(vidroNormal);
        
        Componente paraCSport = new Componente("Pára-Choque Linha Sport",1869,10);
        Componente paraCConfort = new Componente("Pára-Choque Linha Confort",1559,10);
        Componente paraCNormal = new Componente("Pára-Choque Básico",0,10);
        
        this.componentesEx.adicionaParaChoque(paraCSport);
        this.componentesEx.adicionaParaChoque(paraCConfort);
        this.componentesEx.adicionaParaChoque(paraCNormal);
    }
    
    public void encomendaBase(int quantidade, String componente) {
        if (componente.contains("Pintura"))
            this.componentesBase.adicionaPintura(quantidade, componente);
        if (componente.contains("Motor"))
            this.componentesBase.adicionaMotorizacao(quantidade, componente);
    }
    
    public void encomendaInterior(int quantidade, String componente) {
        if (componente.contains("Estofo"))
            this.componentesInt.adicionaEstofos(quantidade, componente);
        if (componente.contains("Luzes"))
            this.componentesInt.adicionaLuzes(quantidade, componente);
        if (componente.contains("Frisos"))
            this.componentesInt.adicionaFrisos(quantidade, componente);
        
    }    
    
    public void encomendaExterior(int quantidade, String componente) {
        if (componente.contains("Jante"))
            this.componentesEx.adicionaJantes(quantidade, componente);
        if (componente.contains("Pneu"))
            this.componentesEx.adicionaPneus(quantidade, componente);
        if (componente.contains("Vidro"))
            this.componentesEx.adicionaVidros(quantidade, componente);
        if (componente.contains("Pára-Choque"))
            this.componentesEx.adicionaParachoque(quantidade, componente);
        if (componente.contains("Teto"))
            this.componentesEx.adicionaTetos(quantidade, componente);
    }
    
    public int buscaInfoCompBase (String componente) {
        return this.componentesBase.getStock(componente);
    }
    
    public int buscaInfoCompInt (String componente) {
        return this.componentesInt.getStock(componente);
    }

    public int buscaInfoCompExt (String componente) {
        return this.componentesEx.getStock(componente);
    }
        
    /**
     * Método para gravar num ficheiro o estado/informação do programa
     * @param nomeFicheiro o nome do ficheiro onde ficará a informação do programa
     * @throws FileNotFoundException
     * @throws IOException
     */
    public void guardaEstado(String nomeFicheiro) throws FileNotFoundException,IOException {
        FileOutputStream fos = new FileOutputStream(nomeFicheiro);
        ObjectOutputStream oos = new ObjectOutputStream(fos);
        oos.writeObject(this); //guarda-se todo o objecto de uma só vez
        oos.flush();
        oos.close();
    }
    
    /**
     * Método para carregar o estado/informação do programa.
     * @param nomeFicheiro o nome do ficheiro onde ficou a informação do programa
     * @return A instância completa da informação dos sócios todos.
     * @throws FileNotFoundException
     * @throws IOException
     * @throws ClassNotFoundException
     */
    public static Stock carregaEstado(String nomeFicheiro) throws FileNotFoundException, IOException,ClassNotFoundException {                                 
        FileInputStream fis = new FileInputStream(nomeFicheiro);
        ObjectInputStream ois = new ObjectInputStream(fis);
        Stock h = (Stock) ois.readObject();
        ois.close();
        return h;
    } 
}
