public interface InterfGereVendasModel {

    InterfGereVendasModel setCatProdutos(String file);
    InterfGereVendasModel setCatClientes(String file);
    InterfGereVendasModel setFaturacaoFilial(String file);
    
    int getNFiliais();
    InterfGereVendasModel setNFiliais(int nFiliais);

}