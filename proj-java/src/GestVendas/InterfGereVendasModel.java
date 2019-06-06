package GestVendas;

import GestVendas.Exceptions.ClienteInexistenteException;
import GestVendas.Exceptions.FilialInvalidException;
import GestVendas.Exceptions.InvalidConfigException;
import GestVendas.Exceptions.ProdutoInexistenteException;
import GestVendas.Models.AuxModels.IGlobalRep;
import GestVendas.Models.AuxModels.IMonthlyRep;
import GestVendas.Models.AuxModels.InterfInfoMensal;
import GestVendas.Models.AuxModels.InterfStatInfo;
import GestVendas.lib.Par;

import java.io.IOException;
import java.util.List;
import java.util.TreeSet;

public interface InterfGereVendasModel {

    boolean isValid();

    InterfGereVendasModel createData(String configs) throws IOException, InvalidConfigException;

    InterfGereVendasModel setProdutos(String file) throws IOException;

    InterfGereVendasModel setClientes(String file) throws IOException;

    InterfGereVendasModel setVendas(String file, int n_filiais) throws IOException;

    InterfGereVendasModel carregaEstado(String fich) throws IOException, ClassNotFoundException;

    void guardaEstado(String fich) throws IOException;


    // Interrogacoes Estatisticas

    // Q1
    String ultimoFicheiroVendas();

    // Q2
    int getNumVendasErradas();

    // Q3
    int getNumProdutos();

    // Q4
    int getNumProdutosComprados();

    // Q5
    int getNumProdutosNaoComprados();

    // Q6
    int getNumClientes();

    // Q7
    int getNumClientesCompradores();

    // Q8
    int getNumClientesNaoCompradores();

    // Q9
    int getNumVendasZero();

    // Q10
    double getFaturacao();

    // Q11
    IMonthlyRep getComprasPorMes();

    // Q12
    IGlobalRep getFaturacaoPorMesFil();

    // Q13
    List<IMonthlyRep> getNumDistintosClienteMonthFil();

    // Interrogacoes Dinamicas

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
    List<Par<String, Integer>> getTopNProdutosMaisDistintos(int N);

    // Q7
    List<String> getTop3Compradores(int filial) throws FilialInvalidException;

    // Q8
    TreeSet<Par<String,Integer>> getTopNVersatileClientes(int N);

    // Q9
    List<Par<String, Double>> getMelhoresClientes(String prodCode, int N) throws ProdutoInexistenteException;

    // Q10
    InterfStatInfo getFaturacaoTotal(String prodCode) throws ProdutoInexistenteException; // X


    int getNFiliais();

}