package configurafacil.test;

import configurafacil.business.Componente;
import configurafacil.business.ExcecaoGeral;
import java.io.Serializable;
import java.util.*;

/**
 *
 * @author Todos
 */
public class Base implements Serializable {
    
    private Map<String,Componente> motorizacoes;
    private Map<String,Componente> pinturas;
    
    public Base(){
        this.pinturas = new HashMap<>();
        this.motorizacoes = new HashMap<>();
    }
    
    public void adicionaPintura(Componente pintura){
        this.pinturas.put(pintura.getDesignacao(), pintura);
    }
    
    public void adicionaMotorizacao(Componente motorizacao){
        this.motorizacoes.put(motorizacao.getDesignacao(),motorizacao);
    }
    
    public void adicionaPintura(int quantidade,String designacao){
        Componente pintura = this.pinturas.get(designacao);
        pintura.adicionaQuantidade(quantidade);
        this.pinturas.put(pintura.getDesignacao(), pintura);
    }
    
    public void adicionaMotorizacao(int quantidade,String designacao){
        Componente motorizacao = this.motorizacoes.get(designacao);
        motorizacao.adicionaQuantidade(quantidade);
        this.motorizacoes.put(motorizacao.getDesignacao(), motorizacao);
    }
    
    public void retiraPintura(String designacao) throws ExcecaoGeral {
        Componente pintura = this.pinturas.get(designacao);
        pintura.retiraQuantidade();
    }
    
    public void retiraMotorizacao(String designacao) throws ExcecaoGeral{
        Componente motorizacao = this.motorizacoes.get(designacao);
        motorizacao.retiraQuantidade();
    }
    
    public int getStock(String componente) {
        if (componente.contains("Pintura"))
            return pinturas.get(componente).getStock();
        if (componente.contains("Motor"))
            return motorizacoes.get(componente).getStock();
        return 0;
    }
    
    public boolean noStock(String componente) {
        if (componente.contains("Pintura"))
            return pinturas.get(componente).getStock() == 0;
        if (componente.contains("Motor"))
            return motorizacoes.get(componente).getStock() == 0;
        return false;
    }
}
