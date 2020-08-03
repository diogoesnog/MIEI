package configurafacil.test;

import configurafacil.business.Componente;
import configurafacil.business.ExcecaoGeral;
import java.io.Serializable;
import java.util.*;

/**
 * 
 * @author Todos
 */
public class Interior implements Serializable {

    private Map<String,Componente> luzes;
    private Map<String,Componente> frisos;
    private Map<String,Componente> estofos;

    public Interior() {       
        this.luzes = new HashMap<>();
        this.frisos = new HashMap<>();
        this.estofos = new HashMap<>();
    }
        
    
    public void adicionaLuzes(Componente luzes){
        this.luzes.put(luzes.getDesignacao(),luzes);
    }
      
    public void adicionaFrisos(Componente frisos){
        this.frisos.put(frisos.getDesignacao(),frisos);
    }
    
    public void adicionaEstofos(Componente estofos){
        this.estofos.put(estofos.getDesignacao(),estofos);
    }
    
    
    public void adicionaLuzes(int quantidade,String designacao){
        Componente luzes1;
        luzes1 = this.luzes.get(designacao);
        luzes1.adicionaQuantidade(quantidade);
        this.luzes.put(luzes1.getDesignacao(), luzes1);
    }   
    
    public void adicionaFrisos(int quantidade,String designacao){
        Componente frisos1;
        frisos1 = this.frisos.get(designacao);
        frisos1.adicionaQuantidade(quantidade);
        this.frisos.put(frisos1.getDesignacao(), frisos1);
    }
    
    public void adicionaEstofos(int quantidade,String designacao){
        Componente estofos1;
        estofos1 = this.estofos.get(designacao);
        estofos1.adicionaQuantidade(quantidade);
        this.estofos.put(estofos1.getDesignacao(), estofos1);
    }   
    
    public void retiraLuzes(String designacao) throws ExcecaoGeral{
        Componente luzes1;
        luzes1 = this.luzes.get(designacao);
        luzes1.retiraQuantidade();
    }
       
    public void retiraFrisos( String designacao) throws ExcecaoGeral{
        Componente frisos1;
        frisos1 = this.frisos.get(designacao);
        frisos1.retiraQuantidade();
    }
    
    public void retiraEstofos( String designacao) throws ExcecaoGeral{
        Componente estofos1;
        estofos1 = this.estofos.get(designacao);
        estofos1.retiraQuantidade();
    }

    public int getStock(String componente) {
        if (componente.contains("Estofo"))
            return estofos.get(componente).getStock();
        if (componente.contains("Frisos"))
            return frisos.get(componente).getStock();
        if (componente.contains("Luzes"))
            return luzes.get(componente).getStock();
        
        return 0;
    }
    
    public boolean checkStock(String componente) {
        if (componente.contains("Estofo"))
            return estofos.get(componente).getStock() != 0;
        if (componente.contains("Frisos"))
            return frisos.get(componente).getStock() != 0;
        if (componente.contains("Luzes"))
            return luzes.get(componente).getStock() != 0;
        return false;
    }
    
}
