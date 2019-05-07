package GestVendas.Models.Catalogs;

import java.io.Serializable;
import java.util.Map;

public class CatClientes implements ICatClientes, Serializable {

    private Map<String,ICliente> clientes;

    public CatClientes() {
        clientes = new HashMap<>();
    }

    public int size() {
        return clientes.size();
    }

    public ICatClientes insereCliente(ICliente c) {
        clientes.add(c);
        return this;
    }

    public boolean existeCliente(ICliente c) {
        return clientes.containsKey(c.getCodigo());
    }

    public boolean existeCliente(String clientCode) {
        return clientes.containsKey(clientCode);
    }

    public Set<String> getClientes() {
        return new HashSet<String>(clientes.keySet());
    }

}
