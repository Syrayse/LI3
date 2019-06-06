package GestVendas.Models;

import GestVendas.Exceptions.ClienteInexistenteException;
import GestVendas.Exceptions.ProdutoInexistenteException;
import GestVendas.Models.AuxModels.InterfInfoMensal;
import GestVendas.lib.Par;

import java.util.List;
import java.util.Set;
import java.util.TreeSet;

public interface IFilial {

    int getNumVendas();

    int getNumVendas(int mes);

    int getNumClientes(int mes);

    int getNumClientes(String prodCode);

    Set<String> getClientes(int mes);

    List<String> getTop3Compradores();

    InterfInfoMensal getInfoCliente(String clientCode) throws ClienteInexistenteException;

    InterfInfoMensal getInfoProduto(String prodCode) throws ProdutoInexistenteException;

    TreeSet<Par<String, Integer>> getClientesProductSum(String clientCode) throws ClienteInexistenteException;

    TreeSet<Par<String, Integer>> getTopNVersatileClientes(int N);

    List<Par<String, Double>> getMelhoresClientes(String prodCode, int N) throws ProdutoInexistenteException;
}
