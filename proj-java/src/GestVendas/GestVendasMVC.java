package GestVendas;

/**
 * Classe que implementa a main desta nossa estruturação separada
 * em model view controller. E permite dar o "arranque" ao programa.
 */
public class GestVendasMVC {

    public static void main (String[] args) {
        InterfGereVendasModel model = new GereVendasModel();

        InterfGereVendasView view = new GereVendasView();

        InterfGereVendasController control = new GereVendasController();

        control.set(model);
        control.set(view);
        control.startController();
    }

}
