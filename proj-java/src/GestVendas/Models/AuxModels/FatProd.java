package GestVendas.Models.AuxModels;

public class FatProd {

    private int filial;
    private int mes;
    private int quantidade;
    private double receita;

    public FatProd() {
        filial = 0;
        mes = 0;
        quantidade = 0;
        receita = 0.0;
    }

    public FatProd(int filial, int mes, int quantidade, double receita) {
        this.filial = filial;
        this.mes = mes;
        this.quantidade = quantidade;
        this.receita = receita;
    }

    public int getFilial() {
        return filial;
    }

    public int getMes() {
        return mes;
    }

    public int getQuantidade() {
        return quantidade;
    }

    public double getReceita() {
        return receita;
    }
}
