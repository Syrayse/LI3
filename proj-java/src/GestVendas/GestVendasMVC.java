// Versao 1 do professor Mário Martins
package GestVendas;

import static java.lang.System.out;

public class GestVendasMVC {

    public static void main (String[] args) {
        // O modelo (estruturas de dados)
        /*
		este deve conte ro caTALOGO DE PRODUTOS CLIENTES, faturacao e tratamento por filiais.
		a createData deve inicializar todas estas.

        */
        InterfGereVendasModel model = new GereVendasModel();

        if (model.createData() == null) {
            out.println("Error... ");
            System.exit(-1);
        }

        // O "menu"
        InterfGereVendasView view = new GereVendasView();

        // O controlador
        InterfGereVendasController control = new GereVendasController();

        // é preciso atribuir ao controlador modelos e views, para 
        /*
		O controlador internamente deve conter os models e views com que vai trabalhar.
		Deve ser como está abaixo para que nao seja tao rigido e para se poder alterar a qualquer momento
        */
        control.set(model);
        control.set(view);
        control.startController();
        System.exit(0);
    }

}
