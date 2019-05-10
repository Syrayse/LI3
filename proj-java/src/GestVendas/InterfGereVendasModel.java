package GestVendas;

import GestVendas.Models.AuxModels.InterfInfoMensal;
import GestVendas.Models.AuxModels.InterfStatInfo;
import GestVendas.lib.Par;

import java.util.TreeSet;

public interface InterfGereVendasModel {

    InterfGereVendasModel createData();
    // Q1
    TreeSet<String> getProdutosNaoVendidos(); // X

    // Q2
    Par<Integer, Integer> getVendasInfo(int mes); // X

    Par<Integer, Integer> getVendasInfo(int mes, int filial); // X

    // Q3
    InterfInfoMensal getInfoMensalCliente(String clientCode);

    // Q4
    InterfInfoMensal getInfoMensalProd(String prodCode);

    // Q5
    TreeSet<Par<String,Integer>> getTopProdutosMaisComprados(String clientCode);

    // Q6
    TreeSet<Par<String, Integer>> getTopNProdutosMaisDistintos(int N);

    // Q7
    TreeSet<String> getTop3Compradores();

    // Q8
    TreeSet<Par<String,Integer>> getTopNVersatileClientes(int N);

    // Q9
    TreeSet<Par<String,Double>> getMelhoresClientes(String prodCode);

    // Q10
    InterfStatInfo getFaturacaoTotal(String prodCode);


    int getNFiliais();

}