package GestVendas.Models.Catalogs;

import GestVendas.Models.BaseModels.IProduto;

import java.util.TreeSet;

/**
 * Interface que define o contrato que qualquer catálogo de produtos deve cumprir.
 */
public interface ICatProdutos {

    /**
     * Calcula o número de produtos no catálogo.
     *
     * @return Número de produtos no catálogo.
     */
    int size();

    /**
     * Insere um produto no catálogo de produtos.
     *
     * @param p Produto que se pretende inserir.
     * @return O catálogo de produto com um novo produto.
     */
    ICatProdutos insereProduto(IProduto p);

    /**
     * Verifica se um dado produto existe no catálogo de produtos.
     * @param p Produto que se pretende verificar que existe.
     * @return Se o produto existe ou não.
     */
    boolean existeProduto(IProduto p);

    /**
     * Verifica se um dado produto existe no catálogo de produto, segundo o seu código.
     * @param prodCode Código do produto que se pretende verificar que existe.
     * @return Se o produto existe ou não.
     */
    boolean existeProduto(String prodCode);

    /**
     * Calcula um TreeSet com o código de todos os produtos no catálogo de produtos,
     * ordenado por ordem alfabética.
     *
     * @return O conjunto com todos os códigos de produtos.
     */
    TreeSet<String> getCodigoProdutos();

}
