package GestVendas.Models.AuxModels;

/**
 * Interface que todas as classes que englobam valores global, mensais e por filial devem definir.
 */
public interface IGlobalRep {

    /**
     * Adicionar um valor a uma dada filial e mes.
     *
     * @param filial Filial na qual se pretende adicionar.
     * @param mes    Mês ao qual se pretende adicionar.
     * @param val    Valor que se pretende adicionar.
     * @return Estrutura onde foi adicionado o valor.
     */
    IGlobalRep addToFilial(int filial, int mes, double val);

    /**
     * Indica o valor associado a um dado mês e filial.
     * @param filial Filial que se pretende verificar.
     * @param mes Mês que se pretende verificar.
     * @return Valor associado ao mês e filial.
     */
    double getTotal(int filial, int mes);

    /**
     * Valor global associado a um mês.
     * @param mes Mès que se pretende verificar.
     * @return Valor associado.
     */
    double getTotal(int mes);

    /**
     * Representação em string da estrutura.
     * @return Representação em string da estrutura.
     */
    String toString();

    /**
     * Cria uma cópia da estrutura atual.
     * @return Cópia da estrutura atual.
     */
    IGlobalRep clone();
}
