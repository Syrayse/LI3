package GestVendas;

import GestVendas.Views.Input;

import java.io.IOException;
import java.io.Serializable;

public class GereVendasController implements InterfGereVendasController, Serializable {

    private InterfGereVendasModel model;
    private InterfGereVendasView view;

    public InterfGereVendasController set(InterfGereVendasModel it) {
        return null;
    }

    public InterfGereVendasController set(InterfGereVendasView it) {
        return null;
    }

    public void startController() {
        this.runMainMenu();
    }

    private void runMainMenu() {
        int i;
        boolean in = true;

        while (in) {
            view.clearScreen();
            view.mainMenu();
            i = view.lerInt("Insira a opçao que deseja: ");
            //view.imprime("Insira a opçao que deseja: ");
            //i = Input.lerInt();

            switch (i) {
                case 0:
                    in = false;
                    break;
                case 1:
                    this.carregaFicheiroBin();
                    break;
                case 2:
                    this.guardaFicheiroBin();
                    break;
                case 3:
                    break;
                case 4:
                    break;
                case 5:
                    this.consultasEstatMenu();
                    break;
                case 6:
                    this.consultasDynMenu();
                    break;
                default:
                    view.imprimeLinha("Opçao invalida!");
                    Input.lerString();
            }
        }

    }

    private void carregaFicheiroBin() {
        String modelBin = view.getDiretoria(1, "guardar");
        //view.imprimeLinha("Insira o nome do ficheiro do qual pretende carregar o modelo:");
        //String modelBin = Input.lerString();

        try {
            model = model.carregaEstado(modelBin);
            view.imprimeLinha("Informção carrega com sucesso!");
        } catch (Exception exc) {
            view.imprimeLinha(exc.getMessage());
        }
    }

    private void guardaFicheiroBin() {
        String modelBin = view.getDiretoria(1, "guardar");
        //view.imprime("Indique o nome do ficheiro onde pretende guardar o modelo atual:");
        //String modelBin = Input.lerString();

        try {
            model.guardaEstado(modelBin);
            view.imprimeLinha("Informação guardada com sucesso!");
        } catch (IOException ioe) {
            view.imprimeLinha(ioe.getMessage());
        }
    }

    private void carregaFicheiroTxt() {
        String tmp;
        try {
            tmp = view.getDiretoria(0, "clientes");
            //Carregar estrutura Clientes
            view.imprimeLinha("Ficheiro carregado com sucesso!");
        } catch (Exception ioe) {
            view.imprimeLinha(ioe.getMessage());
            return ;
        }
        try {
            tmp = view.getDiretoria(0, "produtos");
            //Carregar estrutura Produtos
            view.imprimeLinha("Ficheiro carregado com sucesso!");
        } catch (Exception ioe) {
            view.imprimeLinha(ioe.getMessage());
            return ;
        }
        try {
            tmp = view.getDiretoria(0, "vendas");
            //Carregar estrutura Vendas
            view.imprimeLinha("Ficheiro carregado com sucesso!");
        } catch (Exception ioe) {
            view.imprimeLinha(ioe.getMessage());
            return ;
        }
    }

    /**
     * Assumindo,
     * <p>
     * 1 - Informação geral sobre o último ficheiro de vendas lido.
     * 2 - Número total de compras por mês.
     * 3 - Faturação total por mês, para cada filial e valor total global.
     * 4 - Número de distintos clientes em cada mês, filial a filial.
     */
    private void consultasEstatMenu() {
        int i;
        boolean in = true;

        while (in) {
            view.clearScreen();
            view.estMenu();
            //view.mainMenu();
            i = view.lerInt("Insira a opçao que deseja: ");
            //view.imprime("Insira a opçao que deseja: ");
            //i = Input.lerInt();

            switch (i) {
                case 0:
                    in = false;
                    break;
                case 1:
                    break;
                case 2:
                    break;
                case 3:
                    break;
                case 4:
                    break;
                default:
                    view.imprimeLinha("Opçao invalida!");
                    Input.lerString();
            }
        }
    }

    private void consultasDynMenu() {
        int i;
        boolean in = true;

        while (in) {
            view.clearScreen();
            view.dynMenu();
            //view.mainMenu();
            i = view.lerInt("Insira a opçao que deseja: ");
            //view.imprime("Insira a opçao que deseja: ");
            //i = Input.lerInt();

            switch (i) {
                case 0:
                    in = false;
                    break;
                case 1:
                    break;
                case 2:
                    break;
                case 3:
                    break;
                case 4:
                    break;
                case 5:
                    break;
                case 6:
                    break;
                case 7:
                    break;
                case 8:
                    break;
                case 9:
                    break;
                case 10:
                    break;
                default:
                    view.imprimeLinha("Opçao invalida!");
                    Input.lerString();
            }
        }
    }

    private void useNavControl(NavControl<? extends Object> navigator) {
        int i;
        boolean in = true;

        while (in) {
            view.clearScreen();
            navigator.showPage();
            view.listOptions();
            i = view.lerInt("Insira a opçao que deseja: ");
            //view.imprime("Insira a opçao que deseja: ");
            //i = Input.lerInt();

            switch (i) {
                case 0:
                    in = false;
                    break;
                case 1:
                    navigator.proximaPagina();
                    break;
                case 2:
                    navigator.retrocePagina();
                    break;
                default:
                    view.imprimeLinha("Opçao invalida!");
                    Input.lerString();
            }
        }
    }
}
