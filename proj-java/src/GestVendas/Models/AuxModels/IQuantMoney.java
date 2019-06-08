package GestVendas.Models.AuxModels;

/**
 * Interface que define o contrato que todas as classes que armazenem quantidade e montate de dinheiro devem cumprir.
 */
public interface IQuantMoney {

    /**
     * Indica a quantidade total corretemente associada.
     *
     * @return A quantidade total.
     */
    int getQuantidade();

    /**
     * Indica o montante da receita total associado.
     *
     * @return Montante total da receita.
     */
    double getReceita();

    /**
     * Adiciona um montante de quantidade à estrutura.
     *
     * @param q Quantidade a adicionar.
     * @return Estrutura alterada.
     */
    IQuantMoney addQuantidade(int q);

    /**
     * Adiciona um montante de receita à estrutura.
     *
     * @param r Receita a adicionar.
     * @return Estrutura alterada.
     */
    IQuantMoney addReceita(double r);

    /**
     * Verifica se a estrutura é vazia ou nao.
     *
     * @return Se a estrutura é vazia ou nao.
     */
    boolean isEmpty();

    /**
     * Cria uma cópia da estrutura atual.
     *
     * @return A cópia criada.
     */
    IQuantMoney clone();
}
