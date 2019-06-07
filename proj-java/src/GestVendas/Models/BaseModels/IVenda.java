package GestVendas.Models.BaseModels;

/**
 * Interface que define o contrato que qualquer venda deve cumprir.
 */
public interface IVenda {

    /**
     * Indica o código do produto associado à venda.
     *
     * @return Código do produto associado à venda.
     */
    String getCodigoProduto();

    /**
     * Indica o preço ao qual foi vendido o produto.
     *
     * @return O preço ao qual foi vendido o produto.
     */
    double getPreco();

    /**
     * Indica o número de unidades transacionadas.
     * @return O número de unidades transacionadas.
     */
    int getUnidades();

    /**
     * Indica o código promocional com que foi efetuada a compra.
     * @return Código promocional com que foi efetuada a compra.
     */
    String getCodigoPromo();

    /**
     * Indica o código de cliente associado à venda.
     * @return Código de cliente associado à venda.
     */
    String getCodigoCliente();

    /**
     * Indica o mês em que foi efetuada uma certa venda.
     * @return Mês em que foi efetuada certa.
     */
    int getMes();

    /**
     * Indica a filial onde ocorre a venda.
     * @return A filial onde ocorre a venda.
     */
    int getFilial();

    /**
     * Indica a receita total associada a uma venda.
     * @return Indica a receita total associada a uma venda.
     */
    double getReceita();

}