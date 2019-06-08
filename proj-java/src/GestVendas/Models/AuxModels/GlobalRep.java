package GestVendas.Models.AuxModels;

import GestVendas.lib.Common;

import java.io.Serializable;
import java.util.ArrayList;
import java.util.List;

public class GlobalRep implements IGlobalRep, Serializable {

    List<List<Double>> global;

    public GlobalRep() {
        global = new ArrayList<>();
    }

    public GlobalRep(int filial) {
        global = new ArrayList<>(filial + 1);

        for (int i = 0; i <= filial; i++) {
            List<Double> mensal = new ArrayList<>(12);
            for (int j = 0; j < 12; j++) {
                mensal.add(0.0);
            }
            global.add(i, mensal);
        }
    }

    public GlobalRep(GlobalRep g) {
        int filiais = g.getNumFiliais();
        global = new ArrayList<>(filiais);

        global.add(0, g.getMonthly());

        for (int i = 1; i <= filiais; i++) {
            global.add(i, g.getMonthly(i));
        }
    }

    public int getNumFiliais() {
        return global.size() - 1;
    }

    public IGlobalRep addToFilial(int filial, int mes, double val) {
        if (filial > 0) {
            double quanto;
            List<Double> amounts = global.get(filial);
            List<Double> amountsG = global.get(0);

            amounts = amounts == null ? makeMonthly() : amounts;

            quanto = amounts.get(mes - 1) + val;

            amounts.add(mes - 1, quanto);

            global.add(filial, amounts);

            amountsG = amountsG == null ? makeMonthly() : amountsG;

            quanto = amountsG.get(mes - 1) + val;

            amountsG.add(mes - 1, quanto);

            global.add(0, amountsG);
        }
        return this;
    }

    public double getTotal(int filial, int mes) {
        return global.get(filial).get(mes - 1);
    }

    public double getTotal(int mes) {
        return global.get(0).get(mes - 1);
    }

    public String toString() {

        StringBuilder sb = new StringBuilder();

        int filiais, meses = Common.MES_MAX;
        filiais = this.getNumFiliais();

        sb.append("MESES ->\t");

        for (int i = 0; i < meses; i++) {
            sb.append(String.format("|    %2d    |", i + 1));
        }

        sb.append("\n");

        sb.append("FILIAIS\n");

        for (int i = 1; i <= filiais; i++) {
            sb.append(String.format("%d\t\t\t", i));

            for (int j = 1; j <= meses; j++) {
                sb.append(String.format("   %6.2f   ", getTotal(i, j)));
            }

            sb.append("\n");
        }

        sb.append("Global\t\t");

        for (int j = 1; j <= meses; j++) {
            sb.append(String.format("   %6.2f   ", getTotal(j)));
        }

        return sb.toString();
    }

    public IGlobalRep clone() {
        return new GlobalRep(this);
    }

    private List<Double> makeMonthly() {
        return new ArrayList<>(Common.MES_MAX);
    }

    private List<Double> getMonthly() {
        return new ArrayList<>(global.get(0));
    }

    private List<Double> getMonthly(int filial) {
        return new ArrayList<>(global.get(filial));
    }

}
