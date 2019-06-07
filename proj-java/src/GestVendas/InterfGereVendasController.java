package GestVendas;

/**
 * Interface que define o contrato que qualquer controlador deste sistema deve cumprir.
 */
public interface InterfGereVendasController {

    /**
     * Atribui ao controlador atual um modelo que este pode utilizar para gerir os recursos do sistema.
     *
     * @param it Modelo que se pretende associar.
     * @return O controlador com o modelo indicado.
     */
    InterfGereVendasController set(InterfGereVendasModel it);

    /**
     * Atribui ao controlador atual uma forma de poder comunicar visualmente com o utilizador do sistema.
     *
     * @param it Interface que permite a comunicação visual.
     * @return O controlador com o metódo de comunicação indicado.
     */
    InterfGereVendasController set(InterfGereVendasView it);

    /**
     * Dá o arranque ao controlador, de forma a que este possa cumprir as suas funcionalidades principais.
     */
    void startController();

}