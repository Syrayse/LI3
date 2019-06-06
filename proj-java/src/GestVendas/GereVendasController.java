package GestVendas;

import GestVendas.Exceptions.ClienteInexistenteException;
import GestVendas.Exceptions.FilialInvalidException;
import GestVendas.Exceptions.ProdutoInexistenteException;
import GestVendas.Models.AuxModels.InterfInfoMensal;
import GestVendas.Views.Input;
import GestVendas.lib.Common;
import GestVendas.lib.NavControl;
import GestVendas.lib.Par;

import java.io.IOException;
import java.io.Serializable;

public class GereVendasController implements InterfGereVendasController, Serializable {

    private InterfGereVendasModel model;
    private InterfGereVendasView view;

    public InterfGereVendasController set(InterfGereVendasModel it) {
        this.model = it;
        return this;
    }

    public InterfGereVendasController set(InterfGereVendasView it) {
        this.view = it;
        return this;
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
            view.imprimeLinha("Indique a opção que deseja:");
            i = Input.lerInt();

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
                    this.createDataMenu();
                    break;
                case 4:
                    this.loadFilesMenu();
                    break;
                case 5:
                    if (model.isValid())
                        this.consultasEstatMenu();
                    else {
                        view.imprimeLinha("Não pode aceder a esta funcionalidade pois ainda não carregou o modelo.");
                        Input.lerString();
                    }
                    break;
                case 6:
                    if (model.isValid())
                        this.consultasDynMenu();
                    else {
                        view.imprimeLinha("Não pode aceder a esta funcionalidade pois ainda não carregou o modelo.");
                        Input.lerString();
                    }
                    break;
                default:
                    view.imprimeLinha("Opçao invalida!");
                    Input.lerString();
            }
        }

    }

    private void carregaFicheiroBin() {
        view.imprimeLinha("Insira o nome do ficheiro do qual pretende carregar o modelo:");
        String modelBin = Input.lerString();

        try {
            model = model.carregaEstado(modelBin);
            view.imprimeLinha("Informação carrega com sucesso!");
        } catch (Exception exc) {
            view.imprimeLinha(exc.getMessage());
        }

        Input.lerString();
    }

    private void guardaFicheiroBin() {
        view.imprimeLinha("Indique o nome do ficheiro onde pretende guardar o modelo atual:");
        String modelBin = Input.lerString();

        try {
            model.guardaEstado(modelBin);
            view.imprimeLinha("Informação guardada com sucesso!");
        } catch (IOException ioe) {
            view.imprimeLinha(ioe.getMessage());
        }

        Input.lerString();
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
            view.imprimeLinha("Indique a opção que deseja:");
            i = Input.lerInt();

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
                case 11:
                    break;
                case 12:
                    break;
                case 13:
                    break;
                default:
                    view.imprimeLinha("Opçao invalida!");
                    Input.lerString();
            }
        }
    }

    private void consultasDynMenu() {
        int i, n, mes;
        boolean in = true;
        String tmp;

        while (in) {
            view.clearScreen();
            view.dynMenu();
            view.imprimeLinha("Indique a opção que deseja:");
            i = Input.lerInt();

            switch (i) {
                case 0:
                    in = false;
                    break;
                case 1:
                    this.useNavControl(new NavControl<>(
                            "Produtos Nunca Comprados",
                            model.getProdutosNaoVendidos(),
                            s -> s,
                            view
                    ));
                    break;
                case 2:
                    view.imprimeLinha("Insira o mês que pretende verificar:");
                    mes = Input.lerInt();
                    if (!Common.intervaloInclusivo(mes, 1, Common.MES_MAX)) {
                        view.imprimeLinha("Indicou um mês errado!");
                        Input.lerString();
                    }

                    view.imprimeLinha("Insira a filial que pretende verificar (0 para valores globais)");
                    n = Input.lerInt();
                    try {
                        Par<Integer, Integer> res;
                        if (n == 0)
                            res = model.getVendasInfo(mes);
                        else
                            res = model.getVendasInfo(mes, n);
                        view.imprimeLinha(String.format(
                                "Número global de vendas = %d\nNúmero total de clientes distintos = %d",
                                res.getKey(), res.getValue()
                        ));
                    } catch (Exception e) {
                        view.imprimeLinha(e.getMessage());
                    }
                    Input.lerString();
                    break;
                case 3:
                    view.clearScreen();
                    view.imprimeLinha("Insira o cliente que pretende verificar:");
                    tmp = Input.lerString();
                    try {
                        InterfInfoMensal iim = model.getInfoMensalCliente(tmp);
                        view.printHeader("Informação Mensal do Cliente " + tmp, "BLUE");
                        view.imprimeLinha(iim.toString());
                        view.printFooter();
                    } catch (ClienteInexistenteException cie) {
                        view.imprimeLinha(cie.getMessage());
                    }
                    Input.lerString();
                    break;
                case 4:
                    view.clearScreen();
                    view.imprimeLinha("Insira o produto que pretende verificar:");
                    tmp = Input.lerString();
                    try {
                        InterfInfoMensal iim = model.getInfoMensalProd(tmp);
                        view.printHeader("Informação Mensal do Produto " + tmp, "BLUE");
                        view.imprimeLinha(iim.toString());
                        view.printFooter();
                    } catch (ProdutoInexistenteException pie) {
                        view.imprimeLinha(pie.getMessage());
                    }
                    Input.lerString();
                    break;
                case 5:
                    view.imprimeLinha("Insira o cliente que pretende verificar:");
                    tmp = Input.lerString();
                    try {
                        this.useNavControl(new NavControl<>(
                                "Produtos Mais Comprados do Cliente " + tmp,
                                model.getTopProdutosMaisComprados(tmp),
                                p -> String.format("%s, unidades:%5d", p.getKey(), p.getValue()),
                                view
                        ));
                    } catch (ClienteInexistenteException cie) {
                        view.imprimeLinha(cie.getMessage());
                        Input.lerString();
                    }
                    break;
                case 6:
                    view.imprimeLinha("Insira o nũmero máximo de elementos que pretende verificar:");
                    n = Input.lerInt();
                    this.useNavControl(new NavControl<>(
                            "Top " + n + " Produtos Mais Vendidos (anual)",
                            model.getTopNProdutosMaisDistintos(n),
                            s -> String.format("%s, clientes:%5d", s.getKey(), s.getValue()),
                            view
                    ));
                    break;
                case 7:
                    view.imprimeLinha("Indique a filial que pretende verificar: ");
                    n = Input.lerInt();
                    try {
                        this.useNavControl(new NavControl<>(
                                "Top 3 Maiores Compradores na Filial " + n,
                                model.getTop3Compradores(n),
                                s -> s,
                                view
                        ));
                    } catch (FilialInvalidException fie) {
                        view.imprimeLinha(fie.getMessage());
                        Input.lerString();
                    }
                    break;
                case 8:
                    view.imprimeLinha("Insira o nũmero máximo de elementos que pretende verificar:");
                    n = Input.lerInt();
                    this.useNavControl(new NavControl<>(
                            "Top " + n + " Clientes de Produtos Distintos",
                            model.getTopNVersatileClientes(n),
                            p -> String.format("%s, distintos:%5d", p.getKey(), p.getValue()),
                            view
                    ));
                    break;
                case 9:
                    view.imprimeLinha("Insira o produto que pretende verificar:");
                    tmp = Input.lerString();
                    view.imprimeLinha("Insira o nũmero máximo de elementos:");
                    n = Input.lerInt();
                    try {
                        this.useNavControl(new NavControl<>(
                                "Top " + n + " Clientes de " + tmp,
                                model.getMelhoresClientes(tmp, n),
                                p -> p.getKey() + String.format(", gastou:%5.2f", p.getValue()),
                                view
                        ));
                    } catch (ProdutoInexistenteException ex) {
                        view.imprimeLinha(ex.getMessage());
                        Input.lerString();
                    }
                    break;
                case 10: // fATURACAO TOTAL COM CADA PRODUTOS
                    view.clearScreen();
                    view.imprimeLinha("Insira o produto que pretende verificar:");
                    tmp = Input.lerString();
                    try {
                        view.imprimeLinha(model.getFaturacaoTotal(tmp).toString());
                    } catch (ProdutoInexistenteException ex) {
                        view.imprimeLinha(ex.getMessage());
                    }
                    Input.lerString();
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
            i = 0;
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

    private void createDataMenu() {
        view.imprimeLinha("Indique o ficheiro de configurações que pretende carregar:");
        String configs = Input.lerString();

        try {
            model.createData(configs);
            view.imprimeLinha("Ficheiro " + configs + " carregado com sucesso!");
        } catch (Exception exc) {
            view.imprimeLinha(exc.getMessage());
            view.imprimeLinha("Ocorreu erro ao carregar ficheiro de configurações.");
        }

        Input.lerString();
    }

    private void loadFilesMenu() {
        view.clearScreen();
        InterfGereVendasModel m = new GereVendasModel();
        String clientes, produtos, vendas;
        int n_filiais;

        view.imprimeLinha("Indique o numero de filiais desejado:");
        n_filiais = Input.lerInt();

        view.imprimeLinha("Indique o ficheiro de clientes:");
        clientes = Input.lerString();

        view.imprimeLinha("Indique o ficheiro de produtos:");
        produtos = Input.lerString();

        view.imprimeLinha("Indique o ficheiro de vendas:");
        vendas = Input.lerString();

        try {
            m.setClientes(clientes);
            m.setProdutos(produtos);
            m.setVendas(vendas, n_filiais);
            view.imprimeLinha("Ficheiros carregados com sucesso!");
            view.imprimeLinha("Informação sobre os ficheiros carregados!:");

            // Por aqui cenas
        } catch (Exception exc) {
            view.imprimeLinha(exc.getMessage());
            view.imprimeLinha("Ocorreu erro ao carregar ficheiros manualmente.");
        }

        Input.lerString();
    }

}
