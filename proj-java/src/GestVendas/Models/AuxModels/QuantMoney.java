package GestVendas.Models.AuxModels;

import java.io.Serializable;

public class QuantMoney implements IQuantMoney, Serializable {

    private int quantidade;
    private double receita;

    public QuantMoney() {
        quantidade = 0;
        receita = 0.0;
    }

    public QuantMoney(QuantMoney qm) {
        quantidade = qm.getQuantidade();
        receita = qm.getReceita();
    }

    public int getQuantidade() {
        return quantidade;
    }

    public double getReceita() {
        return receita;
    }

    public IQuantMoney addQuantidade(int q) {
        quantidade += q;
        return this;
    }

    public IQuantMoney addReceita(double r) {
        receita += r;
        return this;
    }

    public boolean isEmpty() {
        return quantidade == 0 && receita == 0.0;
    }

    public IQuantMoney clone() {
        return new QuantMoney(this);
    }
}
