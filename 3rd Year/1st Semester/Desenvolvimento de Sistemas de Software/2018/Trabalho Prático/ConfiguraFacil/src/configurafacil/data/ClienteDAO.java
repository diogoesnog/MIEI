/*
* Trabalho realizado para DSS
 */
package configurafacil.data;

import configurafacil.business.Cliente;
import java.sql.Connection;
import java.sql.PreparedStatement;
import java.sql.ResultSet;
import java.sql.SQLException;
import java.sql.Statement;
import java.util.Collection;
import java.util.HashMap;
import java.util.Map;
import java.util.Set;
import java.util.logging.Level;
import java.util.logging.Logger;

/**
 *
 * @author Diogo Araújo
 */
public class ClienteDAO implements Map<Integer, Cliente> {
    
    Connection connection = null;
    
    @Override
    public int size() {
        
        int i = 0;
        try {
            connection = ConnectBD.connect();
            Statement stm = connection.createStatement();
            ResultSet rs = stm.executeQuery("SELECT COUNT(*) FROM cliente");
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
            ResultSet rs = stm.executeQuery("SELECT COUNT(*) FROM cliente");
            if(rs.next()) {
                return 0 == rs.getInt(1);
            }
            
        } catch (Exception e) {throw new NullPointerException(e.getMessage());}
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
            PreparedStatement stm = connection.prepareStatement("SELECT id FROM cliente WHERE id = ?");
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

    
    public HashMap<Integer, Cliente> getClientes() {
        HashMap<Integer,Cliente> clientes = new HashMap<>();
        int id;
        
        try{
            connection = ConnectBD.connect();
            Statement stm = connection.createStatement();
            ResultSet rs = stm.executeQuery("SELECT id FROM cliente");
            while(rs.next()){
                id = rs.getInt("id");
                clientes.put(id,(this.get(id)));
            }
        } catch (ClassNotFoundException | SQLException e) {
        } finally {
            ConnectBD.close(connection);
        }
        return clientes;
    }
    
    @Override
    public Cliente get(Object key) {
        Cliente c = null;
        try {
            connection = ConnectBD.connect();
            PreparedStatement stm = connection.prepareStatement("SELECT * FROM cliente WHERE id=?");
            stm.setInt(1, (Integer)key);
            ResultSet rs = stm.executeQuery();
            
            if (rs.next()) {
                c = new Cliente(rs.getInt(1), rs.getString(2), rs.getString(3));
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
    public Cliente put(Integer key, Cliente value) {
        Cliente c = null;
        try {
            connection = ConnectBD.connect();
            PreparedStatement stm = connection.prepareStatement("INSERT INTO cliente\n" +
                "VALUES (?, ?, ?)\n" +
                "ON DUPLICATE KEY UPDATE nome=VALUES(nome),  morada=VALUES(morada)");
            stm.setInt(1, value.getNIF());
            stm.setString(2, value.getNome());
            stm.setString(3, value.getMorada());
            stm.executeUpdate();
            
            c = value;
        } catch (Exception e) {
            e.printStackTrace();
        } finally {
            ConnectBD.close(connection);
        }
        return c;
        
    }

    @Override
    public Cliente remove(Object key) {
        Cliente c = this.get(key);
        try {
            
            connection= ConnectBD.connect();
            PreparedStatement stm = connection.prepareStatement("DELETE FROM cliente WHERE id = ?");
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

    
    
    
    
    
    
    
    
    @Override
    public boolean containsValue(Object value) {
        throw new UnsupportedOperationException("Not supported yet."); //To change body of generated methods, choose Tools | Templates.
    }
    
    @Override
    public void putAll(Map<? extends Integer, ? extends Cliente> m) {
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
    public Collection<Cliente> values() {
        throw new UnsupportedOperationException("Not supported yet."); //To change body of generated methods, choose Tools | Templates.
    }

    @Override
    public Set<Entry<Integer, Cliente>> entrySet() {
        throw new UnsupportedOperationException("Not supported yet."); //To change body of generated methods, choose Tools | Templates.
    }
    
    
}
