package GestVendas.Models;

import GestVendas.Exceptions.ProdutoInexistenteException;
import GestVendas.Models.AuxModels.IGlobalRep;

import java.io.Serializable;
import java.util.List;
import java.util.Set;

public class Faturacao implements IFaturacao, Serializable {

    public int getNumVendas(int mes) {
        return 0;
    }

    public int getNumProdutos() {
        return 0;
    }

    public Set<String> getCodigoProdutos() {
        return null;
    }


    public IGlobalRep getInfo(String prodCode, int n_filiais) throws ProdutoInexistenteException {
        return null;
    }

    public List<String> getNMaisVendidos(int N) {
        return null;
    }

    public double getFaturacao() {
        return 0.0;
    }
}
