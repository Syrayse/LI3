package GestVendas;

/**
 * Interface que indica os metódos que uma classe que seja o utilizada
 * como view deve implementar de forma a permitir o correto funcionamento
 * da visualização.
 */
public interface InterfGereVendasView {

    /**
     * Metódo que permite "limpar" o ecra atual.
     */
    void clearScreen();

    /**
     * Imprime no ecra o menu principal.
     */
    void mainMenu();

    /**
     * Imprime no ecra o menu associado às queries dinàmicas.
     */
    void dynMenu();

    /**
     * Imprime no ecra o menu associado às queries estatisticas.
     */
    void estMenu();

    /**
     * Imprime no ecra a string passada como argumento.
     *
     * @param txt String que se pretende imprimir.
     */
    void imprime(String txt);

    /**
     * Imprime no ecra uma linha com a string passada como argumento.
     *
     * @param line String que se pretende imprimir.
     */
    void imprimeLinha(String line);

    /**
     * Imprime um header predefinido, com o titulo passado como argumento.
     *
     * @param title Titulo do header.
     */
    void printHeader(String title);

    /**
     * Imprime um header predefinido com o titulo passado como argumento e a cor indicada.
     *
     * @param title String que se pretende imprimir.
     * @param color Cor com a qual se pretende imprimir.
     */
    void printHeader(String title, String color);

    /**
     * Imprime um footer caracteristico.
     */
    void printFooter();

    /**
     * Imprime um menu com as opções utilizadas para navegar em collections.
     */
    void listOptions();
}