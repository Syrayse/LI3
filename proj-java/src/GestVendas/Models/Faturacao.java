package GestVendas.Models;

import GestVendas.Exceptions.ProdutoInexistenteException;
import GestVendas.Models.AuxModels.FatProd;
import GestVendas.Models.AuxModels.GlobalRep;
import GestVendas.Models.AuxModels.IGlobalRep;
import GestVendas.lib.Common;
import GestVendas.lib.Par;

import java.io.Serializable;
import java.util.*;

public class Faturacao implements IFaturacao, Serializable {

    private Map<String, List<FatProd>> produtos;
    private int[] numVendas;
    private double[] faturacao;

    private static int meses = Common.MES_MAX;

    public Faturacao() {
        numVendas = new int[meses];
        faturacao = new double[meses];

        for (int i = 0; i < meses; i++) {
            numVendas[i] = 0;
            faturacao [i] = 0.0;
        }

        produtos = new HashMap<>();
    }

    public IFaturacao insereVenda(String codProd, int mes, int quantidade, double receita, int fil) {

        List<FatProd> list = produtos.get(codProd);

        if (list == null)
            list = new ArrayList<>(5);

        list.add(new FatProd(fil, mes, quantidade, receita));

        produtos.put(codProd, list);

        numVendas[mes - 1] += quantidade;
        faturacao[mes - 1] += receita;

        return this;
    }

    public int getNumVendas(int mes) {
        return numVendas[mes - 1];
    }

    public int getNumProdutos() {
        return produtos.size();
    }

    public Set<String> getCodigoProdutos() {
        return produtos.keySet();
    }

    public IGlobalRep getInfo(String prodCode, int n_filiais) throws ProdutoInexistenteException {
        safeGuardProduto(prodCode);
        IGlobalRep igr = new GlobalRep(n_filiais);
        addToGlobal(igr, produtos.get(prodCode));
        return igr;
    }

    public List<String> getNMaisVendidos(int N) {
        Comparator<Par<String, Integer>> comp = (p1, p2) -> (-1) * Integer.compare(p1.getValue(), p2.getValue());
        List<String> list = new ArrayList<>();
        PriorityQueue<Par<String, Integer>> prio = new PriorityQueue<>(produtos.size(), comp);

        produtos.forEach(
                (k, v) -> prio.add(new Par<>(k, sumQuants(v)))
        );

        for (int i = 0; i < N && prio.size() > 0; i++) {
            list.add(i, prio.poll().getKey());
        }

        return list;
    }

    public double getFaturacao() {
        double fat = 0.0;

        for (int i = 0; i < meses; i++) {
            fat += faturacao[i];
        }

        return fat;
    }

    public IGlobalRep getOverall(int n_filiais) {
        IGlobalRep igr = new GlobalRep(n_filiais);
        produtos.values().forEach(l -> addToGlobal(igr, l));
        return igr;
    }

    private void addToGlobal(IGlobalRep igp, List<FatProd> l) {
        for (FatProd f : l) {
            if (f.getFilial() <= igp.getNumFiliais())
                igp.addToFilial(f.getFilial(), f.getMes(), f.getReceita());
        }
    }

    private void safeGuardProduto(String prodCode) throws ProdutoInexistenteException {
        if (!produtos.containsKey(prodCode))
            throw new ProdutoInexistenteException("O produto " + prodCode + " nao esta inserido!");
    }

    private int sumQuants(List<FatProd> l) {
        int r = 0;

        for (FatProd fp : l) {
            r += fp.getQuantidade();
        }

        return r;
    }
}
