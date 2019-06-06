package GestVendas.lib;

import GestVendas.InterfGereVendasView;

import java.util.ArrayList;
import java.util.Collection;
import java.util.List;
import java.util.function.Function;

public class NavControl<E> implements INavControl<E> {

    private static final int N_COLS = 4;
    private static final int N_LINS = 5;
    private static final int N_PER_PAGE = N_COLS * N_LINS;

    private List<E> dict;
    private Function<E, String> print_function;
    private String title;
    private InterfGereVendasView view;
    private int init;
    private int end;
    private int size;
    private int page;
    private int maxPage;

    public NavControl(Collection<E> list, Function<E, String> print_function, InterfGereVendasView view) {
        title = "Listagem";
        dict = new ArrayList<>(list);
        size = list.size();
        page = size == 0 ? 0 : 1;
        init = 0;
        end = NavControl.N_PER_PAGE;
        maxPage = (int) Math.ceil((double) size / NavControl.N_PER_PAGE);
        this.setPrintFunction(print_function);
        this.view = view;
    }

    public NavControl(String title, Collection<E> list, Function<E, String> print_function, InterfGereVendasView view) {
        this(list, print_function, view);
        this.title = title;
    }

    public NavControl changeDict(Collection<E> list) {
        if (list == null)
            return null;

        dict = new ArrayList<>(list);
        size = list.size();
        page = size == 0 ? 0 : 1;
        init = 0;
        end = NavControl.N_PER_PAGE;
        maxPage = (int) Math.ceil((double) size / NavControl.N_PER_PAGE);
        return this;
    }

    public NavControl setPrintFunction(Function<E, String> print_function) {
        this.print_function = print_function;
        return this;
    }

    public NavControl proximaPagina() {
        if (dict == null)
            return null;
        int perPage = NavControl.N_PER_PAGE;

        if (end > size) {
            page = 1;

            init = 0;

            end = perPage;
        } else {
            page++;

            init = end;

            end += perPage;
        }

        return this;
    }

    public NavControl retrocePagina() {
        if (dict == null)
            return null;

        int perPage = NavControl.N_PER_PAGE;

        if (init < perPage) {
            page = (size / perPage) + 1;

            end = page * perPage;

            init = end - perPage;
        } else {
            page--;

            end = init;

            init -= perPage;
        }

        return this;
    }

    public void showPage() {
        if (print_function == null || dict == null)
            return;

        StringBuilder content = new StringBuilder("");
        String line;

        view.printHeader(title, "BLUE");

        for (int i = init; i < end && i < size; i++) {

            for (int j = 0; j < N_COLS && (j * N_LINS + i) < size; j++) {
                line = String.format("%5d: %s\t", j + 1, print_function.apply(dict.get(j)));
                content.append(line);
            }

            content.append("\n");
        }

        view.imprimeLinha(content.toString());

        this.showFooter();
    }

    private void showFooter() {
        view.printFooter();
        view.imprimeLinha("\tResultados de " + (size == 0 ? 0 : init + 1) + " ate " + Math.min(end, size) + " de um total de " + size + "\tPagina " + page + " de " + maxPage);
        view.printFooter();
    }

}
