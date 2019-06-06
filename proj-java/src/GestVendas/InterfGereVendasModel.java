package GestVendas;

import GestVendas.Exceptions.ClienteInexistenteException;
import GestVendas.Exceptions.ProdutoInexistenteException;
import GestVendas.Models.AuxModels.InterfInfoMensal;
import GestVendas.Models.AuxModels.InterfStatInfo;
import GestVendas.lib.Par;

import java.io.IOException;
import java.util.List;
import java.util.TreeSet;

public interface InterfGereVendasModel {

    InterfGereVendasModel createData();

    InterfGereVendasModel carregaEstado(String fich) throws IOException, ClassNotFoundException;

    void guardaEstado(String fich) throws IOException;

    // Q1
    TreeSet<String> getProdutosNaoVendidos(); // X

    // Q2
    Par<Integer, Integer> getVendasInfo(int mes); // X

    Par<Integer, Integer> getVendasInfo(int mes, int filial); // X

    // Q3
    InterfInfoMensal getInfoMensalCliente(String clientCode) throws ClienteInexistenteException;

    // Q4
    InterfInfoMensal getInfoMensalProd(String prodCode) throws ProdutoInexistenteException;

    // Q5
    TreeSet<Par<String, Integer>> getTopProdutosMaisComprados(String clientCode) throws ClienteInexistenteException;

    // Q6
    List<Par<String, Integer>> getTopNProdutosMaisDistintos(int N);

    // Q7
    List<String> getTop3Compradores(int filial);

    // Q8
    TreeSet<Par<String,Integer>> getTopNVersatileClientes(int N);

    // Q9
    List<Par<String, Double>> getMelhoresClientes(String prodCode, int N) throws ProdutoInexistenteException;

    // Q10
    InterfStatInfo getFaturacaoTotal(String prodCode) throws ProdutoInexistenteException; // X


    int getNFiliais();

}