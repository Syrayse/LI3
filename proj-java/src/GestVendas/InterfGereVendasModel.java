package GestVendas;

import GestVendas.Exceptions.ClienteInexistenteException;
import GestVendas.Exceptions.FilialInvalidException;
import GestVendas.Exceptions.ProdutoInexistenteException;
import GestVendas.Models.AuxModels.InterfInfoMensal;
import GestVendas.Models.AuxModels.InterfStatInfo;
import GestVendas.lib.Par;

import java.io.IOException;
import java.util.TreeSet;

public interface InterfGereVendasModel {

    InterfGereVendasModel createData();

    InterfGereVendasModel carregaEstado(String fich) throws IOException, ClassNotFoundException;

    void guardaEstado(String fich) throws IOException;

    // Q1
    TreeSet<String> getProdutosNaoVendidos(); // X

    // Q2
    Par<Integer, Integer> getVendasInfo(int mes); // X

    Par<Integer, Integer> getVendasInfo(int mes, int filial) throws FilialInvalidException; // X

    // Q3
    InterfInfoMensal getInfoMensalCliente(String clientCode) throws ClienteInexistenteException;

    // Q4
    InterfInfoMensal getInfoMensalProd(String prodCode) throws ProdutoInexistenteException;

    // Q5
    TreeSet<Par<String, Integer>> getTopProdutosMaisComprados(String clientCode) throws ClienteInexistenteException;

    // Q6
    TreeSet<Par<String, Integer>> getTopNProdutosMaisDistintos(int N);

    // Q7
    TreeSet<String> getTop3Compradores();

    // Q8
    TreeSet<Par<String,Integer>> getTopNVersatileClientes(int N);

    // Q9
    TreeSet<Par<String, Double>> getMelhoresClientes(String prodCode) throws ProdutoInexistenteException;

    // Q10
    InterfStatInfo getFaturacaoTotal(String prodCode) throws ProdutoInexistenteException;


    int getNFiliais();

}