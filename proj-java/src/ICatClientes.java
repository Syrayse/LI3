import java.util.Set;

public interface ICatClientes {

    int size();
    ICatClientes insereCliente(ICliente c);
    boolean temCliente(ICliente c);
    Set<ICliente> getClientes();

}
