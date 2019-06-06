package GestVendas;

import GestVendas.lib.Crono;

import java.io.BufferedReader;
import java.io.FileReader;
import java.io.IOException;
import java.nio.file.Files;
import java.nio.file.Paths;
import java.util.ArrayList;
import java.util.List;

import static java.lang.System.out;

public class TesteVendas {

    public static List<String> lerLinhasWithBuff(String fichTxt) {
        List<String> linhas = new ArrayList<>();
        BufferedReader inFile = null;
        String linha = null;

        try {
            inFile = new BufferedReader(new FileReader(fichTxt));
            while( (linha = inFile.readLine()) != null )
                linhas.add(linha);
        }
        catch(IOException exc) {
            out.println(exc);
        }

        return linhas;
    }

    public static void main(String[] args) {
        List<String> lines;
        out.println("first");
        Crono.start();
        try {
            lines = Files.readAllLines(Paths.get("Vendas_1M.txt"));
            out.println(Crono.stop());
            out.println(lines.size());

            out.println("second");
            Crono.start();
            lines = Files.readAllLines(Paths.get("Vendas_3M.txt"));
            out.println(Crono.stop());
            out.println(lines.size());

            out.println("third");
            Crono.start();
            lines = Files.readAllLines(Paths.get("Vendas_5M.txt"));
            out.println(Crono.stop());
            out.println(lines.size());
        }
        catch(IOException exc) {
            out.println(exc);
        }
    }
}
