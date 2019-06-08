package GestVendas.Models;

import GestVendas.Exceptions.ProdutoInexistenteException;
import GestVendas.Models.AuxModels.IGlobalRep;
import GestVendas.Models.AuxModels.IQuantMoney;
import GestVendas.lib.Common;

import java.io.Serializable;
import java.util.*;

public class Faturacao implements IFaturacao, Serializable {

    private Map<String, Map<String, IQuantMoney[]>> productSide;
    private int[] numVendas;
    private double[] faturacao;
    private static int meses = Common.MES_MAX;

    public Faturacao() {
        numVendas = new int[meses];
        faturacao = new double[meses];
        productSide = new HashMap<>();

        for (int i = 0; i < meses; i++) {
            numVendas[i] = 0;
            faturacao[i] = 0.0;
        }
    }

    public int getNumVendas(int mes) {
        return numVendas[mes - 1];
    }

    public int getNumProdutos() {
        int i = 0;
        for (Map<String, IQuantMoney[]> letter : productSide.values())
            i += letter.size();
        return i;
    }

    public Set<String> getCodigoProdutos() {
        Set<String> prods = new HashSet<>();

        for (Map<String, IQuantMoney[]> letter : productSide.values())
            prods.addAll(letter.keySet());

            return prods;
    }


    public IGlobalRep getInfo(String prodCode, int n_filiais) throws ProdutoInexistenteException {
        return null;
    }

    public List<String> getNMaisVendidos(int N) {

        return null;
    }

    public double getFaturacao() {
        double fat = 0.0;

        for (int i = 0; i < 12; i++) {
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
