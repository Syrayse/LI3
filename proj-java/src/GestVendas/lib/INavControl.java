package GestVendas.lib;

import java.util.Collection;
import java.util.function.Function;

/**
 * Interface que define todos os metódos que classes que permitam tranvessar itens devem implementar.
 *
 * @param <E> Tipo de dados utilizado.
 */
public interface INavControl<E> {

    /**
     * Alterado o dicionário atual utilizado pela estrutura.
     * @param collection Novo dicionário a ser utilizado.
     * @return A estrutura alterada.
     */
    INavControl changeDict(Collection<E> collection);

    /**
     * Modifica a função de impressão utilizada.
     * @param print_f Nova função de impressão.
     * @return A estrutura alterada.
     */
    INavControl setPrintFunction(Function<E, String> print_f);

    /**
     * Pede a estrutura para passar para a página seguinte.
     * @return A estrutura alterada.
     */
    INavControl proximaPagina();

    /**
     * Pede a estrutura para retroceder de página.
     * @return A estrutura alterada.
     */
    INavControl retrocePagina();

    /**
     * Imprime no ecra a página atual.
     */
    void showPage();

}
