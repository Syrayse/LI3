package GestVendas.Models.AuxModels;

/**
 * Interface que define o contrato que uma InfoMensal devem comtemplar.
 */
public interface InterfInfoMensal {

    /**
     * Insere uma quantidade num dado mês.
     *
     * @param mes   Mês a adicionar.
     * @param quant Quantidade a adicionar.
     * @return Estrutura alterada.
     */
    InterfInfoMensal insereQuant(int mes, int quant);

    /**
     * Insere uma quantidade de distintos num dado mês.
     *
     * @param mes   Mès a adicionar.
     * @param quant Quantidade a adicionar.
     * @return Estrutura alterada.
     */
    InterfInfoMensal insereQuandDis(int mes, int quant);

    /**
     * Insere uma receita num dado mês.
     *
     * @param mes Mês a adicionar.
     * @param rec Receita a adicionar.
     * @return Estrutura alterada.
     */
    InterfInfoMensal insereReceita(int mes, double rec);

    /**
     * Quantidade de um dado mês
     *
     * @param mes Mês que se pretende verificar.
     * @return Quantidade de um dado mês.
     */
    int getQuant(int mes);

    /**
     * Quantidade de distintos de um dado mês.
     *
     * @param mes Mês que se pretende verificar.
     * @return Quantidade de distintos de um mês.
     */
    int getQuantDis(int mes);

    /**
     * Receita de um dado mês.
     *
     * @param mes Mês que se pretende verificar.
     * @return Receita de um dado mês.
     */
    double getReceita(int mes);

    /**
     * Calcula a representação em string associada.
     *
     * @return A string calculada.
     */
    String toString();

    /**
     * Cria uma cópia da estrutura atual.
     * @return Cria uma estrutura cópia.
     */
    InterfInfoMensal clone();

}
