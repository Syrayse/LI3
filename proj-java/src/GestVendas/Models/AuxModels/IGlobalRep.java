package GestVendas.Models.AuxModels;

public interface IGlobalRep {
    IGlobalRep addToFilial(int filial, int mes, double val);

    double getTotal(int filial, int mes);

    double getTotal(int mes);

    String toString();

    IGlobalRep clone();
}
