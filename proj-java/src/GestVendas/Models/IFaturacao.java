package GestVendas.Models;

import GestVendas.Exceptions.ProdutoInexistenteException;
import GestVendas.Models.AuxModels.InterfStatInfo;

import java.util.List;
import java.util.Set;

public interface IFaturacao {

    int getNumVendas(int mes);

    Set<String> getCodigoProdutos();

    InterfStatInfo getInfo(String prodCode, int n_filiais) throws ProdutoInexistenteException;

    List<String> getNMaisVendidos(int N);
}
