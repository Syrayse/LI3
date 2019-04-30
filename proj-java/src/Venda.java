import java.io.Serializable;

public class Venda implements IVenda, Serializable {

    private String codigoProduto;
    private double preco;
    private int unidades;
    private String codigoPromo;
    private String codigoCliente;
    private int mes;
    private int filial;

    public Venda() {
        codigoProduto = "";
        preco = -1;
        unidades = -1;
        codigoPromo = "";
        codigoCliente = "";
        mes = -1;
        filial = -1;
    }

    public Venda(String codigoProduto, double preco, int unidades, String codigoPromo, String codigoCliente, int mes, int filial) {
        this.codigoProduto = codigoProduto;
        this.preco = preco;
        this.unidades = unidades;
        this.codigoPromo = codigoPromo;
        this.codigoCliente = codigoCliente;
        this.mes = mes;
        this.filial = filial;
    }

    public String getCodigoProduto() {
        return codigoProduto;
    }

    public double getPreco() {
        return preco;
    }

    public int getUnidades() {
        return unidades;
    }

    public String getCodigoPromo() {
        return codigoPromo;
    }

    public String getCodigoCliente() {
        return codigoCliente;
    }

    public int getMes() {
        return mes;
    }

    public int getFilial() {
        return filial;
    }

    public double getReceita() {
        return unidades * preco;
    }

    public boolean equals(Object o) {
        if (this == o) return true;
        if (o == null || getClass() != o.getClass()) return false;
        Venda venda = (Venda) o;
        return Double.compare(preco, venda.getPreco()) == 0 &&
                unidades == venda.getUnidades() &&
                mes == venda.getMes() &&
                filial == venda.getFilial() &&
                codigoProduto.equals(venda.getCodigoProduto()) &&
                codigoPromo.equals(venda.getCodigoPromo()) &&
                codigoCliente.equals(venda.getCodigoCliente());
    }

}
