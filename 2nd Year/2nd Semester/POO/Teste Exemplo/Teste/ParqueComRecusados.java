import java.util.*;

public class ParqueComRecusados implements IParque
{
    private Map<String, Set<String>> recusas;
    
    public void sai(String matricula) throws VeiculoNaoExisteException {
        super.sai(matricula);
    }
    
    public boolean noParque(String matricula) {
        super.noParque(matricula);
    }
    
    public boolean equals(Object o) {
        if (o == this) return true;
        if ((o==null)||(this.getClass() != o.getClass())) return false;
        ParqueComRecusados p = (ParqueComRecusados) o;
        return super.equals(p) && this.recusas.equals(p.getRecusas());
    
    }

    public HashMap<String, TreeSet<String>> getRecusas() {
    Set<String> matriculas = recusas.keySet();
    HashMap<String,TreeSet<String>> novo = new HashMap<String,TreeSet<String>>();
    
    for(String s: matriculas) {
        novo.put(s,recusas.get(matricula));
    }
    return novo;
    }
}
