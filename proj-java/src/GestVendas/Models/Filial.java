package GestVendas.Models;

import GestVendas.Exceptions.ClienteInexistenteException;
import GestVendas.Exceptions.ProdutoInexistenteException;
import GestVendas.Models.AuxModels.InterfInfoMensal;
import GestVendas.lib.Par;

import java.io.Serializable;
import java.util.List;
import java.util.Set;
import java.util.TreeSet;

public class Filial implements IFilial, Serializable {

    public int getNumVendas() {
        return 0;
    }

    public int getNumVendas(int mes) {
        return 0;
    }

    public int getNumClientes(int mes) {
        return 0;
    }

    public int getNumClientes(String prodCode) {
        return 0;
    }

    public Set<String> getClientes(int mes) {
        return null;
    }

    public List<String> getTop3Compradores() {
        return null;
    }

    public InterfInfoMensal getInfo(String clientCode) throws ClienteInexistenteException {
        return null;
    }

    public InterfInfoMensal getInfoProduto(String prodCode) throws ProdutoInexistenteException {
        return null;
    }

    public InterfInfoMensal getInfoCliente(String clientCode) throws ClienteInexistenteException {
        return null;
    }

    public TreeSet<Par<String, Integer>> getClientesProductSum(String clientCode) throws ClienteInexistenteException {
        return null;
    }

    public TreeSet<Par<String, Integer>> getTopNVersatileClientes(int N) {
        return null;
    }

    public List<Par<String, Double>> getMelhoresClientes(String prodCode, int N) throws ProdutoInexistenteException {
        return null;
    }
}
