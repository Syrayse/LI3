package GestVendas.Models.AuxModels;

public interface IMonthlyRep {

    IMonthlyRep addToMonth(int month, int val);

    int getMonth(int month);

    String toString();

    IMonthlyRep clone();
}
