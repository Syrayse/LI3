package GestVendas.Models;

import GestVendas.Exceptions.ClienteInexistenteException;
import GestVendas.Exceptions.ProdutoInexistenteException;
import GestVendas.Models.AuxModels.InterfInfoMensal;
import GestVendas.lib.Par;

import java.util.List;
import java.util.TreeSet;

/**
 * Interface que define o contrato que uma classe associada a uma filial deve estabelecer.
 */
public interface IFilial {

    /**
     * Adiciona um registo de venda à filial.
     *
     * @param codCliente Código do cliente.
     * @param codProd    Código do produto.
     * @param mes        Mês em que ocorreu a venda.
     * @param quantidade Quantidade transaccionada.
     * @param receita    Receita total originada da venda.
     * @return A Filial com uma nova venda.
     */
    IFilial insereVenda(String codCliente, String codProd, int mes, int quantidade, double receita);

    /**
     * Calcula o número total de vendas na filial.
     *
     * @return O número total de vendas na filial.
     */
    int getNumVendas();

    /**
     * Calcula o número total de vendas na filial num dado mês.
     *
     * @param mes Mês que se pretende verificar.
     * @return O número total de vendas na filial num dado mês.
     */
    int getNumVendas(int mes);

    /**
     * Calcula o número total de clientes.
     *
     * @return O número total de clientes.
     */
    int getNumClientes();

    /**
     * Calcula o número total de clientes que efetuaram compras num dado mês.
     *
     * @param mes Mês que se pretende verificar.
     * @return O número total de clientes que efetuaram compras num dado mês.
     */
    int getNumClientes(int mes);

    /**
     * Calcula o número de clientes que compraram um certo produto, caso o produto não exista retorna 0.
     *
     * @param prodCode Código do produto que se pretende verificar.
     * @return Número de clientes que compraram um dado produto.
     */
    int getNumClientes(String prodCode);

    /**
     * Indica uma lista com o código dos top 3 clientes que mais dinheiro gastaram naquela filial.
     * @return Lista com o código dos top 3 clientes que mais dinheiro gastaram naquela filial.
     */
    List<Par<String, Double>> getTop3Compradores();

    /**
     * Calcula uma estrutura com a informação mensal associada a um cliente.
     * @param clientCode Código do cliente que se pretende verificar.
     * @return A estrutura calculada.
     * @throws ClienteInexistenteException Caso o cliente não exista.
     */
    InterfInfoMensal getInfoCliente(String clientCode) throws ClienteInexistenteException;

    /**
     * Calcula uma estrutura com a informação mensal associada a um produto.
     * @param prodCode Código do produto que se pretende verificar.
     * @return A estrutura calculada.
     * @throws ProdutoInexistenteException Caso o produto não exista.
     */
    InterfInfoMensal getInfoProduto(String prodCode) throws ProdutoInexistenteException;

    /**
     * Calcula um TreeSet de pares, que associam a cada produto a quantidade comprada por um dado cliente.
     * Ordenado por ordem decrescente da quantidade.
     * @param clientCode Código do cliente que se pretende verificar.
     * @return O TreeSet calculado.
     * @throws ClienteInexistenteException Caso o cliente não exista.
     */
    TreeSet<Par<String, Integer>> getClientesProductSum(String clientCode) throws ClienteInexistenteException;

    /**
     * Calcula uma lista de pares, que associam a cada cliente o número de produtos distintos que este comprou.
     * Ordenado por ordem decrescente do número distinto de produtos comprados.
     * @param N Tamanho máximo da lista.
     * @return O TreeSet Calculado.
     */
    List<Par<String, Integer>> getTopNVersatileClientes(int N);

    /**
     * Calcula uma lista de pares, que associam a cada cliente o valor gasto num dado produto.
     * Ordenado por ordem decrescente do montante gasto naquele produto.
     * @param prodCode Código do cliente que se pretrende verificar.
     * @param N Tamanha máximo da lista.
     * @return A lista calculada.
     * @throws ProdutoInexistenteException Caso o produto não exista.
     */
    List<Par<String, Double>> getMelhoresClientes(String prodCode, int N) throws ProdutoInexistenteException;
}
