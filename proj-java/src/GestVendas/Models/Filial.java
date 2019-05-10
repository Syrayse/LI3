package GestVendas.Models;

import java.io.Serializable;
import java.util.Set;

public class Filial implements IFilial, Serializable {

    public int getNumVendas() {
        return 0;
    }

    public int getNumVendas(int mes) {
        return 0;
    }

    public int getNumClientes(int mes) {
        return 0;
    }

    public Set<String> getClientes(int mes) {
        return null;
    }
}
