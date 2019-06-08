package GestVendas;

import GestVendas.Exceptions.ClienteInexistenteException;
import GestVendas.Exceptions.FilialInvalidException;
import GestVendas.Exceptions.InvalidConfigException;
import GestVendas.Exceptions.ProdutoInexistenteException;
import GestVendas.Models.AuxModels.IGlobalRep;
import GestVendas.Models.AuxModels.IMonthlyRep;
import GestVendas.Models.AuxModels.InterfInfoMensal;
import GestVendas.Models.BaseModels.Cliente;
import GestVendas.Models.BaseModels.IVenda;
import GestVendas.Models.BaseModels.Produto;
import GestVendas.Models.BaseModels.Venda;
import GestVendas.Models.Catalogs.CatClientes;
import GestVendas.Models.Catalogs.CatProdutos;
import GestVendas.Models.Catalogs.ICatClientes;
import GestVendas.Models.Catalogs.ICatProdutos;
import GestVendas.Models.Faturacao;
import GestVendas.Models.Filial;
import GestVendas.Models.IFaturacao;
import GestVendas.Models.IFilial;
import GestVendas.lib.Common;
import GestVendas.lib.Par;

import java.io.*;
import java.nio.file.Files;
import java.nio.file.Paths;
import java.util.ArrayList;
import java.util.List;
import java.util.TreeSet;

public class GereVendasModel implements InterfGereVendasModel, Serializable {

    private String ultimoVendas;
    private int vendasErradas;
    private int vendasZero;

    private ICatClientes clientes;
    private ICatProdutos produtos;
    private IFaturacao faturacao;
    private IFilial global;
    private List<IFilial> filiais;

    public GereVendasModel() {
        ultimoVendas = "";
        vendasErradas = -1;
        vendasZero = -1;
        clientes = null;
        produtos = null;
        faturacao = null;
        global = null;
        filiais = null;
    }

    public boolean isValid() {
        return clientes != null;
    }

    public InterfGereVendasModel createData(String configs) throws IOException, InvalidConfigException {
        List<String> lines = Files.readAllLines(Paths.get(configs));
        String[] tokens;

        if (lines.size() != 4) {
            throw new InvalidConfigException("O ficheiro de configs possui mais argumentos do que o necessário!");
        }

        tokens = lines.get(0).split("[ :]+");

        if (tokens.length != 2 || !tokens[0].equals("N_FILIAIS")) {
            throw new InvalidConfigException("Os argumentos do ficheiro configs estão mal formatados!");
        }

        int n_filiais = Integer.parseInt(tokens[1]);

        for (int i = 1; i < 4; i++) {
            tokens = lines.get(i).split("[ :]+");

            if (tokens.length != 2)
                throw new InvalidConfigException("Os argumentos do ficheiro configs estão mal formatados!");

            switch (tokens[0]) {
                case "PROD_PATH":
                    this.setProdutos(tokens[1]);
                    break;
                case "CLNT_PATH":
                    this.setClientes(tokens[1]);
                    break;
                case "VENDAS_PATH":
                    this.setVendas(tokens[1], n_filiais);
                    break;
                default:
                    throw new InvalidConfigException("Os argumentos do ficheiros de configs possuem o identificador errado");
            }

        }

        return this;
    }

    public InterfGereVendasModel setProdutos(String file) throws IOException {
        List<String> lines = Files.readAllLines(Paths.get(file));

        produtos = new CatProdutos();

        for (String entry : lines) {

            if (validateProdutoCode(entry)) {
                produtos.insereProduto(new Produto(entry));
            }

        }

        return this;
    }

    public InterfGereVendasModel setClientes(String file) throws IOException {
        List<String> lines = Files.readAllLines(Paths.get(file));

        clientes = new CatClientes();

        for (String entry : lines) {

            if (validateClienteCode(entry)) {
                clientes.insereCliente(new Cliente(entry));
            }

        }

        return this;
    }

    public InterfGereVendasModel setVendas(String file, int n_filiais) throws IOException {
        List<String> lines = Files.readAllLines(Paths.get(file));
        String[] tokens;
        String codeProd, codeCliente;
        int quant, mes, fil;
        double rev;

        this.vendasZero = 0;
        this.vendasErradas = 0;

        faturacao = new Faturacao();
        global = new Filial();
        filiais = new ArrayList<>(n_filiais);

        for (int i = 0; i < n_filiais; i++)
            filiais.add(i, new Filial());

        // Processamento restante
        for (String entry : lines) {

            tokens = entry.split(" ");

            if (validateVendaCode(tokens)) {
                IVenda venda = new Venda(tokens);

                codeProd = venda.getCodigoProduto();
                codeCliente = venda.getCodigoCliente();
                quant = venda.getUnidades();
                rev = venda.getReceita();
                mes = venda.getMes();
                fil = venda.getFilial();

                global.insereVenda(codeCliente, codeProd, mes, quant, rev);
                faturacao.insereVenda(codeProd, mes, quant, rev, fil);
                filiais.get(venda.getFilial() - 1).insereVenda(codeCliente, codeProd, mes, quant, rev);
                if (venda.getPreco() == 0.0)
                    this.vendasZero++;

            } else {
                this.vendasErradas++;
            }

        }

        ultimoVendas = file;

        return this;
    }

    public InterfGereVendasModel carregaEstado(String fich) throws IOException, ClassNotFoundException {
        FileInputStream fileIn = new FileInputStream(fich);
        ObjectInputStream in = new ObjectInputStream(fileIn);
        InterfGereVendasModel tmp = (GereVendasModel) in.readObject();

        in.close();
        fileIn.close();

        return tmp;
    }

    public void guardaEstado(String fich) throws IOException {
        ObjectOutputStream out = new ObjectOutputStream(new FileOutputStream(fich));

        out.writeObject(this);

        out.flush();

        out.close();
    }

    // Interrogacoes Estatisticas

    // Q1
    public String ultimoFicheiroVendas() {
        return ultimoVendas;
    }

    // Q2
    public int getNumVendasErradas() {
        return vendasErradas;
    }

    // Q3
    public int getNumProdutos() {
        return produtos.size();
    }

    // Q4
    public int getNumProdutosComprados() {
        return faturacao.getNumProdutos();
    }

    // Q5
    public int getNumProdutosNaoComprados() {
        return this.getNumProdutos() - this.getNumProdutosComprados();
    }

    // Q6
    public int getNumClientes() {
        return clientes.size();
    }

    // Q7
    public int getNumClientesCompradores() {
        return global.getNumClientes();
    }

    // Q8
    public int getNumClientesNaoCompradores() {
        return this.getNumClientes() - this.getNumClientesCompradores();
    }

    // Q9
    public int getNumVendasZero() {
        return vendasZero;
    }

    // Q10
    public double getFaturacao() {
        return faturacao.getFaturacao();
    }

    // Q11
    public IMonthlyRep getComprasPorMes() {
        return global.getComprasMes();
    }

    // Q12
    public IGlobalRep getFaturacaoPorMesFil() {
        return faturacao.getOverall(filiais.size());
    }

    // Q13
    public List<IMonthlyRep> getNumDistintosClienteMonthFil() {
        List<IMonthlyRep> r = new ArrayList<>(filiais.size());

        for (int i = 0; i < filiais.size(); i++)
            r.add(i, filiais.get(i).getMonthRepDintis());

        return r;
    }

    // INTERROGACOES Dinamicas

    // Q1
    public TreeSet<String> getProdutosNaoVendidos() {
        TreeSet<String> r = produtos.getCodigoProdutos();

        r.removeAll(faturacao.getCodigoProdutos());

        return r;
    }

    // Q2
    public Par<Integer,Integer> getVendasInfo(int mes) {
        return new Par<>(global.getNumVendas(mes), global.getNumClientes(mes));
    }

    public Par<Integer, Integer> getVendasInfo(int mes, int filial) throws FilialInvalidException {
        safeGuardFilial(filial);
        IFilial f = filiais.get(filial - 1);

        return new Par<>(f.getNumVendas(mes), f.getNumClientes(mes));
    }

    // Q3
    public InterfInfoMensal getInfoMensalCliente(String clientCode) throws ClienteInexistenteException {
        return global.getInfoCliente(clientCode);
    }

    // Q4
    public InterfInfoMensal getInfoMensalProd(String prodCode) throws ProdutoInexistenteException {
        return global.getInfoProduto(prodCode);
    }

    // Q5
    // Falta definir comparador
    public TreeSet<Par<String, Integer>> getTopProdutosMaisComprados(String clientCode) throws ClienteInexistenteException {
        return global.getClientesProductSum(clientCode);
    }

    // Q6
    public List<Par<String, Integer>> getTopNProdutosMaisDistintos(int N) {
        List<String> mais_vendidos = faturacao.getNMaisVendidos(N);

        List<Par<String, Integer>> result = new ArrayList<>();

        mais_vendidos.forEach(s -> result.add(new Par<>(s, global.getNumClientes(s))));

        return result;
    }

    // Q7
    public List<Par<String, Double>> getTop3Compradores(int filial) throws FilialInvalidException {
        safeGuardFilial(filial);
        return filiais.get(filial - 1).getTop3Compradores();
    }

    // Q8
    public List<Par<String, Integer>> getTopNVersatileClientes(int N) {
        return global.getTopNVersatileClientes(N);
    }

    // Q9
    public List<Par<String, Double>> getMelhoresClientes(String prodCode, int N) throws ProdutoInexistenteException {
        return global.getMelhoresClientes(prodCode, N);
    }

    // Q10
    public IGlobalRep getFaturacaoTotal(String prodCode) throws ProdutoInexistenteException {
        return faturacao.getInfo(prodCode, filiais.size());
    }

    public int getNFiliais() {
        return filiais.size();
    }

    private void safeGuardFilial(int filial) throws FilialInvalidException {
        if (!Common.intervaloInclusivo(filial, 1, filiais.size()))
            throw new FilialInvalidException("A filial " + filial + " não se encontra no sistema!");
    }

    private boolean validateProdutoCode(String prodCode) {
        return prodCode.length() == 6 &&
                Common.intervaloInclusivo(prodCode.charAt(0), 'A', 'Z') &&
                Common.intervaloInclusivo(prodCode.charAt(1), 'A', 'Z') &&
                Common.intervaloInclusivo(Integer.parseInt(prodCode.substring(2)), 1000, 9999);
    }

    private boolean validateClienteCode(String clienteCode) {
        return clienteCode.length() == 5 &&
                Common.intervaloInclusivo(clienteCode.charAt(0), 'A', 'Z') &&
                Common.intervaloInclusivo(Integer.parseInt(clienteCode.substring(1)), 1000, 5000);
    }

    private boolean validateVendaCode(String[] vendaTokens) {
        return vendaTokens.length == 7 &&
                produtos.existeProduto(vendaTokens[0]) &&
                Common.intervaloInclusivo(Double.parseDouble(vendaTokens[1]), 0.0, 999.99) &&
                Common.intervaloInclusivo(Integer.parseInt(vendaTokens[2]), 1, 200) &&
                (vendaTokens[3].equals("N") || vendaTokens[3].equals("P")) &&
                clientes.existeCliente(vendaTokens[4]) &&
                Common.intervaloInclusivo(Integer.parseInt(vendaTokens[5]), 1, Common.MES_MAX) &&
                Common.intervaloInclusivo(Integer.parseInt(vendaTokens[6]), 1, getNFiliais());
    }
}
