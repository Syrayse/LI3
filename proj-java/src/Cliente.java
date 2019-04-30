import java.io.Serializable;

public class Cliente implements ICliente, Comparable<Cliente>, Serializable {

    private String codigo;

    public Cliente() {
        codigo = "";
    }

    public Cliente(String codigo) {
        this.codigo = codigo;
    }

    public String getCodigo() {
        return codigo;
    }

    public int compareTo(Cliente c) {
        return this.codigo.compareTo(c.getCodigo());
    }

    public boolean equals(Object o) {
        if (this == o) return true;
        if (o == null || getClass() != o.getClass()) return false;
        Cliente cliente = (Cliente) o;
        return codigo.equals(cliente.getCodigo());
    }

    public int hashCode() {
        return codigo.hashCode();
    }

}
