package GestVendas.Models.Catalogs;

import java.util.Set;

public interface ICatProdutos {

    int size();
    ICatProdutos insereProduto(IProduto p);
    boolean temProduto(IProduto p);
    Set<IProduto> getProdutosPorLetra();

}
