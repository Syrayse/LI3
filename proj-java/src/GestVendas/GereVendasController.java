package GestVendas;

import GestVendas.Exceptions.ClienteInexistenteException;
import GestVendas.Exceptions.FilialInvalidException;
import GestVendas.Exceptions.ProdutoInexistenteException;
import GestVendas.Models.AuxModels.IGlobalRep;
import GestVendas.Models.AuxModels.IMonthlyRep;
import GestVendas.Models.AuxModels.InterfInfoMensal;
import GestVendas.Views.Input;
import GestVendas.lib.Common;
import GestVendas.lib.Crono;
import GestVendas.lib.NavControl;
import GestVendas.lib.Par;

import java.io.IOException;
import java.io.Serializable;
import java.util.List;
import java.util.TreeSet;

public class GereVendasController implements InterfGereVendasController, Serializable {

    private static final String omissionFile = "gestVendas.dat";

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
        double tmp;

        if (modelBin.equals("") || modelBin.equals("\n"))
            modelBin = omissionFile;

        try {
            Crono.start();
            model = model.carregaEstado(modelBin);
            tmp = Crono.stop();
            view.imprimeLinha("Informação carregada com sucesso do ficheiro " + modelBin + "!");
            view.imprimeLinha("CPU Time: " + tmp);
        } catch (Exception exc) {
            view.imprimeLinha(exc.getMessage());
        }

        Input.lerString();
    }

    private void guardaFicheiroBin() {
        view.imprimeLinha("Indique o nome do ficheiro onde pretende guardar o modelo atual:");
        String modelBin = Input.lerString();
        double tmp;

        if (modelBin.equals("") || modelBin.equals("\n"))
            modelBin = omissionFile;

        try {
            Crono.start();
            model.guardaEstado(modelBin);
            tmp = Crono.stop();
            view.imprimeLinha("Informação guardada com sucesso  no ficheiro " + modelBin + " !");
            view.imprimeLinha("CPU Time: " + tmp);
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
        String tmp;
        int i, n;
        double it, v;
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
                    Crono.start();
                    tmp = model.ultimoFicheiroVendas();
                    it = Crono.stop();
                    view.imprimeLinha("Último ficheiro de vendas lido: " + tmp);
                    view.imprimeLinha("CPU Time: " + it);
                    Input.lerString();
                    break;
                case 2:
                    Crono.start();
                    n = model.getNumVendasErradas();
                    it = Crono.stop();
                    view.imprimeLinha("Número de vendas erradas: " + n);
                    view.imprimeLinha("CPU Time: " + it);
                    Input.lerString();
                    break;
                case 3:
                    Crono.start();
                    n = model.getNumProdutos();
                    it = Crono.stop();
                    view.imprimeLinha("Número de produtos: " + n);
                    view.imprimeLinha("CPU Time: " + it);
                    Input.lerString();
                    break;
                case 4:
                    Crono.start();
                    n = model.getNumProdutosComprados();
                    it = Crono.stop();
                    view.imprimeLinha("Número de produtos comprados: " + n);
                    view.imprimeLinha("CPU Time: " + it);
                    Input.lerString();
                    break;
                case 5:
                    Crono.start();
                    n = model.getNumProdutosNaoComprados();
                    it = Crono.stop();
                    view.imprimeLinha("Número de produtos não comprados: " + n);
                    view.imprimeLinha("CPU Time: " + it);
                    Input.lerString();
                    break;
                case 6:
                    Crono.start();
                    n = model.getNumClientes();
                    it = Crono.stop();
                    view.imprimeLinha("Número de clientes: " + n);
                    view.imprimeLinha("CPU Time: " + it);
                    Input.lerString();
                    break;
                case 7:
                    Crono.start();
                    n = model.getNumClientesCompradores();
                    it = Crono.stop();
                    view.imprimeLinha("Número de clientes que efetuaram compras:" + n);
                    view.imprimeLinha("CPU Time: " + it);
                    Input.lerString();
                    break;
                case 8:
                    Crono.start();
                    n = model.getNumClientesNaoCompradores();
                    it = Crono.stop();
                    view.imprimeLinha("Número de clientes que não efetuaram compras:" + n);
                    view.imprimeLinha("CPU Time: " + it);
                    Input.lerString();
                    break;
                case 9:
                    Crono.start();
                    n = model.getNumVendasZero();
                    it = Crono.stop();
                    view.imprimeLinha("Número de vendas a 0.0: " + n);
                    view.imprimeLinha("CPU Time: " + it);
                    Input.lerString();
                    break;
                case 10:
                    Crono.start();
                    v = model.getFaturacao();
                    it = Crono.stop();
                    view.imprimeLinha("Faturacao Total: " + v);
                    view.imprimeLinha("CPU Time: " + it);
                    Input.lerString();
                    break;
                case 11:
                    Crono.start();
                    IMonthlyRep r = model.getComprasPorMes();
                    it = Crono.stop();
                    view.imprime(r.toString());
                    view.imprimeLinha("CPU Time: " + it);
                    Input.lerString();
                    break;
                case 12:
                    Crono.start();
                    IGlobalRep rm = model.getFaturacaoPorMesFil();
                    it = Crono.stop();
                    view.imprime(rm.toString());
                    view.imprimeLinha("CPU Time: " + it);
                    Input.lerString();
                    break;
                case 13:
                    Crono.start();
                    List<IMonthlyRep> l = model.getNumDistintosClienteMonthFil();
                    it = Crono.stop();

                    for (int j = 0; i < l.size(); i++) {
                        view.imprimeLinha("FILIAL " + (j + 1));
                        view.imprime(l.get(j).toString());
                    }

                    view.imprimeLinha("CPU Time: " + it);
                    Input.lerString();
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
        double time;

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
                    Crono.start();
                    TreeSet<String> t1 = model.getProdutosNaoVendidos();
                    view.imprimeLinha("CPU time: " + Crono.stop());
                    Input.lerString();
                    this.useNavControl(new NavControl<>(
                            "Produtos Nunca Comprados",
                            t1,
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
                        Crono.start();
                        if (n == 0)
                            res = model.getVendasInfo(mes);
                        else
                            res = model.getVendasInfo(mes, n);
                        time = Crono.stop();
                        view.imprimeLinha(String.format(
                                "Número global de vendas = %d\nNúmero total de clientes distintos = %d",
                                res.getKey(), res.getValue()
                        ));
                        view.imprimeLinha("CPU Time: " + time);
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
                        Crono.start();
                        InterfInfoMensal iim = model.getInfoMensalCliente(tmp);
                        time = Crono.stop();
                        view.printHeader("Informação Mensal do Cliente " + tmp, "BLUE");
                        view.imprimeLinha(iim.toString());
                        view.printFooter();
                        view.imprimeLinha("CPU Time: " + time);
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
                        Crono.start();
                        InterfInfoMensal iim = model.getInfoMensalProd(tmp);
                        time = Crono.stop();
                        view.printHeader("Informação Mensal do Produto " + tmp, "BLUE");
                        view.imprimeLinha(iim.toString());
                        view.printFooter();
                        view.imprimeLinha("CPU Time: " + time);
                    } catch (ProdutoInexistenteException pie) {
                        view.imprimeLinha(pie.getMessage());
                    }
                    Input.lerString();
                    break;
                case 5:
                    view.imprimeLinha("Insira o cliente que pretende verificar:");
                    tmp = Input.lerString();
                    try {
                        Crono.start();
                        TreeSet<Par<String, Integer>> t2 = model.getTopProdutosMaisComprados(tmp);
                        view.imprimeLinha("CPU Time: " + Crono.stop());
                        Input.lerString();
                        this.useNavControl(new NavControl<>(
                                "Produtos Mais Comprados do Cliente " + tmp,
                                t2,
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

                    Crono.start();
                    List<Par<String, Integer>> t3 = model.getTopNProdutosMaisDistintos(n);
                    view.imprimeLinha("CPU Time: " + Crono.stop());
                    Input.lerString();

                    this.useNavControl(new NavControl<>(
                            "Top " + n + " Produtos Mais Vendidos (anual)",
                            t3,
                            s -> String.format("%s, clientes:%5d", s.getKey(), s.getValue()),
                            view
                    ));
                    break;
                case 7:
                    view.imprimeLinha("Indique a filial que pretende verificar: ");
                    n = Input.lerInt();

                    try {
                        Crono.start();
                        List<String> t4 = model.getTop3Compradores(n);
                        view.imprimeLinha("CPU Time: " + Crono.stop());
                        Input.lerString();

                        this.useNavControl(new NavControl<>(
                                "Top 3 Maiores Compradores na Filial " + n,
                                t4,
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

                    Crono.start();
                    TreeSet<Par<String, Integer>> t5 = model.getTopNVersatileClientes(n);
                    view.imprimeLinha("CPU Time: " + Crono.stop());
                    Input.lerString();

                    this.useNavControl(new NavControl<>(
                            "Top " + n + " Clientes de Produtos Distintos",
                            t5,
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
                        Crono.start();
                        List<Par<String, Double>> t6 = model.getMelhoresClientes(tmp, n);
                        view.imprimeLinha("CPU Time: " + Crono.stop());
                        Input.lerString();

                        this.useNavControl(new NavControl<>(
                                "Top " + n + " Clientes de " + tmp,
                                t6,
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
                        Crono.start();
                        IGlobalRep t7 = model.getFaturacaoTotal(tmp);
                        Crono.stop();
                        view.imprimeLinha("CPU Time: " + Crono.stop());
                        Input.lerString();

                        view.imprimeLinha(t7.toString());
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
        double tmp;

        try {
            Crono.start();
            model.createData(configs);
            tmp = Crono.stop();
            view.imprimeLinha("Ficheiro " + configs + " carregado com sucesso!");
            view.imprimeLinha("CPU Time: " + tmp);
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
        double tmp;


        view.imprimeLinha("Indique o numero de filiais desejado:");
        n_filiais = Input.lerInt();

        view.imprimeLinha("Indique o ficheiro de clientes:");
        clientes = Input.lerString();

        view.imprimeLinha("Indique o ficheiro de produtos:");
        produtos = Input.lerString();

        view.imprimeLinha("Indique o ficheiro de vendas:");
        vendas = Input.lerString();

        try {
            Crono.start();
            m.setClientes(clientes);
            view.imprimeLinha("CPU Time para Clientes: " + Crono.stop());

            Crono.start();
            m.setProdutos(produtos);
            view.imprimeLinha("CPU Time para Produtos: " + Crono.stop());

            Crono.start();
            m.setVendas(vendas, n_filiais);
            view.imprimeLinha("CPU Time para Vendas: " + Crono.stop());

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
