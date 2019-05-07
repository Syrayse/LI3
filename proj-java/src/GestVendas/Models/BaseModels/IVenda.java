package GestVendas.Models.BaseModels;

public interface IVenda {

    String getCodigoProduto();
    double getPreco();
    int getUnidades();
    String getCodigoPromo();
    String getCodigoCliente();
    int getMes();
    int getFilial();
    double getReceita();

}