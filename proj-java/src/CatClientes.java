import java.io.Serializable;
import java.util.HashSet;
import java.util.Set;

public class CatClientes implements ICatClientes, Serializable {

    private Set<ICliente> clientes;

    public CatClientes() {
        clientes = new HashSet<>();
    }

    public CatClientes(CatClientes cc) {
        clientes = cc.getClientes();
    }

    public int size() {
        return clientes.size();
    }

    public ICatClientes insereCliente(ICliente c) {
        clientes.add(c);
        return this;
    }

    public boolean temCliente(ICliente c) {
        return clientes.contains(c);
    }

    public Set<ICliente> getClientes() {
        return new HashSet<>(clientes);
    }


}
