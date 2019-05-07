package GestVendas;

public interface InterfGereVendasModel {

    InterfGereVendasModel setCatProdutos(String file);
    InterfGereVendasModel setCatClientes(String file);
    InterfGereVendasModel setFaturacaoFilial(String file);
    
    // Q1
    TreeSet<String> getProdutosNaoVendidos();

    // Q2
    Pair<Integer,Integer> getVendasInfo(int mes);
    Pair<Integer,Integer> getVendasInfo(int mes, int filial);

    // Q3
    InfoMensal getInfoMensalCliente(String clientCode);

    // Q4
    InfoMensal getInfoMensalProd(String prodCode);

    // Q5
    TreeSet<Pair<String,Integer>> getTopProdutosMaisComprados(String clientCode);

    // Q6
    TreeSet<Pair<IProduto,Integer>> getTopNProdutosMaisVendidos(int N);

    // Q7
    TreeSet<ICliente> getTop3Compradores();

    // Q8
    TreeSet<Pair<ICliente,Integer>> getTopNVersatileClientes(int N);

    // Q9
    TreeSet<Pair<ICliente,Double>> getMelhoresClientes(String prodCode);

    // Q10
    StatInfo getFaturacaoTotal(String prodCode);


    int getNFiliais();
    InterfGereVendasModel setNFiliais(int nFiliais);

}