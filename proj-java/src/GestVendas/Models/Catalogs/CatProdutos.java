package GestVendas.Models.Catalogs;

import GestVendas.Models.BaseModels.IProduto;

import java.io.Serializable;
import java.util.Map;
import java.util.Set;
import java.util.TreeMap;
import java.util.TreeSet;

public class CatProdutos implements ICatProdutos, Serializable {

    private Map<String, IProduto> produtos;

    public CatProdutos() {
        produtos = new TreeMap<>();
    }

    public int size() {
        return produtos.size();
    }

    public ICatProdutos insereProduto(IProduto p) {
        produtos.put(p.getCodigo(),p);
        return this;
    }

    public boolean existeProduto(IProduto p) {
        return produtos.containsKey(p.getCodigo());
    }

    public boolean existeProduto(String prodCode) {
        return produtos.containsKey(prodCode);
    }

    public Set<String> getCodigoProdutos() {
        return new TreeSet<String>(produtos.keySet());
    }

}
