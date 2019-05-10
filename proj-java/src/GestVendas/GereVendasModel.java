package GestVendas;

import GestVendas.Models.AuxModels.InterfInfoMensal;
import GestVendas.Models.AuxModels.InterfStatInfo;
import GestVendas.Models.Catalogs.ICatClientes;
import GestVendas.Models.Catalogs.ICatProdutos;
import GestVendas.Models.IFaturacao;
import GestVendas.Models.IFilial;
import GestVendas.lib.Common;
import GestVendas.lib.Par;

import java.io.Serializable;
import java.util.HashSet;
import java.util.List;
import java.util.Set;
import java.util.TreeSet;

public class GereVendasModel implements InterfGereVendasModel, Serializable {

    private ICatClientes clientes;
    private ICatProdutos produtos;
    private IFaturacao faturacao;
    private List<IFilial> filiais;

    public InterfGereVendasModel setCatProdutos(String file) {
        return null;
    }

    public InterfGereVendasModel setCatClientes(String file) {
        return null;
    }

    public InterfGereVendasModel setFaturacaoFilial(String file) {
        return null;
    }

    // INTERROGACOES BELOW

    // Q1
    public TreeSet<String> getProdutosNaoVendidos() {
        TreeSet<String> r = produtos.getCodigoProdutos();

        r.removeAll(faturacao.getCodigoProdutos());

        return r;
    }

    // Q2
    public Par<Integer,Integer> getVendasInfo(int mes) {
        Set<String> clientSet = new HashSet<>();

        for (IFilial f : filiais) {
            clientSet.addAll(f.getClientes(mes));
        }

        return new Par<>(faturacao.getNumVendas(mes), clientSet.size());
    }

    public Par<Integer,Integer> getVendasInfo(int mes, int filial) {
        if (!Common.intervaloInclusivo(filial, 1, filiais.size()))
            return null;
        IFilial f = filiais.get(filial - 1);
        return new Par<>(f.getNumVendas(mes), f.getNumClientes(mes));
    }

    // Q3
    public InterfInfoMensal getInfoMensalCliente(String clientCode) {
        return null;
    }

    // Q4
    public InterfInfoMensal getInfoMensalProd(String prodCode) {
        return null;
    }

    // Q5
    public TreeSet<Par<String,Integer>> getTopProdutosMaisComprados(String clientCode) {
        return null;
    }

    // Q6
    public TreeSet<Par<String, Integer>> getTopNProdutosMaisDistintos(int N) {
        return null;
    }

    // Q7
    public TreeSet<String> getTop3Compradores() {
        return null;
    }

    // Q8
    public TreeSet<Par<String,Integer>> getTopNVersatileClientes(int N) {
        return null;
    }

    // Q9
    public TreeSet<Par<String,Double>> getMelhoresClientes(String prodCode) {
        return null;
    }

    // Q10
    public InterfStatInfo getFaturacaoTotal(String prodCode) {
        return null;
    }

    public int getNFiliais() {
        return 0;
    }

}
