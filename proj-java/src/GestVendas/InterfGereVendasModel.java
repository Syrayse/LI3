package GestVendas;

import GestVendas.Exceptions.ClienteInexistenteException;
import GestVendas.Exceptions.FilialInvalidException;
import GestVendas.Exceptions.InvalidConfigException;
import GestVendas.Exceptions.ProdutoInexistenteException;
import GestVendas.Models.AuxModels.IGlobalRep;
import GestVendas.Models.AuxModels.IMonthlyRep;
import GestVendas.Models.AuxModels.InterfInfoMensal;
import GestVendas.lib.Par;

import java.io.IOException;
import java.util.List;
import java.util.TreeSet;

/**
 * Interface que define o contrato que instância da classe modelo deve cumprir.
 */
public interface InterfGereVendasModel {

    /**
     * Verificar se o modelo atual é válido, i.e. se os seus valores internos não são inválidos.
     *
     * @return A validade do modelo atual.
     */
    boolean isValid();

    /**
     * Permite popular o modelo com um conjunto de ficheiros e informação presente num ficheiro de configurações.
     *
     * @param configs Ficheiro de configurações desejado.
     * @return O modelo populado.
     * @throws IOException            Caso algum erro ao ler o ficheiro ocorra.
     * @throws InvalidConfigException Caso o ficheiro esteja mal formatado.
     */
    InterfGereVendasModel createData(String configs) throws IOException, InvalidConfigException;

    /**
     * Permite popular o conjunto de produtos disponiveis com o ficheiro passado como argumento.
     *
     * @param file Ficheiro de produtos pretendido.
     * @return O modelo com produtos populados.
     * @throws IOException Caso ocorra um erro ao ler o ficheiro.
     */
    InterfGereVendasModel setProdutos(String file) throws IOException;

    /**
     * Permite popular o conjunto de clientes disponiveis com o ficheiro passado como argumento.
     *
     * @param file Ficheiro de clientes pretendido.
     *
     * @return O modelo com clientes populados.
     *
     * @throws IOException Caso ocorra um erro ao ler o ficheiro.
     */
    InterfGereVendasModel setClientes(String file) throws IOException;

    /**
     * Permite popular o modelo atual com novas vendas, a partir do ficheiro passado como argumento.
     *
     * @param file Ficheiro de vendas.
     * @param n_filiais Número de filiais que o modelo deve contemplar.
     * @return O modelo populado.
     * @throws IOException Caso ocorra um erro ao ler o ficheiro.
     */
    InterfGereVendasModel setVendas(String file, int n_filiais) throws IOException;

    /**
     * Permite carregar um model gravado no formato binário utilizando ObjectInputStreams.
     *
     * @param fich Ficheiro binário do qual se pretende carregar o modelo.
     * @return O modelo carregado.
     * @throws IOException Caso ocorra um erro ao ler o ficheiro.
     * @throws ClassNotFoundException Caso seja impossivel associar a classe armazenada, a uma classe existente.
     */
    InterfGereVendasModel carregaEstado(String fich) throws IOException, ClassNotFoundException;

    /**
     * Guarda o modelo atual em formato binário.
     *
     * @param fich Nome do ficheiro onde se pretende guardar a informação.
     * @throws IOException Caso ocorra um erro ao guardar o estado.
     */
    void guardaEstado(String fich) throws IOException;

    /**
     * Indica o último ficheiro de vendas lido.
     * @return O último ficheiro de vendas lido, ou "" caso nunca tenha sido lido um ficheiro.
     */
    String ultimoFicheiroVendas();

    /**
     * Indica o número de vendas que deram entrada no modelo, sendo inválidas.
     * @return O número de vendas inválidas.
     */
    int getNumVendasErradas();

    /**
     * Indica o número de produtos existentes atualmente no modelo.
     * @return Número de produtos atual.
     */
    int getNumProdutos();

    /**
     * Indica o número de produtos distintos que foram comprados.
     * @return O número de produtos distintos que foram comprados.
     */
    int getNumProdutosComprados();

    /**
     * Indica o número de produtos que nunca foram comprados.
     * @return O número de produtos que nunca foram comprados.
     */
    int getNumProdutosNaoComprados();

    /**
     * Indica o número de clientes atuais.
     * @return O número de clientes atual.
     */
    int getNumClientes();

    /**
     * Indica o número que clientes que efetuaram compras.
     * @return O número de clientes que efetuaram compras.
     */
    int getNumClientesCompradores();

    /**
     * Indica o número de clientes que não efetuaram compras.
     * @return O número de clientes que não efetuaram compras.
     */
    int getNumClientesNaoCompradores();

    /**
     * Indica o número de vendas com o preço de 0.0.
     * @return O número de vendas com o preço de 0.0.
     */
    int getNumVendasZero();

    /**
     * Indica a faturação total registada até a data.
     * @return A faturação total.
     */
    double getFaturacao();

    /**
     * Permite obter uma estrutura capaz de indicar o número de compras que foram
     * efetuadas no sistema num dado mês.
     * @return Estrutura que armazena o número de compras por mês.
     */
    IMonthlyRep getComprasPorMes();

    /**
     * Permite obter uma estrutura capaz de indicar o faturação efetuada num dado mês
     * numa dada filial, ou em global.
     * @return Estrutura que armazenar faturação por mês, filial e global.
     */
    IGlobalRep getFaturacaoPorMesFil();

    /**
     * Permite obter uma lista com povoada com estruturas capaz de armazenar
     * o número de clientes distintos que efetuaram compras num dado mês.
     * Visto se tratar de uma lista, obtêm-se então a capacidade de obter o número de
     * clientes distintos que efetuaram compras num dado mes numa dada filial.
     *
     * @return Uma lista (tão grande como o número de filiais) que permite obter valores mensais.
     */
    List<IMonthlyRep> getNumDistintosClienteMonthFil();

    /**
     * Calcula o conjunto de produtos que nunca foram comprados, ordenado por ordem alfabética.
     *
     * @return O conjunto de produtos que nunca foram comprados, ordenado por ordem alfabética.
     */
    TreeSet<String> getProdutosNaoVendidos();

    /**
     * Calcula um par de inteiros que indica o número de vendas e o número total de clientes, respectivamente.
     *
     * @param mes Mês que se pretende verificar.
     * @return Par de inteiros com valores referentes ao estado global do modelo.
     */
    Par<Integer, Integer> getVendasInfo(int mes);

    /**
     * Calcula um par de inteiros que indica o número de vendas e o número total de clientes, respectivamente.
     *
     * @param mes    Mês que se pretende verificar.
     * @param filial Filial que se pretende verificar.
     * @return Par de inteiros com valores referentes ao estado de uma filial do modelo.
     * @throws FilialInvalidException Caso a filial indica não exista.
     */
    Par<Integer, Integer> getVendasInfo(int mes, int filial) throws FilialInvalidException;

    /**
     * Calcula uma estrutura capaz de armazenar, por mês, o número de compras, produtos distintos
     * e gasto total associado a um cliente.
     *
     * @param clientCode Código do cliente que se pretende verificar.
     * @return A estrutura seccionada por mês.
     * @throws ClienteInexistenteException Caso o cliente que se pretende verificar não exista.
     */
    InterfInfoMensal getInfoMensalCliente(String clientCode) throws ClienteInexistenteException;

    /**
     * Calcula uma estrutura capaz de armazenar, por mês, o número de compras, clientes distintos
     * e gasto total associado a um produto.
     * @param prodCode Código do produto que se pretende verificar.
     *
     * @return A estrutura seccionada por mês.
     * @throws ProdutoInexistenteException Caso o produto que se pretende verificar não exista.
     */
    InterfInfoMensal getInfoMensalProd(String prodCode) throws ProdutoInexistenteException;

    /**
     * Calcula um TreeSet de pares, que associa a cada produto quantas unidades um dado cliente
     * comprou, daquele produto. Por ordem decrescente do número de unidades compradas.
     *
     * @param clientCode Cliente que se pretende verificar.
     * @return O TreeSet com produtos e respetivas quantidades.
     * @throws ClienteInexistenteException Caso o cliente que se pretende verificar não exista.
     */
    TreeSet<Par<String, Integer>> getTopProdutosMaisComprados(String clientCode) throws ClienteInexistenteException;

    /**
     * Calcula o lista com pares, que associam a cada produto o número de distintos clientes que o compraram.
     * Por ordem decrescente do número de unidades vendidas.
     * @param N Tamanho máximo da lista.
     * @return A lista com pares que associam a cada produto o número de distintos clientes que o compraram.
     */
    List<Par<String, Integer>> getTopNProdutosMaisDistintos(int N);

    /**
     * Calcula uma lista com o código dos top 3 clientes que mais dinheiro gastaram numa dada filial.
     * @param filial Filial que se pretende verificar.
     * @return Uma lista com o código dos top 3 clientes que mais dinheiro gastaram numa dada filial.
     * @throws FilialInvalidException Caso a filial indicada não exista.
     */
    List<Par<String, Double>> getTop3Compradores(int filial) throws FilialInvalidException;

    /**
     * Calcula uma lista com pares, que associa a cada cliente o número de produtos distintos comprados.
     * Ordenado por ordem decrescente do número de produtos distintos comprados.
     * @param N Tamanho máximo da lista.
     * @return A lista calculada.
     */
    List<Par<String, Integer>> getTopNVersatileClientes(int N);

    /**
     * Calcula uma lista com pares, que associada a cada cliente o montante gasto no produto indicado.
     * Ordenado por ordem decrescente do valor gasto.
     *
     * @param prodCode Código do produto que se pretende verificar.
     * @param N Tamanho máximo da lista.
     * @return A lista calculada.
     * @throws ProdutoInexistenteException Caso o produto que se pretenda verificar não exista.
     */
    List<Par<String, Double>> getMelhoresClientes(String prodCode, int N) throws ProdutoInexistenteException;

    /**
     * Calcula uma estrutura capaz de armazenar o a faturação total associada a um produto, por mês, filial
     * e valores globais.
     *
     * @param prodCode Produto que se pretende verificar.
     * @return A estrutura calculada.
     * @throws ProdutoInexistenteException Caso o produto não exista.
     */
    IGlobalRep getFaturacaoTotal(String prodCode) throws ProdutoInexistenteException; // X

    /**
     * Indica o número atual de filiais.
     *
     * @return Número atual de filiais.
     */
    int getNFiliais();

}