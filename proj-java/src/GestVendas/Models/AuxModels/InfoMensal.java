package GestVendas.Models.AuxModels;

import GestVendas.lib.Common;

import java.io.Serializable;

public class InfoMensal implements InterfInfoMensal, Serializable {

    private int[] quantCompras;
    private int[] quantDistint;
    private double[] receita;

    public InfoMensal() {
        quantCompras = new int[Common.MES_MAX];
        quantDistint = new int[Common.MES_MAX];
        receita = new double[Common.MES_MAX];
    }

    public InterfInfoMensal insereQuant(int mes, int quant) {
        quantCompras[mes - 1] += quant;
        return this;
    }

    public InterfInfoMensal insereQuandDis(int mes, int quant) {
        quantDistint[mes - 1] += quant;
        return this;
    }

    public InterfInfoMensal insereReceita(int mes, double rec) {
        receita[mes - 1] += rec;
        return this;
    }

    public int getQuant(int mes) {
        return quantCompras[mes - 1];
    }

    public int getQuantDis(int mes) {
        return quantDistint[mes - 1];
    }

    public double getReceita(int mes) {
        return receita[mes - 1];
    }

    public String toString() {
        StringBuilder sb = new StringBuilder();
        int meses = Common.MES_MAX;

        sb.append("MESES ->\t");

        for (int i = 0; i < meses; i++) {
            sb.append(String.format("|    %2d    |", i + 1));
        }

        sb.append("\n");

        sb.append("QUANT ->\t");

        for (int i = 0; i < meses; i++) {
            sb.append(String.format("%8d \t", quantCompras[i]));
        }

        sb.append("\n");

        sb.append("DISTINT ->\t");

        for (int i = 0; i < meses; i++) {
            sb.append(String.format("%8d \t", quantDistint[i]));
        }

        sb.append("\n");

        sb.append("RECEITA ->\t");

        for (int i = 0; i < meses; i++) {
            sb.append(String.format("  %8.2f\t", receita[i]));
        }

        sb.append("\n");

        return sb.toString();
    }

    public InterfInfoMensal clone() {
        InfoMensal im = new InfoMensal();
        int meses = Common.MES_MAX;

        for (int i = 0; i < meses; i++)
            im.insereQuant(i + 1, this.getQuant(i + 1));

        for (int i = 0; i < meses; i++)
            im.insereQuandDis(i + 1, this.getQuantDis(i + 1));

        for (int i = 0; i < meses; i++)
            im.insereReceita(i + 1, this.getReceita(i + 1));

        return im;
    }

}
