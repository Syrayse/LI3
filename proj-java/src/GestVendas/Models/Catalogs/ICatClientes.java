package GestVendas.Models.Catalogs;

import GestVendas.Models.BaseModels.ICliente;

import java.util.Set;

/**
 * Interface que define o contrato que qualquer catálogo de clientes deve cumprir.
 */
public interface ICatClientes {

    /**
     * Indica o número de clientes no sistema.
     *
     * @return Número de clientes no sistema.
     */
    int size();

    /**
     * Insere um dado cliente no catálogo de clientes.
     * @param c Novo cliente.
     * @return Catálogo de produtos com novo cliente.
     */
    ICatClientes insereCliente(ICliente c);

    /**
     * Verifica se um dado cliente existe no catálogo de clientes.
     * @param c Cliente que se pretende verificar.
     * @return Se o cliente está no catálogo ou não.
     */
    boolean existeCliente(ICliente c);

    /**
     * Verifica se um dadod cliente existe no catálogo de clientes por código.
     * @param clientCode Código que se pretende verificar.
     * @return Se o cliente está no catálogo ou não.
     */
    boolean existeCliente(String clientCode);

    /**
     * Calcula um conjunto com o código de todos os clientes presente no catálogo.
     * @return Conjunto calculado.
     */
    Set<String> getCodigoClientes();

}
