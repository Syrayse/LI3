package GestVendas.lib;

import java.util.Collection;
import java.util.function.Consumer;

public interface INavControl<E> {

    INavControl changeDict(Collection<E> collection);

    INavControl setPrintFunction(Consumer<E> print_f);

    INavControl proximaPagina();

    INavControl retrocePagina();

    void showPage();

}
