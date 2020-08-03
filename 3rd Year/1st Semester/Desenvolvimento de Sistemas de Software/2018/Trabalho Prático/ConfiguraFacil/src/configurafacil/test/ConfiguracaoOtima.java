package configurafacil.test;

import configurafacil.business.Modelo;

/**
 * 
 * @author Todos
 */
public class ConfiguracaoOtima {
    private double orcamentoI;
    private Modelo modelo;
    
    public ConfiguracaoOtima(){
        this.orcamentoI =0;
        this.modelo = new Modelo();
    }
    
    public ConfiguracaoOtima(double orcamentoI, Modelo modelo){
        this.orcamentoI = orcamentoI;
        this.modelo = modelo;
    }
    
    public void configurando(){
        
    }
    
}
