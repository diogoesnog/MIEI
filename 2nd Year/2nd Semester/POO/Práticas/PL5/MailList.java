import java.util.List;
import java.util.ArrayList;
import java.util.GregorianCalendar;

/**
 * Classe MailList.
 * 
 * @author Diogo Nogueira.
 * @version 27.05.2017
 */

public class MailList
{
        /** Variáveis de Instância.*/
        
        private String nomeconta;
        private List<Mail> conta;
        
        /** Construtores. */
        
        /** Construtor vazio da classe MailList. */
        public MailList() {
            this.nomeconta = new String();
            this.conta = new ArrayList<Mail>();
        }
        
        /**Construtor de copia da classe MailList. */
        public MailList(MailList o){
            this.nomeconta = o.getNomeConta();
            this.conta = o.getConta();
        }
        
        /** Metodos. */
        
        /** Metodos de Instancia. -> Gets e Sets. */
        public String getNomeConta() {return nomeconta;}
        public List<Mail> getConta() {
            List<Mail> novo = new ArrayList<Mail>();
            
            for(Mail f: conta){novo.add(f.clone());}
            
            return novo;
        }
        
        /** Metodos Pedidos. */
        
        /** Metodo que determina o total de mails guardados. */
        public int totalEmails() {
            int total = 0;
            for(Mail f: conta){total++;}
            return total;
        }
        
        /** Metodo que guarda um novo mail recebido. */
        public void adicionarEmail(Mail m) {
            conta.add(m.clone());            
        }
        
        /** Metodo que determina quantos mails têm por origem um dado endereço. */
        
        /** Iterador externo. */
        public int fromE(String endereco) {
            int quantidade = 0;
            for(Mail o: conta){if(o.getRemetente().equals(endereco)) quantidade++;}
            return quantidade;
        }
        /** Iterador interno. */
        public int fromI(String endereco) {
            return (int) conta.stream().filter(mail -> mail.getRemetente().equals(endereco)).count();
        }
        
        /** Metodo que elimina todos os e-mails recebidos antes de uma data que é dada como parâmetro. */
        
        /** Iterador externo. */
        public void eliminarRecebidos(GregorianCalendar data){
            for(Mail o: conta){if (o.getRecepcao().equals(data)) conta.remove(o);}
        }
}