/*
* Trabalho realizado para DSS
 */
package configurafacil.data;

import configurafacil.business.Componente;
import java.sql.Connection;
import java.sql.PreparedStatement;
import java.sql.ResultSet;
import java.sql.SQLException;
import java.sql.Statement;
import java.util.*;
import java.util.logging.Level;
import java.util.logging.Logger;

/**
 *
 * @author Diogo Araújo
 */
public class ExteriorDAO implements Map<Integer, Componente>{
    
    Connection connection;
    
    
    @Override
    public int size() {
        int i = 0;
        try {
            connection = ConnectBD.connect();
            Statement stm = connection.createStatement();
            ResultSet rs = stm.executeQuery("SELECT COUNT(*) FROM exterior");
            if(rs.next()) {
                i = rs.getInt(1);
            }
        }
        catch (ClassNotFoundException | SQLException e) {throw new NullPointerException(e.getMessage());}
        finally {
            ConnectBD.close(connection);
        }
        return i;
    }

    @Override
    public boolean isEmpty() {
        try {
            connection = ConnectBD.connect();
            Statement stm = connection.createStatement();
            ResultSet rs = stm.executeQuery("SELECT COUNT(*) FROM interior");
            if(rs.next()) {
                return 0 == rs.getInt(1);
            }
            
        } catch (ClassNotFoundException | SQLException e) {throw new NullPointerException(e.getMessage());}
        finally {
            ConnectBD.close(connection);
        }
        return false;
    }

    @Override
    public boolean containsKey(Object key) {
        boolean contains = false;
        
        try {
            connection = ConnectBD.connect();
            PreparedStatement stm = connection.prepareStatement("SELECT id FROM exterior WHERE id = ?");
            stm.setInt(1, (Integer)key);
            ResultSet rs = stm.executeQuery();
            
            if(rs.next()){
                if(rs.getInt("id") == (int) key){
                    contains = true;
                }
            }
        }
        catch (Exception e) {throw new NullPointerException(e.getMessage());}
        finally {
            ConnectBD.close(connection);
        }
        return contains;
    }

    
    public HashMap<Integer, Componente> getExterior() {
        HashMap<Integer,Componente> exterior = new HashMap<Integer,Componente>();
        int id;
        
        try{
            connection = ConnectBD.connect();
            Statement stm = connection.createStatement();
            ResultSet rs = stm.executeQuery("SELECT id FROM exterior");
            while(rs.next()){
                id = rs.getInt("id");
                exterior.put(id,(this.get(id)));
            }
        } catch (ClassNotFoundException | SQLException e) {
        } finally {
            ConnectBD.close(connection);
        }
        return exterior;
    }
    @Override
    public Componente get(Object key) {
        Componente c = null;
        try {
            connection = ConnectBD.connect();
            PreparedStatement stm = connection.prepareStatement("SELECT * FROM exterior WHERE id=?");
            stm.setInt(1, (Integer)key);
            ResultSet rs = stm.executeQuery();
            
            if (rs.next()) {
                c = new Componente(rs.getInt(1), rs.getString(2), rs.getDouble(3), rs.getInt(4));
            }
        } catch (SQLException | ClassNotFoundException ex) {
            Logger.getLogger(InteriorDAO.class.getName()).log(Level.SEVERE, null, ex);
        }
        finally {
            ConnectBD.close(connection);
        }
        return c;
    }


    @Override
    public Componente remove(Object key) {
        Componente c = this.get(key);
        try {
            
            connection= ConnectBD.connect();
            PreparedStatement stm = connection.prepareStatement("DELETE FROM exterior WHERE id = ?");
            stm.setInt(1, (Integer)key);
            stm.executeUpdate();
        }
        catch (SQLException | ClassNotFoundException ex) {
            Logger.getLogger(ClienteDAO.class.getName()).log(Level.SEVERE, null, ex);
        }
        finally {
            ConnectBD.close(connection);
        }
        return c;
    }

    
    
    
    
    
    
    
    // Não usadas
    @Override
    public Componente put(Integer key, Componente value) {
        throw new UnsupportedOperationException("Not supported yet."); //To change body of generated methods, choose Tools | Templates.
    }
    
    @Override
    public boolean containsValue(Object value) {
        throw new UnsupportedOperationException("Not supported yet."); //To change body of generated methods, choose Tools | Templates.
    }
    
    @Override
    public void putAll(Map<? extends Integer, ? extends Componente> m) {
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
    public Collection<Componente> values() {
        throw new UnsupportedOperationException("Not supported yet."); //To change body of generated methods, choose Tools | Templates.
    }

    @Override
    public Set<Entry<Integer, Componente>> entrySet() {
        throw new UnsupportedOperationException("Not supported yet."); //To change body of generated methods, choose Tools | Templates.
    }
    
}
