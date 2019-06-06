package GestVendas;

import GestVendas.Exceptions.ClienteInexistenteException;
import GestVendas.Exceptions.ProdutoInexistenteException;
import GestVendas.Models.AuxModels.InterfInfoMensal;
import GestVendas.Models.AuxModels.InterfStatInfo;
import GestVendas.Models.Catalogs.ICatClientes;
import GestVendas.Models.Catalogs.ICatProdutos;
import GestVendas.Models.IFaturacao;
import GestVendas.Models.IFilial;
import GestVendas.lib.Par;

import java.io.*;
import java.util.ArrayList;
import java.util.List;
import java.util.TreeSet;

public class GereVendasModel implements InterfGereVendasModel, Serializable {

    private ICatClientes clientes;
    private ICatProdutos produtos;
    private IFaturacao faturacao;
    private IFilial global;
    private List<IFilial> filiais;

    public InterfGereVendasModel createData() {
        return null;
    }

    private InterfGereVendasModel setCatProdutos(String file) {
        return null;
    }

    private InterfGereVendasModel setCatClientes(String file) {
        return null;
    }

    private InterfGereVendasModel setFaturacaoFilial(String file) {
        return null;
    }

    public InterfGereVendasModel carregaEstado(String fich) throws IOException, ClassNotFoundException {
        InterfGereVendasModel tmp = null;

        FileInputStream fileIn = new FileInputStream(fich);
        ObjectInputStream in = new ObjectInputStream(fileIn);

        tmp = (GereVendasModel) in.readObject();

        in.close();
        fileIn.close();

        return tmp;
    }

    public void guardaEstado(String fich) throws IOException {
        ObjectOutputStream out = new ObjectOutputStream(new FileOutputStream(fich));

        out.writeObject(this);

        out.flush();

        out.close();
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
        return new Par<>(faturacao.getNumVendas(mes), global.getNumClientes(mes));
    }

    public Par<Integer, Integer> getVendasInfo(int mes, int filial) {
        IFilial f = filiais.get(filial - 1);

        return new Par<>(f.getNumVendas(mes), f.getNumClientes(mes));
    }

    // Q3
    public InterfInfoMensal getInfoMensalCliente(String clientCode) throws ClienteInexistenteException {
        return global.getInfoCliente(clientCode);
    }

    // Q4
    public InterfInfoMensal getInfoMensalProd(String prodCode) throws ProdutoInexistenteException {
        return global.getInfoProduto(prodCode);
    }

    // Q5
    // Falta definir comparador
    public TreeSet<Par<String, Integer>> getTopProdutosMaisComprados(String clientCode) throws ClienteInexistenteException {
        return global.getClientesProductSum(clientCode);
    }

    // Q6
    public List<Par<String, Integer>> getTopNProdutosMaisDistintos(int N) {
        List<String> mais_vendidos = faturacao.getNMaisVendidos(N);

        List<Par<String, Integer>> result = new ArrayList<>();

        mais_vendidos.forEach(s -> result.add(new Par<>(s, global.getNumClientes(s))));

        return result;
    }

    // Q7
    public List<String> getTop3Compradores(int filial) {
        return filiais.get(filial - 1).getTop3Compradores();
    }

    // Q8
    public TreeSet<Par<String,Integer>> getTopNVersatileClientes(int N) {
        return global.getTopNVersatileClientes(N);
    }

    // Q9
    public List<Par<String, Double>> getMelhoresClientes(String prodCode, int N) throws ProdutoInexistenteException {
        return global.getMelhoresClientes(prodCode, N);
    }

    // Q10
    public InterfStatInfo getFaturacaoTotal(String prodCode) throws ProdutoInexistenteException {
        return faturacao.getInfo(prodCode, filiais.size());
    }

    public int getNFiliais() {
        return filiais.size();
    }
}
