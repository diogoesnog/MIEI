package configurafacil.test;

import configurafacil.business.Componente;
import configurafacil.business.ExcecaoGeral;
import java.io.Serializable;
import java.util.*;

/**
 * 
 * @author Todos
 */
public class Exterior implements Serializable {
    
    private Map<String,Componente> jantes;
    private Map<String,Componente> pneus;
    private Map<String,Componente> tetos;
    private Map<String,Componente> vidros;
    private Map<String,Componente> parachoques;
    
    public Exterior(){
        this.jantes = new HashMap<>();
        this.pneus = new HashMap<>();
        this.tetos = new HashMap<>();
        this.vidros = new HashMap<>();
        this.parachoques = new HashMap<>();
    }
           
    
    public void adicionaJantes(Componente jantes){
        this.jantes.put(jantes.getDesignacao(), jantes);
    }
    
    public void adicionaTetos(Componente tetos){
        this.tetos.put(tetos.getDesignacao(), tetos);
    }
       
    public void adicionaPneus(Componente pneus){
        this.pneus.put(pneus.getDesignacao(), pneus);
    }
    
    public void adicionaVidros(Componente vidros){
        this.vidros.put(vidros.getDesignacao(),vidros);
    }
    
    public void adicionaParaChoque(Componente parachoque){
        this.parachoques.put(parachoque.getDesignacao(),parachoque);
    }
    
    public void adicionaJantes(int quantidade, String designacao){
        Componente jantes1;
        jantes1 = this.jantes.get(designacao);
        jantes1.adicionaQuantidade(quantidade);
        this.jantes.put(jantes1.getDesignacao(), jantes1);
    }
    
    public void adicionaTetos(int quantidade, String designacao){
        Componente tetos1;
        tetos1 = this.tetos.get(designacao);
        tetos1.adicionaQuantidade(quantidade);
        this.tetos.put(tetos1.getDesignacao(), tetos1);
    }
    
    public void adicionaPneus(int quantidade, String designacao){
        Componente pneus1;
        pneus1 = this.pneus.get(designacao);
        pneus1.adicionaQuantidade(quantidade);
        this.pneus.put(pneus1.getDesignacao(),pneus1);
    }
    
    public void adicionaVidros(int quantidade, String designacao){
        Componente vidros1;
        vidros1 = this.vidros.get(designacao);
        vidros1.adicionaQuantidade(quantidade);
        this.vidros.put(vidros1.getDesignacao(),vidros1);
    }
    
    public void adicionaParachoque(int quantidade, String designacao){
        Componente parachoque = this.parachoques.get(designacao);
        parachoque.adicionaQuantidade(quantidade);
        this.parachoques.put(parachoque.getDesignacao(), parachoque);
    }
    
    public void retiraJantes( String designacao) throws ExcecaoGeral{
        Componente jantes1;
        jantes1 = this.jantes.get(designacao);
        jantes1.retiraQuantidade();
    }  

    public void retiraPneus(String designacao) throws ExcecaoGeral{
        Componente pneus1;
        pneus1 = this.pneus.get(designacao);
        pneus1.retiraQuantidade();
    }
    
    public void retiraVidros(String designacao) throws ExcecaoGeral{
        Componente vidros1;
        vidros1 = this.vidros.get(designacao);
        vidros1.retiraQuantidade();
    }
    
    public void retiraTetos(String designacao) throws ExcecaoGeral{
        Componente tetos1;
        tetos1 = this.tetos.get(designacao);
        tetos1.retiraQuantidade();
    }
    
    public void retiraParachoque(String designacao) throws ExcecaoGeral{
        Componente parachoques1;
        parachoques1 = this.parachoques.get(designacao);
        parachoques1.retiraQuantidade();
    }

    public int getStock(String componente) {
        if (componente.contains("Jante"))
            return jantes.get(componente).getStock();
        if (componente.contains("Pneu"))
            return pneus.get(componente).getStock();
        if (componente.contains("Vidro"))
            return vidros.get(componente).getStock();
        if (componente.contains("Pára"))
            return parachoques.get(componente).getStock();
        if (componente.contains("Teto"))
            return tetos.get(componente).getStock();
        return 0;
    }
    
    public boolean checkStock(String componente) {
        if (componente.contains("Jante"))
            return jantes.get(componente).getStock() != 0;
        if (componente.contains("Pneu"))
            return pneus.get(componente).getStock() != 0;
        if (componente.contains("Vidro"))
            return vidros.get(componente).getStock() != 0;
        return false;
    }
    
    
    
}
