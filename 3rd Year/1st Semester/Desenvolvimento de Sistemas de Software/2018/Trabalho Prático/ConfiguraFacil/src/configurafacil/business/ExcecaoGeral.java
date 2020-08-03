package configurafacil.business;

/**
 *
 * @author Todos
 */
public class ExcecaoGeral extends Exception {
    
    private int index;
    
    public ExcecaoGeral(){
        super();
    }
    
    public ExcecaoGeral(String s, int index){
        super(s);
        this.index = index;
    }

    public int getIndex() {
        return index;
    }
}
