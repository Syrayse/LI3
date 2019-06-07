package GestVendas.Models.Catalogs;

import GestVendas.Models.BaseModels.ICliente;

import java.io.Serializable;
import java.util.HashMap;
import java.util.HashSet;
import java.util.Map;
import java.util.Set;

public class CatClientes implements ICatClientes, Serializable {

    private Map<String, ICliente> clientes;

    public CatClientes() {
        clientes = new HashMap<>();
    }

    public int size() {
        return clientes.size();
    }

    public ICatClientes insereCliente(ICliente c) {
        clientes.put(c.getCodigo(),c);
        return this;
    }

    public boolean existeCliente(ICliente c) {
        return clientes.containsKey(c.getCodigo());
    }

    public boolean existeCliente(String clientCode) {
        return clientes.containsKey(clientCode);
    }

    public Set<String> getCodigoClientes() {
        return new HashSet<>(clientes.keySet());
    }

}
