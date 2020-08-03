/*
* Trabalho realizado para DSS
 */
package configurafacil.data;

import configurafacil.business.Modelo;
import java.sql.Connection;
import java.sql.PreparedStatement;
import java.sql.ResultSet;
import java.sql.SQLException;
import java.sql.Statement;
import java.util.*;

/**
 *
 * @author Diogo Araújo
 */
public class ModeloDAO implements Map<Integer, Modelo> {
    
    Connection connection;

    @Override
    public int size() {
        throw new UnsupportedOperationException("Not supported yet."); //To change body of generated methods, choose Tools | Templates.
    }

    @Override
    public boolean isEmpty() {
        throw new UnsupportedOperationException("Not supported yet."); //To change body of generated methods, choose Tools | Templates.
    }

    @Override
    public boolean containsKey(Object key) {
        boolean contains = false;
        
        try {
            connection = ConnectBD.connect();
            PreparedStatement stm = connection.prepareStatement("SELECT id FROM UC WHERE id = ?");
            stm.setInt(1, (Integer)key);
            ResultSet rs = stm.executeQuery();
            
            if(rs.next()){
                if(rs.getInt("id") == (int) key){
                    contains = true;
                }
            }
        }
        catch (ClassNotFoundException | SQLException e) {throw new NullPointerException(e.getMessage());}
        finally {
            ConnectBD.close(connection);
        }
        return contains;
    }

    @Override
    public boolean containsValue(Object value) {
        throw new UnsupportedOperationException("Not supported yet."); //To change body of generated methods, choose Tools | Templates.
    }

    @Override
    public Modelo get(Object key) {
        throw new UnsupportedOperationException("Not supported yet."); //To change body of generated methods, choose Tools | Templates.
    }

    @Override
    public Modelo put(Integer key, Modelo value) {
        Modelo m = null;
        try {
            connection = ConnectBD.connect();
            PreparedStatement stm = connection.prepareStatement("INSERT INTO modelo (Cliente_nif, tipo, precoModelo, precofinal, pacote, pintura, motorizacao, jantes, pneus, vidros, parachoques, tetos, luzes, frisos, estofos)\n" +
"  VALUE (?,?,?,?,?,?,?,?,?,?,?,?,?,?,?)", Statement.RETURN_GENERATED_KEYS);
            stm.setInt(1, value.getCliente().getNIF());
            stm.setString(2, value.getTipo());
            stm.setDouble(3, value.getPrecoModelo());
            stm.setDouble(4, value.getPrecofinal());
            stm.setString(5, value.getPacoteN());
            stm.setInt(6, getIDBase(value.getPintura().getDesignacao()));
            stm.setInt(7, getIDBase(value.getMotorizacao().getDesignacao()));
            stm.setInt(8, getIDExterior(value.getJantes().getDesignacao()));
            stm.setInt(9, getIDExterior(value.getPneus().getDesignacao()));
            stm.setInt(10, getIDExterior(value.getTipoVidros().getDesignacao()));
            stm.setInt(11, getIDExterior(value.getTipoParaChoque().getDesignacao()));
            stm.setInt(12, getIDExterior(value.getTipoTeto().getDesignacao()));
            stm.setInt(13, getIDInterior(value.getTipoLuzes().getDesignacao()));
            stm.setInt(14, getIDInterior(value.getTipoFrisos().getDesignacao()));
            stm.setInt(15, getIDInterior(value.getTipoEstofos().getDesignacao()));
            
            stm.executeUpdate();
            
            ResultSet rs = stm.getGeneratedKeys();
            if(rs.next()) {
                int newId = rs.getInt(1);
                value.setId(newId);
            }
            
            
            m = value;
        } catch (ClassNotFoundException | SQLException e) {
        } finally {
            ConnectBD.close(connection);
        }
        return m;
    }

    
//    private int getID(String designacao) {
//        int id = 0;
//        
//        id = getIDBase(designacao);
//        id = getIDExterior(designacao);
//        id = getIDInterior(designacao);
//        
//        return id;
//    }
    
    private int getIDInterior(String designacao) {
         try {
            connection = ConnectBD.connect();
            PreparedStatement stm = connection.prepareStatement("SELECT idComponente FROM interior WHERE designacao = ?");
            stm.setString(1, designacao);
            ResultSet rs = stm.executeQuery();
            if(rs.next()) {
                return rs.getInt(1);
            }
        } catch (ClassNotFoundException | SQLException e) {
        } finally {
            ConnectBD.close(connection);
        }
        return 0;
    }
    
    private int getIDExterior(String designacao) {
         try {
            connection = ConnectBD.connect();
            PreparedStatement stm = connection.prepareStatement("SELECT idComponente FROM exterior WHERE designacao = ?");
            stm.setString(1, designacao);
            ResultSet rs = stm.executeQuery();
            if(rs.next()) {
                return rs.getInt(1);
            }
        } catch (ClassNotFoundException | SQLException e) {
        } finally {
            ConnectBD.close(connection);
        }
        return 0;
    }
    
    private int getIDBase(String designacao) {
         try {
            connection = ConnectBD.connect();
            PreparedStatement stm = connection.prepareStatement("SELECT idComponente FROM base WHERE designacao = ?");    
            stm.setString(1, designacao);
            ResultSet rs = stm.executeQuery();
            if(rs.next()) {
                return rs.getInt(1);
            }
        } catch (ClassNotFoundException | SQLException e) {
        } finally {
            ConnectBD.close(connection);
        }
        return 0;
    }
    
    
    
    
    
    
    
    
    
    
    
    @Override
    public Modelo remove(Object key) {
        throw new UnsupportedOperationException("Not supported yet."); //To change body of generated methods, choose Tools | Templates.
    }

    @Override
    public void putAll(Map<? extends Integer, ? extends Modelo> m) {
        throw new UnsupportedOperationException("Not supported yet."); //To change body of generated methods, choose Tools | Templates.
    }

    @Override
    public void clear() {
        throw new UnsupportedOperationException("Not supported yet."); //To change body of generated methods, choose Tools | Templates.
    }

    @Override
    public Set<Integer> keySet() {
        throw new UnsupportedOperationException("Not supported yet."); //To change body of generated methods, choose Tools | Templates.
    }

    @Override
    public Collection<Modelo> values() {
        throw new UnsupportedOperationException("Not supported yet."); //To change body of generated methods, choose Tools | Templates.
    }

    @Override
    public Set<Entry<Integer, Modelo>> entrySet() {
        throw new UnsupportedOperationException("Not supported yet."); //To change body of generated methods, choose Tools | Templates.
    }
    
}
