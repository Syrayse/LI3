package GestVendas;

public interface InterfGereVendasView {

    void clearScreen();

    void mainMenu();

    void dynMenu();

    void estMenu();

    String getDiretoria(int i, String vendas);

    int lerInt(String s);

    void imprime(String txt);

    void imprimeLinha(String line);

    void printHeader(String title);

    void printHeader(String title, String color);

    void printFooter();

    void listOptions();
}