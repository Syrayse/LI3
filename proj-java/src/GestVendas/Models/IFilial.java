package GestVendas.Models;

import java.util.Set;

public interface IFilial {

    int getNumVendas();

    int getNumVendas(int mes);

    int getNumClientes(int mes);

    Set<String> getClientes(int mes);

}
