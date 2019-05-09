package GestVendas.Models.Catalogs;

import GestVendas.Models.BaseModels.IProduto;

import java.util.Set;

public interface ICatProdutos {

    int size();
    ICatProdutos insereProduto(IProduto p);
    boolean existeProduto(IProduto p);
    boolean existeProduto(String prodCode);
    Set<String> getCodigoProdutos();

}
