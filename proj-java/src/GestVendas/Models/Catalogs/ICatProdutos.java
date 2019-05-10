package GestVendas.Models.Catalogs;

import GestVendas.Models.BaseModels.IProduto;

import java.util.TreeSet;

public interface ICatProdutos {

    int size();
    ICatProdutos insereProduto(IProduto p);
    boolean existeProduto(IProduto p);
    boolean existeProduto(String prodCode);

    TreeSet<String> getCodigoProdutos();

}
