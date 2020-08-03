/*
* Trabalho realizado para DSS
 */
package configurafacil.business;

import configurafacil.data.*;
import javax.swing.DefaultListModel;

/**
 * A nossa principal classe.
 * @author Todos
 */
public class ConfiguraFacil {
    
    private ClienteDAO clienteDAO;
    private ExteriorDAO exteriorDAO;
    private InteriorDAO interiorDAO;
    private ModeloDAO modeloDAO;
    private Modelo modelo;

    /**
     * O Construtor principal da nossa facade.
     */
    public ConfiguraFacil() {
        clienteDAO = new ClienteDAO();
        exteriorDAO = new ExteriorDAO();
        interiorDAO = new InteriorDAO();
        modeloDAO = new ModeloDAO();
        modelo = new Modelo();
    }
    
    // Cenas do ConfigurarModeloGUI

    /**
     * Escolha do tipo do carro.
     * @param tipo O tipo do modelo escolhido.
     */
    public void escolhaTipo (String tipo) {
        this.modelo.setTipo(tipo);
    }
    
    /**
     * Escolha do preço do modelo do carro.
     * @param preco O preço do modelo base.
     */
    public void escolhaPrecoBase (double preco) {
        modelo.setPrecoModelo(preco);
    }
    
    
    // Cenas do ConfigurarBaseGUI

    /**
     * Escolha da pintura do carro.
     * @param escolha A pintura do carro escolhida pelo cliente.
     */
    public void escolhePintura (String escolha) {
        Componente c;
        if(escolha.contains("Azul")){
            c = new Componente("Pintura Azul",535,1);
            this.modelo.setPintura(c);
        }
        if(escolha.contains("Vermelha")){
            c = new Componente("Pintura Vermelha",535,1);
            this.modelo.setPintura(c);
        }
        if(escolha.contains("Preta")){
            c = new Componente("Pintura Preta", 0,1);
            this.modelo.setPintura(c);
        }
        if(escolha.contains("Branca")){
            c = new Componente("Pintura Branca", 0,1);
            this.modelo.setPintura(c);
        } 
    }
    
    /**
     * Escolha da motorização do carro.
     * @param escolha A motorização do carro escolhida pelo cliente.
     * @throws ExcecaoGeral A Exceção usada para colmatar uma incompatibilidade de motorização e modelo/tipo escolhido anteriormente.
     */
    public void escolheMotorizacao (String escolha) throws ExcecaoGeral {
        Componente c;
        
        if(escolha.contains("Diesel")){
            c = new Componente("Motor Diesel", 1200,1);
            this.modelo.setMotorizacao(c);
        }
        if(escolha.contains("Gasolina")){
            c = new Componente("Motor Gasolina", 1500,1);
            this.modelo.setMotorizacao(c);
        }
        if(escolha.contains("Híbrido")){
            c = new Componente("Motor Híbrido", 2000,1);
            this.modelo.setMotorizacao(c);
        }
        if(escolha.contains("Elétrico")){
            c = new Componente("Motor Elétrico", 3000,1);
            this.modelo.setMotorizacao(c);
        }
    }
    
    /**
     * Escolha do pacote do carro.
     * @param escolha O pacote do carro escolhido pelo cliente.
     */
    public void escolhePacote(String escolha) {
        Pacote p;
            if(escolha.contains("Sport")){
                p = new Pacote("Sport");
                this.modelo.setPacote(p);
            }
            if(escolha.contains("Comfort")){
                p = new Pacote("Comfort");
                this.modelo.setPacote(p);
            }
            if(escolha.contains("Deluxe")){
                 p = new Pacote("Deluxe");
                this.modelo.setPacote(p);
            }
    }
    
    // Coisas do ConfigurarInteriorGUI

    /**
     * Escolha dos frisos do carro.
     * @param escolha Os frisos escolhidos pelo cliente.
     */
    public void escolheFrisos (String escolha) {
        Componente c;
        if(escolha.contains("Prata")){
            c = new Componente("Frisos em Prata", 0,1);
            this.modelo.setTipoFrisos(c);
        }
        if(escolha.contains("Preto")){
            c = new Componente("Frisos Preto Brilhante", 170,1);
            this.modelo.setTipoFrisos(c);
        }
        if(escolha.contains("Pérola")){
            c = new Componente("Frisos Pérola Cromado",180,1);
            this.modelo.setTipoFrisos(c);
        }
        if(escolha.contains("Carbono")){
            c = new Componente("Frisos Liga de Carbono",200,1);
            this.modelo.setTipoFrisos(c);
        }
    }
    
    /**
     * Escolha das luzes do carro.
     * @param escolha As luzes escolhidas pelo cliente.
     */
    public void escolheLuzes (String escolha) {
        Componente c;
        if(escolha.contains("Normais")){
            c = new Componente("Luzes Normais Brancas", 0,1);
            this.modelo.setLuzes(c);
        }
        if(escolha.contains("Vermelhas")){
            c = new Componente("Luzes Vermelhas", 115,1);
            this.modelo.setLuzes(c);
        }
        if(escolha.contains("Azul")){
            c = new Componente("Luzes Azul",115,1);
            this.modelo.setLuzes(c);
        }
        if(escolha.contains("Personalizáveis")){
            c = new Componente("Luzes Personalizáveis",155,1);
            this.modelo.setLuzes(c);
        }
    }
    
    /**
     * Escolha dos estofos do carro.
     * @param escolha Os estofos escolhidos pelo cliente.
     */
    public void escolheEstofos (String escolha) {
        Componente c;
        if(escolha.contains("Pele Preto")){
            c = new Componente("Estofo Pele Preto", 1255,1);
            this.modelo.setEstofo(c);
        }
        if(escolha.contains("Tecido")){
            c = new Componente("Estofo Tecido Preto", 0,1);
            this.modelo.setEstofo(c);
        }
        if(escolha.contains("Sport Cinzento")){
            c = new Componente("Estofo Sport Cinzento", 1765,1);
            this.modelo.setEstofo(c);
        }
        if(escolha.contains("Camel")){
            c = new Componente("Estofo Pele Camel",1855,1);
            this.modelo.setEstofo(c);
        }  
    }
    
    // Coisas no ConfigurarExteriorGUI

    /**
     * Escolha dos tetos do carro.
     * @param escolha Os tetos escolhidos pelo cliente.
     */
    public void escolheTetos (String escolha) {
        Componente c;

        if(escolha.contains("Automático")){
            c = new Componente("Teto de Abrir Automático", 1950,1);
            this.modelo.setTeto(c);
        }
        if(escolha.contains("Panorâmico")){
            c = new Componente("Teto Panorâmico", 1755,1);
            this.modelo.setTeto(c);
        }
        if(escolha.contains("Normal")){
            c = new Componente("Teto Normal", 0,1);
            this.modelo.setTeto(c);
        } 
        if(escolha.contains("Tecido")){
            c = new Componente("Teto de Abrir em Tecido",1630,1);
            this.modelo.setTeto(c);
        } 
    }
    
    /**
     * Escolha dos vidros do carro.
     * @param escolha Os vidros escolhidos pelo cliente.
     */
    public void escolheVidros (String escolha) {
        Componente c;

        if(escolha.contains("Escurecido")){
            c = new Componente("Vidro Escurecido", 2069,1);
            this.modelo.setVidros(c);
        }
        if(escolha.contains("Normal")){
            c = new Componente("Vidro Normal", 0,1);
            this.modelo.setVidros(c);
        }
    }
    
    /**
     * Escolha dos para-choques do carro.
     * @param escolha Os parachoques escolhidos pelo cliente.
     */
    public void escolheParaChoques (String escolha) {
        Componente c;
        if(escolha.contains("Básico")){
            c = new Componente("Pára-Choque Básico", 0,1);
            this.modelo.setParaChoque(c);
        }
        if(escolha.contains("Confort")){
            c = new Componente("Pára-Choque Linha Confort", 1559,1);
            this.modelo.setParaChoque(c);
        }
        if(escolha.contains("Sport")){
            c = new Componente("Pára-Choque Linha Sport", 1869,1);
            this.modelo.setParaChoque(c);
        }
    }
    
    /**
     * Escolha dos pneus do carro.
     * @param escolha Os pneus escolhidos pelo cliente.
     */
    public void escolhePneus (String escolha) {
        Componente c;
        if(escolha.contains("Michelin")){
            c = new Componente("Pneu Michelin", 1555,1);
            this.modelo.setPneus(c);
        }
        if(escolha.contains("Continental")){
            c = new Componente("Pneu Continental", 0,1);
            this.modelo.setPneus(c);
        }
    }
    
    /**
     * Escolha das jantes do carro.
     * @param escolha As jantes escolhidas pelo cliente.
     */
    public void escolheJantes (String escolha) {
        Componente c;
        if(escolha.contains("Liga")){
            c = new Componente("Jantes Liga-Leve Ferric",856,1);
            this.modelo.setJantes(c);
        }
        if(escolha.contains("Normais")){
            c = new Componente("Jantes Normais",0,1);
            this.modelo.setJantes(c);
        }
        if(escolha.contains("Bicolores")){
            c = new Componente("Jantes Bicolores em Preto",945,1);
            this.modelo.setJantes(c);
        }
        if(escolha.contains("Preto")){
            c = new Componente("Jantes Bicolores em Preto",945,1);
            this.modelo.setJantes(c);
        }
    }
    
    // Coisas no EfetuarPagamentoGUI

    /**
     * Método para obter o preço total da configuração feita pelo cliente.
     * @return O preço total da configuração.
     */
    public double precoTotal() {
        return modelo.getPrecofinal();
    }

    
    private int idCompra;

    /**
     * O método para efetuar a compra da configuração escolhida até então.
     * @param nome O nome do cliente que efetuou a compra.
     * @param nif O NIF do cliente que efetuou a compra.
     * @param morada A morada do cliente que efetuou a compra.
     */
    public void efetuarCompra (String nome, int nif, String morada) {
        Cliente c = new Cliente(nif, nome, morada);
        clienteDAO.put(nif, c);
        this.modelo.setCliente(c);
        idCompra = modeloDAO.put(null, modelo).getId();
    }
    
    /**
     * Um método auxiliar para fornecer visualmente o ID automático dado a esta configuração paga.
     * @return O ID da Compra.
     */
    public String idCompra() {
        return Integer.toString(idCompra);
    }
    
    @SuppressWarnings("unchecked")
    /**
     * Um método auxiliar para a criar a lista de componentes escolhidos pelo cliente para posterior visualização.
     * @return Um ListModel com os componentes escolhidos.
     */
    public DefaultListModel getListComponentes() {
        DefaultListModel lista = new DefaultListModel();
        lista.addElement("Modelo: " + modelo.getTipo() + " | Preço: " + modelo.getPrecoModelo()+"€");
        lista.addElement(modelo.getMotorizacao());
        lista.addElement(modelo.getPintura());
        lista.addElement("");
        if (modelo.getPacote() != null) lista.addElement("Este modelo contém o pacote "+modelo.getPacoteN());
        lista.addElement("");
        lista.addElement(modelo.getTipoEstofos());
        lista.addElement(modelo.getTipoLuzes());
        lista.addElement(modelo.getTipoFrisos());
        lista.addElement("");
        lista.addElement(modelo.getJantes());
        lista.addElement(modelo.getPneus());
        lista.addElement(modelo.getTipoParaChoque());
        lista.addElement(modelo.getTipoTeto());
        lista.addElement(modelo.getTipoVidros());
        return lista;
    }
}


