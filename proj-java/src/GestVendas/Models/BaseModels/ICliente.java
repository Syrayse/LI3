package GestVendas.Models.BaseModels;

/**
 * Interface que define o contrato que todos os clientes devem implementar.
 */
public interface ICliente {

    /**
     * Indica o código do cliente.
     *
     * @return Código do cliente.
     */
    String getCodigo();

    /**
     * Calcula a função de hash de um cliente.
     * @return O hash de um cliente.
     */
    int hashCode();

}
