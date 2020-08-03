package configurafacil.test;

import configurafacil.business.Modelo;
import java.util.*;

/**
 *
 * @author Todos
 */
public class QueueModels {
    private Queue<Modelo> modelos;
    // private Queue<Modelo> modelosEmFalta // modelos cujos os componentes não se encontram em stock
    
    public QueueModels(){
        this.modelos = new LinkedList<>();
    }
    
    public void addModel(Modelo m){
        this.modelos.add(m);
    }
    
    public Modelo retiraModel(){
        return this.modelos.remove();
    }
    
    public String toString(){
        StringBuilder s = new StringBuilder("Modelos em espera\n");
        for(Modelo m : this.modelos){
            s.append(m);
        }
        return s.toString();
    }
}
