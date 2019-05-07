package GestVendas.Models.Catalogs;

import java.util.Set;

public interface ICatClientes {

    int size();
    ICatClientes insereCliente(ICliente c);
    boolean existeCliente(ICliente c);
    boolean existeCliente(String clientCode);
    Set<String> getCodigoClientes();
    
}
