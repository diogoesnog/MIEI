package cesium;


import java.util.*;

public class Cesium extends Observable {

    // Variáveis de Instância
    private Map<String,Aluno> socios;

   
     // Construtores
    
     // Construtor Vazio
    public Cesium() {
        this.socios = new Hashtable<String,Aluno>();
    }

    
    // Adicionar aluno
    public void addAluno(Aluno a) {
        Aluno copia = (Aluno)a.clone();
        String num= a.getNumero();
        boolean update = this.socios.containsKey(num);
        this.socios.put(num,copia);
        if (!update) {
            this.setChanged();
            this.notifyObservers();
        }
    }

    // Consultar aluno
    public Aluno getAluno(String num) throws CesiumException {
        
        try {
            Aluno a = this.socios.get(num);
            return (Aluno)a.clone();
        } 
        catch (NullPointerException e) {
            StringBuilder sb = new StringBuilder("Aluno ");
            sb.append(num);
            sb.append(" inexistente!");
            throw new CesiumException(sb.toString());
        }
    }

    // Remover aluno
    public void delAluno(String num) throws CesiumException {
        if (!this.socios.containsKey(num)) {
            StringBuilder sb = new StringBuilder("Aluno ");
            sb.append(num);
            sb.append(" inexistente.");
            throw new CesiumException(sb.toString());
        }        
        this.socios.remove(num);
        this.setChanged();
        this.notifyObservers();
    }

}
