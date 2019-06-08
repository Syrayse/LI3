package GestVendas.Models;

import GestVendas.Exceptions.ClienteInexistenteException;
import GestVendas.Exceptions.ProdutoInexistenteException;
import GestVendas.Models.AuxModels.*;
import GestVendas.lib.Common;
import GestVendas.lib.Par;

import java.io.Serializable;
import java.util.*;

public class Filial implements IFilial, Serializable {

    private int[] numVendas;
    private Map<String, Set<String>> clientSide;
    private Map<String, Map<String, IQuantMoney[]>> productSide;

    public Filial() {
        int meses = Common.MES_MAX;
        numVendas = new int[meses];

        for (int i = 0; i < meses; i++)
            numVendas[i] = 0;

        clientSide = new HashMap<>();
        productSide = new HashMap<>();
    }

    public IFilial insereVenda(String codCliente, String codProd, int mes, int quantidade, double receita) {
        Map<String, IQuantMoney[]> maps;
        Set<String> sets;
        IQuantMoney[] arr;

        maps = productSide.get(codProd);

        if (maps == null)
            maps = new HashMap<>();

        arr = maps.get(codCliente);

        if (arr == null)
            arr = newQuants();

        arr[mes - 1].addQuantidade(quantidade);
        arr[mes - 1].addReceita(receita);
        maps.put(codCliente, arr);

        productSide.put(codProd, maps);

        sets = clientSide.get(codCliente);

        if (sets == null) {
            sets = new HashSet<>();
        }
        sets.add(codProd);
        clientSide.put(codCliente, sets);

        numVendas[mes - 1]++;

        return this;
    }

    public int getNumVendas() {
        int r = 0;

        for (int numVenda : numVendas) r += numVenda;

        return r;
    }

    public int getNumVendas(int mes) {
        return numVendas[mes - 1];
    }

    public int getNumClientes() {
        return clientSide.size();
    }

    public int getNumClientes(int mes) {
        return (int) clientSide.keySet().stream().filter(s -> clientSide.get(s).stream()
                .anyMatch(l -> !productSide.get(l).get(s)[mes - 1].isEmpty()))
                .count();
    }

    public int getNumClientes(String prodCode) {
        return productSide.containsKey(prodCode) ? productSide.get(prodCode).size() : 0;
    }

    public List<Par<String, Double>> getTop3Compradores() {
        Comparator<Par<String, Double>> compGasto = (p1, p2) -> (-1) * Double.compare(p1.getValue(), p2.getValue());
        PriorityQueue<Par<String, Double>> orde = new PriorityQueue<>(clientSide.size(), compGasto);
        List<Par<String, Double>> list = new ArrayList<>(Math.min(3, clientSide.size()));

        clientSide.forEach(
                (k, v) -> {
                    orde.add(new Par<>(
                            k,
                            v.stream().mapToDouble(s -> getReceita(getIQM(s, k))).sum()
                    ));
                }
        );

        for (int i = 0; i < 3 && orde.size() > 0; i++) {
            list.add(orde.poll());
        }

        return list;
    }

    public InterfInfoMensal getInfoProduto(String prodCode) throws ProdutoInexistenteException {
        safeGuardProduto(prodCode);
        InterfInfoMensal iim = new InfoMensal();
        int meses = Common.MES_MAX;

        productSide.get(prodCode).forEach(
                (k, v) -> updateIIM(iim, v)
        );

        return iim;
    }

    public InterfInfoMensal getInfoCliente(String clientCode) throws ClienteInexistenteException {
        safeGuardCliente(clientCode);
        InterfInfoMensal iim = new InfoMensal();

        clientSide.get(clientCode).forEach(
                s -> updateIIM(iim, getIQM(s, clientCode))
        );

        return iim;
    }

    public TreeSet<Par<String, Integer>> getClientesProductSum(String clientCode) throws ClienteInexistenteException {
        safeGuardCliente(clientCode);
        Comparator<Par<String, Integer>> comparaQuant = (p1, p2) -> (-1) * Integer.compare(p1.getValue(), p2.getValue());
        TreeSet<Par<String, Integer>> tree = new TreeSet<>(comparaQuant);

        clientSide.get(clientCode).forEach(
                s -> tree.add(new Par<>(s, getQuants(getIQM(s, clientCode))))
        );

        return tree;
    }

    public List<Par<String, Integer>> getTopNVersatileClientes(int N) {
        Comparator<Par<String, Integer>> comparaVersatil = (p1, p2) -> (-1) * Integer.compare(p1.getValue(), p2.getValue());
        PriorityQueue<Par<String, Integer>> orde = new PriorityQueue<>(clientSide.size(), comparaVersatil);
        List<Par<String, Integer>> list = new ArrayList<>(Math.min(N, clientSide.size()));

        clientSide.forEach(
                (k, v) -> {
                    orde.add(new Par<>(k, v.size()));
                }
        );

        for (int i = 0; i < N && orde.size() > 0; i++) {
            list.add(orde.poll());
        }

        return list;
    }

    public List<Par<String, Double>> getMelhoresClientes(String prodCode, int N) throws ProdutoInexistenteException {
        safeGuardProduto(prodCode);

        Comparator<Par<String, Double>> compGasto = (p1, p2) -> (-1) * Double.compare(p1.getValue(), p2.getValue());
        PriorityQueue<Par<String, Double>> orde = new PriorityQueue<>(clientSide.size(), compGasto);
        List<Par<String, Double>> list = new ArrayList<>(Math.min(N, clientSide.size()));

        productSide.get(prodCode).forEach(
                (k, v) -> orde.add(new Par<>(k, getReceita(v)))
        );

        for (int i = 0; i < N && orde.size() > 0; i++) {
            list.add(orde.poll());
        }

        return list;
    }

    public IMonthlyRep getMonthRepDintis() {
        IMonthlyRep r = new MonthlyRep();

        for (int i = 0; i < Common.MES_MAX; i++)
            r.addToMonth(i + 1, this.getNumClientes(i + 1));

        return r;
    }

    public IMonthlyRep getComprasMes() {
        IMonthlyRep r = new MonthlyRep();

        for (int i = 0; i < Common.MES_MAX; i++)
            r.addToMonth(i + 1, numVendas[i]);

        return r;
    }

    private void safeGuardProduto(String prodCode) throws ProdutoInexistenteException {
        if (!productSide.containsKey(prodCode))
            throw new ProdutoInexistenteException("O produto " + prodCode + " não possui compras registadas");
    }

    private void safeGuardCliente(String clientCode) throws ClienteInexistenteException {
        if (!clientSide.containsKey(clientCode))
            throw new ClienteInexistenteException("O cliente " + clientCode + " não possui compras registadas");
    }

    private IQuantMoney[] newQuants() {
        IQuantMoney[] r = new IQuantMoney[Common.MES_MAX];

        for (int i = 0; i < Common.MES_MAX; i++)
            r[i] = new QuantMoney();

        return r;
    }

    private double getReceita(IQuantMoney[] q) {
        int meses = Common.MES_MAX;
        double r = 0.0;

        for (int i = 0; i < meses; i++)
            r += q[i].getReceita();

        return r;
    }

    private int getQuants(IQuantMoney[] q) {
        int meses = Common.MES_MAX;
        int r = 0;

        for (int i = 0; i < meses; i++)
            r += q[i].getQuantidade();

        return r;
    }

    private IQuantMoney[] getIQM(String codProd, String codCliente) {
        return productSide.get(codProd).get(codCliente);
    }

    private void updateIIM(InterfInfoMensal iim, IQuantMoney[] v) {
        int meses = Common.MES_MAX;
        for (int i = 0; i < meses; i++) {
            if (!v[i].isEmpty()) {
                iim.insereQuant(i + 1, v[i].getQuantidade());
                iim.insereReceita(i + 1, v[i].getReceita());
                iim.insereQuandDis(i + 1, 1);
            }
        }
    }

}
