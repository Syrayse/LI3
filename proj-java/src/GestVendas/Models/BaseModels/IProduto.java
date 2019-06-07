package GestVendas.Models.BaseModels;

/**
 * Interface que todos os produtos devem cumprir.
 */
public interface IProduto {

    /**
     * Indica o código de produto associado a um produto.
     *
     * @return Código de produto
     */
    String getCodigo();

    /**
     * Calcula a função de hash de um dado produto.
     * @return Calcula a função de hash.
     */
    int hashCode();

}
