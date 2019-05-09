package GestVendas;

import java.util.TreeSet;

import GestVendas.Models.AuxModels.InterfInfoMensal;
import GestVendas.Models.AuxModels.InterfStatInfo;
import GestVendas.lib.Par;

public interface InterfGereVendasModel {

    InterfGereVendasModel setCatProdutos(String file);
    InterfGereVendasModel setCatClientes(String file);
    InterfGereVendasModel setFaturacaoFilial(String file);
    
    // Q1
    TreeSet<String> getProdutosNaoVendidos();

    // Q2
    Par<Integer,Integer> getVendasInfo(int mes);
    Par<Integer,Integer> getVendasInfo(int mes, int filial);

    // Q3
    InterfInfoMensal getInfoMensalCliente(String clientCode);

    // Q4
    InterfInfoMensal getInfoMensalProd(String prodCode);

    // Q5
    TreeSet<Par<String,Integer>> getTopProdutosMaisComprados(String clientCode);

    // Q6
    TreeSet<Par<String,Integer>> getTopNProdutosMaisVendidos(int N);

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