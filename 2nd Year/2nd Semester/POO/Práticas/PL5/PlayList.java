import java.util.List;
import java.util.ArrayList;
import java.util.Iterator;
import java.util.stream.Stream;
import java.util.stream.Collectors;
import java.util.Iterator;

/**
 * Classe PlayList.
 * 
 * @author Diogo Nogueira.
 * @version 27.05.2017
 */

public class PlayList
{
    /** Variáveis de Instância.*/
    
    private String nome;
    private List<Faixa> lista;
    
    /** Construtores. */
    
    /** Construtor vazio da classe PlayList. */
    public PlayList(){
        this.nome = new String();
        this.lista = new ArrayList<Faixa>();
    }
    
    /** Construtor de copia da classe PlayList. */
    public PlayList(PlayList p){
       this.nome = p.getNome();
       this.lista = p.getLista();
    }
    
    /** Métodos. */
    
    /** Métodos de Instância. -> Gets e Sets. */
    public String getNome(){return this.nome;}
    public List<Faixa> getLista(){
        List<Faixa> copia = new ArrayList<Faixa>();
        
        for(Faixa f : lista){copia.add(f.clone());}
        return copia;
            
        //lista.forEach(f -> copia.add(f.clone()));
        //return copia;
        
        //return lista.stream().map(Faixa :: clone).collect(Collectors.toList());
    }
    
    public void setNome(String nome){
        this.nome = nome;
    }
    
    /** Metodos Pedidos. */
  
    /** Metodo que determina o numero total de faixas da PlayList. */
    public int numFaixas(){
        return lista.size();
    }
  
    /** Metodo que adiciona uma faixa. */
    public void addFaixa(Faixa f){
        lista.add(f.clone());
    }
    
    /** Metodo que remove uma faixa. */
    public void removeFaixa(Faixa f){
        lista.remove(f);
    }
    
    /** Metodo que dado um List de Faixa, juntar tais faixas à playlist receptora. */
    
    /** Iterador externo. */
    public void adicionarI(List<Faixa> faixas){
        for(Faixa f : faixas) {lista.add(f.clone());}
    }
    /** Iterador interno. */
    public void adicionarE(List<Faixa> faixas){
        faixas.forEach(f -> lista.add(f.clone()));
        //lista = Stream.concat(lista.stream(), faixas.stream().map(Faixa :: clone)).collect(Collectors.toList());
    }
    
    /** Metodo que determina quantas faixas têm uma classicação superior à Faixa dada como parâmetro. */
    
    /** Iterador externo. */
    public int classificacaoSuperiorI(Faixa f){
        int quantidade = 0;
        int classificacao = f.getClassificacao();
        
        for(Faixa g : lista){if(g.getClassificacao() > classificacao) quantidade++;} 
            
        return quantidade;
    }
    public int classificacaoSuperior(Faixa f){
        int quantidade = 0;
        int classificacao = f.getClassificacao();
        
        Iterator<Faixa> it = lista.iterator();
        Faixa a;
        while(it.hasNext()) {a = it.next();
            if (a.getClassificacao() > classificacao) quantidade++;}
        
            return quantidade;
    }
    
    /** Iterador interno. */
    public long classificacaoSuperiorE(Faixa f){
        int classificacao = f.getClassificacao();
        return lista.stream().filter(faixa -> faixa.getClassificacao()> classificacao).count();
    }
    
    
    /** Metodo que determina se alguma faixa tem duração superior ao valor passada como parâmetro. */
    
    /** Iterador externo. */
    public boolean duracaoSuperiorIV1(double d){
        boolean resultado = false;
        for(Faixa f: lista){if(f.getDuracao() > d) resultado=true;}
        return resultado;        
    }
    public boolean duracaoSuperiorIV2(double d) {
        boolean resultado = false;
        Iterator<Faixa> it = lista.iterator();
        Faixa f;
        
        while(it.hasNext() && !resultado) {
            f = it.next();
            if(f.getDuracao() > d) resultado = true;
        }
        
        return resultado;
    }
    /** Iterador interno. */
    public boolean duracaoSuperiorE(double d){
        return lista.stream().anyMatch(f -> f.getDuracao() > d); //quando encontrar um elemento com duração > d pára 
    }
    
    
    /** Devolver uma cópia listagem de músicas, em que o valor da sua classicação seja alterado para o valor passado como parâmetro. */
    
    /** Iterador externo. */
    public List<Faixa> getCopiaFaixasI(int n){
        List<Faixa> novapl = new ArrayList<Faixa>();
        
        for(Faixa f : lista){
            Faixa faixa = f.clone();
            faixa.setClassificacao(n);
            novapl.add(faixa);
        }
            
        return novapl;
    }
    /** Iterador interno. */
    public List<Faixa> getCopiaFaixasE(int n){
        return lista.stream().map(Faixa :: clone).peek(f -> f.setClassificacao(n)).collect(Collectors.toList());
    }
} 