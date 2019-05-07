package GestVendas.Models.Catalogs;

import java.io.Serializable;
import java.util.Map;

public class CatProdutos implements ICatProdutos, Serializable {

    private Map<String,IProduto> produtos;

    public CatProdutos() {
        produtos = new TreeMap<>();
    }

    public int size() {
        return produtos.size();
    }

    public ICatProdutos insereProduto(IProduto p) {
        produtos.add(p);
        return this;
    }

    public boolean existeProduto(IProduto p) {
        return produtos.containsKey(p.getCodigo());
    }

    public boolean existeProduto(String prodCode) {
        return produtos.containsKey(prodCode);
    }

    public Set<String> getprodutos() {
        return new TreeSet<String>(produtos.keySet());
    }

}
