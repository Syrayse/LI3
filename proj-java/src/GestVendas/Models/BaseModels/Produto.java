package GestVendas.Models.BaseModels;

import java.io.Serializable;

public class Produto implements IProduto, Comparable<Produto>, Serializable {

    private String codigo;

    public Produto() {
        codigo = "";
    }

    public Produto(String codigo) {
        this.codigo = codigo;
    }

    public String getCodigo() {
        return codigo;
    }

    public int compareTo(Produto p) {
        return this.codigo.compareTo(p.getCodigo());
    }

    public boolean equals(Object o) {
        if (this == o) return true;
        if (o == null || getClass() != o.getClass()) return false;
        Produto produto = (Produto) o;
        return codigo.equals(produto.getCodigo());
    }

    public int hashCode() {
        return codigo.hashCode();
    }
}