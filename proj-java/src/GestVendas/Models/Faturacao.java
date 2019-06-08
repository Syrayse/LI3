package GestVendas.Models;

import GestVendas.Comparators.CompMaisGasto;
import GestVendas.Exceptions.ProdutoInexistenteException;
import GestVendas.Models.AuxModels.*;
import GestVendas.lib.Common;

import java.io.Serializable;
import java.util.*;
import java.util.stream.Collectors;

public class Faturacao implements IFaturacao, Serializable {

    private Map<String, IGlobalRep> productSideFat;
    private Map<String, IMonthlyRep> productSideVendas;
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

        productSideFat = new HashMap<>();
        productSideVendas = new HashMap<>();
    }

    public IFaturacao insereVenda(String codProd, int mes, int quantidade, double receita, int fil) {

        IGlobalRep maps;
        IMonthlyRep arr;

        maps = productSideFat.get(codProd);
        arr = productSideVendas.get(codProd);

        if (maps == null)
            maps = new GlobalRep(3);
        if (arr == null)
            arr = new MonthlyRep();

        maps = maps.addToFilial(fil, mes, receita);
        arr = arr.addToMonth(mes, quantidade);

        productSideFat.put(codProd, maps);
        productSideVendas.put(codProd, arr);

        numVendas[mes - 1] += quantidade;
        faturacao[mes - 1] += receita;

        return this;
    }

    public int getNumVendas(int mes) {
        return numVendas[mes - 1];
    }

    public int getNumProdutos() {
        return productSideFat.size();
    }

    public Set<String> getCodigoProdutos() {
        return productSideFat.keySet();
    }

    public IGlobalRep getInfo(String prodCode, int n_filiais) throws ProdutoInexistenteException {
        IGlobalRep res = productSideFat.get(prodCode);


        if (res == null) {
            throw new ProdutoInexistenteException();
        }
        System.out.println(res.getNumFiliais());

        return res;
    }

    public List<String> getNMaisVendidos(int N) {
        Map<Integer, String> prods = new HashMap<>();
        int v;
        MonthlyRep mr;

        for (Map.Entry entry : productSideVendas.entrySet()){
            mr = (MonthlyRep) entry.getValue();

            v = 0;
            for (int i = 1; i <= meses; i++) {
                v += mr.getMonth(i);
            }
            String prod = (String) entry.getKey();
            prods.put(v, prod);
        }

        Map<Integer, String> sorted = new LinkedHashMap<>();

        prods.entrySet()
                .stream()
                .sorted(Map.Entry.comparingByKey(Comparator.reverseOrder()))
                .forEachOrdered(x -> sorted.put(x.getKey(), x.getValue()));

        return sorted.values().stream().limit(N).collect(Collectors.toList());
    }

    public double getFaturacao() {
        double fat = 0.0;

        for (int i = 0; i < meses; i++) {
            fat += faturacao[i];
        }

        /*
        for (Map<String, IQuantMoney[]> letter : productSide.values()) {
            for (IQuantMoney[] as : letter.values()) {
                for (int i = 0; i < 12; i++) {
                    fat += as[i].getReceita();
                }
            }
        }
         */
        return fat;
    }
}
