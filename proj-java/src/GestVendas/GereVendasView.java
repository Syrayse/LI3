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
        printHeader("Menu de Consultas Dinâmicas");
        imprimeLinha("1: Lista ordenada alfabeticamente com os códigos dos produtos que nunca foram comprados.");
        imprimeLinha("2: Número global de vendas realizadas e número total de clientes distintos num determinado mês");
        //Filial a filial ou total
        imprimeLinha("3: Número total de compras e produtos comprados e total gasto para um determinado cliente, mês a mês.");
        imprimeLinha("4: Número de vendas e clientes distintos e total faturado para um determinado produto, mês a mês.");
        imprimeLinha("5: Lista de produtos mais comprados para um determinado clientes.");
        imprimeLinha("6: Lista dos N produtos mais vendidos.");
        imprimeLinha("7: Top 3 compradores.");
        //Filial a filial ou total
        imprimeLinha("8: Lista dos N clientes que compraram mais produtos distintos.");
        imprimeLinha("9: Lista dos N clientes que mais compraram um determinado produto");
        imprimeLinha("10: Faturação para um determinado produto.");
        //Filial a filial e mês - Matriz
        imprimeLinha("0: Sair");
        printFooter();
    }

    public void estMenu() {
        printHeader("Menu de Consultas Estatisticas");
        imprimeLinha("1: Último ficheiro de vendas lido.");
        imprimeLinha("2: Número total de registos de venda errados.");
        imprimeLinha("3: Número total de produtos.");
        imprimeLinha("4: Número total de diferentes produtos comprados.");
        imprimeLinha("5: Número total de produtos não comprados.");
        imprimeLinha("6: Número total de clientes.");
        imprimeLinha("7: Número total de clientes que efetuaram compras.");
        imprimeLinha("8: Número total de clientes que não comprou nada.");
        imprimeLinha("9: Número total de compras de valor igual a 0.0 .");
        imprimeLinha("10: Faturação total.");
        imprimeLinha("11: Número total de compras por mês.");
        imprimeLinha("12: Faturação total por mês e filial e valor total global.");
        imprimeLinha("13: Número de distintos clientes que efetuaram compras em cada mês, filial a filial.");
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

    public void imprime(String text) {
        out.print(text);
    }

    public void imprimeLinha(String text) {
        out.println(text);
    }

    public void printHeader(String text) {
        printHeader(text, "RED");
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
