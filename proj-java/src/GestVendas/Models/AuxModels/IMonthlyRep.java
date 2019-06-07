package GestVendas.Models.AuxModels;

/**
 * Interface que todas as estruturas mensais devem contemplar.
 */
public interface IMonthlyRep {

    /**
     * Adiciona um novo valor à estrutura.
     *
     * @param month Mês onde se pretende adicionar.
     * @param val   Valor que se pretende aadicionar.
     * @return A estrutura que foi alterada.
     */
    IMonthlyRep addToMonth(int month, int val);

    /**
     * Indica o valor associado a um mes.
     * @param month Mês a considerar.
     * @return O valor associado àquele mês.
     */
    int getMonth(int month);

    /**
     * Calcula a representação em string da estrutura.
     * @return A string calculada.
     */
    String toString();

    /**
     * Cria uma cópia da estrutura atual.
     * @return A cópia.
     */
    IMonthlyRep clone();

}
