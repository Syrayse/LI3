import java.util.Objects;

public class Cliente {

    private String clientCode;

    public Cliente(String clientCode) {
        this.clientCode = clientCode;
    }

    public Cliente(Cliente cliente) {
        this.clientCode = cliente.getClientCode();
    }

    public String getClientCode() {
        return this.clientCode;
    }

    public void setClientCode(String clientCode) {
        this.clientCode = clientCode;
    }

    @Override
    public String toString() {
        final StringBuffer sb = new StringBuffer("Cliente{");
        sb.append("clientCode='").append(this.clientCode).append('\'');
        sb.append('}');
        return sb.toString();
    }

    @Override
    public boolean equals(Object o) {
        if (this == o) return true;
        if (o == null || getClass() != o.getClass()) return false;
        Cliente cliente = (Cliente) o;
        return this.clientCode.equals(cliente.clientCode);
    }

    @Override
    public int hashCode() {
        return this.clientCode.hashCode();
    }

    @Override
    public Cliente clone() {
        return new Cliente(this);
    }
}
