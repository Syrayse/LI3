package GestVendas.lib;

import java.util.Collection;
import java.util.function.Function;

public interface INavControl<E> {

    INavControl changeDict(Collection<E> collection);

    INavControl setPrintFunction(Function<E, String> print_f);

    INavControl proximaPagina();

    INavControl retrocePagina();

    void showPage();

}
