package GestVendas;

import GestVendas.Views.Input;

import java.io.Serializable;
import java.util.HashMap;

import static java.lang.System.out;

public class GereVendasView implements InterfGereVendasView, Serializable {

    private static final String BLACK = "\033[0;30m";   // BLACK
    private static final String RED = "\033[0;31m";     // RED
    private static final String GREEN = "\033[0;32m";   // GREEN
    private static final String YELLOW = "\033[0;33m";  // YELLOW
    private static final String BLUE = "\033[0;34m";    // BLUE
    private static final String PURPLE = "\033[0;35m";  // PURPLE
    private static final String CYAN = "\033[0;36m";    // CYAN
    private static final String WHITE = "\033[0;37m";   // WHITE
    // Base separator
    private static final String SEPARATOR = "-";
    // Separator length
    private static final int LEN_SEP = 80;
    // Reset color
    private static final String RESET = "\033[0m";

    private HashMap<String, String> cor;


    public GereVendasView() {
        cor = this.coresBase();
    }

    public void clearScreen() {
        out.print("\033[H\033[2J");
        out.flush();
    }

    public void mainMenu() {
        printHeader("Menu Principal");
        imprimeLinha("1: Carrega de ficheiro binário.");
        imprimeLinha("2: Guarda em ficheiro binário.");
        imprimeLinha("3: Carregar ficheiro de configuração(configs.txt).");
        imprimeLinha("4: Carregar ficheiros manualmente.");
        imprimeLinha("5: Consultas estatisticas.");
        imprimeLinha("6: Consultas dinâmicas.");
        imprimeLinha("0: Sair");
        printFooter();
    }

    public void dynMenu() {
        printHeader("Menu de consultas dinâmicas");
        imprimeLinha(" 01. Lista ordenada alfabeticamente com os códigos dos produtos que nunca foram comprados.");  
        imprimeLinha(" 02. Número global de vendas realizadas e número total de clientes distintos num determinado mês");
        //Filial a filial ou total
        imprimeLinha(" 03. Número total de compras e produtos comprados e total gasto para um determinado cliente, mês a mês.");
        imprimeLinha(" 04. Número de vendas e clientes distintos e total faturado para um determinado produto, mês a mês.");
        imprimeLinha(" 05. Lista de produtos mais comprados para um determinado clientes.");
        imprimeLinha(" 06. Lista dos N produtos mais vendidos.");
        imprimeLinha(" 07. Top 3 compradores.");
        //Filial a filial ou total
        imprimeLinha(" 08. Lista dos N clientes que compraram mais produtos distintos.");
        imprimeLinha(" 09. Lista dos N clientes que mais compraram um determinado produto");
        imprimeLinha(" 10. Faturação para um determinado produto.");
        //Filial a filial e mês - Matriz
        imprimeLinha("0: Sair");
        printFooter();
    }

    public void estMenu() {
        printHeader("Menu de consultas estatisticas");
        imprimeLinha("1: Informação geral do ficheiro de vendas.");
        imprimeLinha("2: Número total de compras por mês.");
        imprimeLinha("3: Faturação total por mês, para cada filial e valor total global.");
        imprimeLinha("4: Número de distintos clientes em cada mês, filial a filial.");
        imprimeLinha("0: Sair");
        printFooter();
    }

    public String getDiretoria(int i, String tipo) {
        if (i == 0) {
            this.imprimeLinha("Insira a diretoria do ficheiro de " + tipo + ".");
            return Input.lerString();
        }
        if (i == 1) {
            this.imprimeLinha("Indique o nome do ficheiro onde pretende" + tipo + "o modelo atual:");
            return Input.lerString();
        }
        return null;
    }

    public int lerInt(String s){
        this.imprime(s);
        return Input.lerInt();
    }

    public void imprime(String text) {
        out.print(text);
    }

    public void imprimeLinha(String text) {
        out.println(text);
    }

    public void printHeader(String text) {
        printHeader(text, RED);
    }

    public void printHeader(String text, String color) {
        String reset = RESET;

        if ((color = cor.get(color)) == null) {
            color = "";
            reset = "";
        }

        int i, len1 = (LEN_SEP - text.length()) / 2;
        int len2 = LEN_SEP - len1 - text.length();
        StringBuilder sb = new StringBuilder();

        sb.append(repeat(SEPARATOR, len1 >= 0 ? len1 : 0));
        sb.append(color).append(text).append(RESET);
        sb.append(repeat(SEPARATOR, len2 >= 0 ? len2 : 0));

        imprimeLinha(sb.toString());

    }

    public void printFooter() {
        imprimeLinha(repeat(SEPARATOR, LEN_SEP));
    }

    public void listOptions() {
        imprimeLinha("1: Proxima pagina");
        imprimeLinha("2: Retroceder pagina");
        imprimeLinha("0: Cancelar");
        printFooter();
    }

    private HashMap<String, String> coresBase() {
        HashMap<String, String> cores = new HashMap<>();
        cores.put("BLACK", BLACK);
        cores.put("RED", RED);
        cores.put("GREEN", GREEN);
        cores.put("YELLOW", YELLOW);
        cores.put("BLUE", BLUE);
        cores.put("PURPLE", PURPLE);
        cores.put("CYAN", CYAN);
        cores.put("WHITE", WHITE);
        return cores;
    }

    private String repeat(String str, int count) {
        StringBuilder sb = new StringBuilder();

        for (int i = 0; i < count; i++) {
            sb.append(str);
        }

        return sb.toString();
    }
}
