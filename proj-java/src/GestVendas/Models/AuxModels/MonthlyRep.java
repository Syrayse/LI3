package GestVendas.Models.AuxModels;

import GestVendas.lib.Common;

import java.util.ArrayList;
import java.util.List;

public class MonthlyRep implements IMonthlyRep {

    private List<Integer> monthly;

    public MonthlyRep() {
        int meses = Common.MES_MAX;

        monthly = new ArrayList<>(meses);

        for (int i = 0; i < meses; i++) {
            monthly.add(i, 0);
        }
    }

    public MonthlyRep(MonthlyRep m) {
        int meses = Common.MES_MAX;

        monthly = new ArrayList<>(meses);

        for (int i = 0; i < meses; i++) {
            monthly.add(i, m.getMonth(i + 1));
        }
    }

    public IMonthlyRep addToMonth(int month, int val) {
        int curr = getMonth(month);

        monthly.add(month - 1, curr + val);

        return this;
    }

    public int getMonth(int month) {
        return monthly.get(month - 1);
    }

    public String toString() {
        StringBuilder sb = new StringBuilder();
        int meses = Common.MES_MAX;

        sb.append("MESES ->\t");

        for (int i = 0; i < meses; i++) {
            sb.append(String.format("|    %2d    |", i + 1));
        }

        sb.append("\n");

        for (int i = 0; i < meses; i++) {
            sb.append(String.format("   %8d   ", getMonth(i + 1)));
        }

        sb.append("\n");

        return sb.toString();
    }

    public IMonthlyRep clone() {
        return new MonthlyRep(this);
    }

}
