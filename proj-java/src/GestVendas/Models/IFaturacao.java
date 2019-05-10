package GestVendas.Models;

import java.util.Set;

public interface IFaturacao {

    int getNumVendas(int mes);

    Set<String> getCodigoProdutos();

}
