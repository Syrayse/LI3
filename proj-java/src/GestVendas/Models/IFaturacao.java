package GestVendas.Models;

import GestVendas.Exceptions.ProdutoInexistenteException;
import GestVendas.Models.AuxModels.IGlobalRep;

import java.util.List;
import java.util.Set;

/**
 * Interface que define o contrato que qualquer estrutura que implemente a faturação deve cumprir.
 */
public interface IFaturacao {

    IFaturacao insereVenda(String codProd, int mes, int quantidade, double receita, int fil);

    /**
     * Calcula o número de vendas num dado mês.
     *
     * @param mes Mès que se pretende verificar.
     * @return Número de vendas num dado mês.
     */
    int getNumVendas(int mes);

    /**
     * Calcula o número de produtos distintos que deram entrada na faturação.
     *
     * @return Número de produtos comprados.
     */
    int getNumProdutos();

    /**
     * Calcula um conjunto com o código de todos os produtos que foram comprados.
     * @return Conjunto com o código de todos os produtos que foram comprados.
     */
    Set<String> getCodigoProdutos();

    /**
     * Permite obter, o valor gasto num dado produto, por mês, por filial e em valores globais.
     *
     * @param prodCode  Código que se pretende verificar.
     * @param n_filiais Número de filais a considerar.
     * @return Um estrutura que armazena os valores por mês, filial e global.
     * @throws ProdutoInexistenteException Caso o produto não exista.
     */
    IGlobalRep getInfo(String prodCode, int n_filiais) throws ProdutoInexistenteException;

    /**
     * Calcula uma lista com o códigos dos N produtos mais vendidos em todo o ano. Ordenado por
     * ordem descrescente da quantidade em que foram comprados.
     * @param N Tamanho máximo da lista.
     * @return A lista calculada.
     */
    List<String> getNMaisVendidos(int N);

    /**
     * Calcula a faturação total regista.
     *
     * @return A faturação total.
     */
    double getFaturacao();

    /**
     * Calcula uma estrutura com a estrutura de faturacao geral do sistema, por filial e total.
     *
     * @param n_filiais Filiais a considerar.
     * @return Estrutura calculada.
     */
    IGlobalRep getOverall(int n_filiais);
}
