package GestVendas;

public interface InterfGereVendasView {

    void clearScreen();

    void mainMenu();

    void imprime(String txt);

    void imprimeLinha(String line);

    void printHeader(String title);

    void printHeader(String title, String color);

    void printFooter();

    void listOptions();
}