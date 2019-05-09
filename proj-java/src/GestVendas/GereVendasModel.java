package GestVendas;

import GestVendas.Models.AuxModels.InterfInfoMensal;
import GestVendas.Models.AuxModels.InterfStatInfo;
import GestVendas.lib.Par;

import java.io.Serializable;
import java.util.TreeSet;

public class GereVendasModel implements InterfGereVendasModel, Serializable {

    public InterfGereVendasModel setCatProdutos(String file) {
        return null;
    }

    public InterfGereVendasModel setCatClientes(String file) {
        return null;
    }

    public InterfGereVendasModel setFaturacaoFilial(String file) {
        return null;
    }

    // Q1
    public TreeSet<String> getProdutosNaoVendidos() {
        return null;
    }

    // Q2
    public Par<Integer,Integer> getVendasInfo(int mes) {
        return null;
    }

    public Par<Integer,Integer> getVendasInfo(int mes, int filial) {
        return null;
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
    public TreeSet<Par<String,Integer>> getTopNProdutosMaisVendidos(int N) {
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
