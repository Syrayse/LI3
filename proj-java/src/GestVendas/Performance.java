package GestVendas;

import GestVendas.Exceptions.InvalidConfigException;
import GestVendas.Models.BaseModels.Cliente;
import GestVendas.Models.BaseModels.Produto;
import GestVendas.Models.BaseModels.Venda;
import GestVendas.Models.Catalogs.CatClientes;
import GestVendas.Models.Catalogs.CatProdutos;
import GestVendas.lib.Crono;

import java.io.BufferedReader;
import java.io.IOException;
import java.nio.file.Files;
import java.nio.file.Path;
import java.nio.file.Paths;
import java.util.List;

public class Performance {
    public static void main(String[] args) {
        String config = "src/tests/performanceConfigs.txt";
        try {
            pLer(config);
            pParsing(config);
            pValidacao(config);
        }
        catch (Exception e) {
            System.out.println("Erro");
        }
    }

    private static void pLer(String configs) throws IOException {
        System.out.println("Starting Read-Only");
        System.out.println();

        List<String> lines = Files.readAllLines(Paths.get(configs));
        String[] tokens;
        for (int i = 0; i < 5; i++) {
            tokens = lines.get(i).split("[ :]+");

                try {
                    Crono.start();
                    BufferedReader br = Files.newBufferedReader(Paths.get(tokens[1]));
                    String linha;
                    while (br.readLine() != null);
                }
                catch (Exception e) {
                    System.err.format("IOException: %s%n", e);
                }
            System.out.println(Crono.print() + " s");
        }
    }

    private static void pParsing(String configs) throws IOException, InvalidConfigException {
        System.out.println();
        System.out.println("Starting Read and parsing");
        System.out.println();

        List<String> lines = Files.readAllLines(Paths.get(configs));
        String[] tokens;
        String linha;

        tokens = lines.get(0).split("[ :]+");

        try {
            Crono.start();
            BufferedReader br = Files.newBufferedReader(Paths.get(tokens[1]));
            while ((linha = br.readLine()) != null){
                parseProdutoCode(linha);
                Produto c = new Produto(linha);
            }
        }
        catch (Exception e) {
            System.err.format("IOException: %s%n", e);
        }
        System.out.println(Crono.print() + " s");

        tokens = lines.get(1).split("[ :]+");

        try {
            Crono.start();
            BufferedReader br = Files.newBufferedReader(Paths.get(tokens[1]));
            while ((linha = br.readLine()) != null){
                parseClienteCode(linha);
                Cliente c = new Cliente(linha);
            }
        }
        catch (Exception e) {
            System.err.format("IOException: %s%n", e);
        }
        System.out.println(Crono.print() + " s");

        for (int i = 2; i < 5; i++) {
            tokens = lines.get(i).split("[ :]+");

            try {
                Crono.start();
                BufferedReader br = Files.newBufferedReader(Paths.get(tokens[1]));
                while ((linha = br.readLine()) != null){
                    String venda[] = parseVendaCode(linha);
                    Venda v = new Venda(venda[0], Double.parseDouble(venda[1]), Integer.parseInt(venda[2]), venda[3], venda[4], Integer.parseInt(venda[5]), Integer.parseInt(venda[6]));
                }
            }
            catch (Exception e) {
                System.err.format("IOException: %s%n", e);
            }
            System.out.println(Crono.print() + " s");
        }
    }

    private static void pValidacao(String configs) throws IOException, InvalidConfigException {
        CatProdutos cp = new CatProdutos();
        CatClientes cc = new CatClientes();

        System.out.println();
        System.out.println("Starting Read, parsing and validation");
        System.out.println();

        List<String> lines = Files.readAllLines(Paths.get(configs));
        String[] tokens;
        String linha;

        tokens = lines.get(0).split("[ :]+");

        try {
            Crono.start();
            BufferedReader br = Files.newBufferedReader(Paths.get(tokens[1]));
            while ((linha = br.readLine()) != null){
                if (validateProdutoCode(parseProdutoCode(linha))){
                    Produto p = new Produto(linha);
                    cp.insereProduto(p);
                }
            }
        }
        catch (Exception e) {
            System.err.format("IOException: %s%n", e);
        }
        System.out.println(Crono.print() + " s");

        tokens = lines.get(1).split("[ :]+");

        try {
            Crono.start();
            BufferedReader br = Files.newBufferedReader(Paths.get(tokens[1]));
            while ((linha = br.readLine()) != null){
                if (validateClienteCode(parseClienteCode(linha))) {
                    Cliente c = new Cliente(linha);
                    cc.insereCliente(c);
                }
            }
        }
        catch (Exception e) {
            System.err.format("IOException: %s%n", e);
        }
        System.out.println(Crono.print() + " s");

        for (int i = 2; i < 5; i++) {
            tokens = lines.get(i).split("[ :]+");

            try {
                Crono.start();
                BufferedReader br = Files.newBufferedReader(Paths.get(tokens[1]));
                while ((linha = br.readLine()) != null){
                    String venda [] = parseVendaCode(linha);
                    if (validateVendaCode(venda, cp, cc)) {
                        Venda v = new Venda(venda[0], Double.parseDouble(venda[1]), Integer.parseInt(venda[2]), venda[3], venda[4], Integer.parseInt(venda[5]), Integer.parseInt(venda[6]));
                    }
                }
            }
            catch (Exception e) {
                System.err.format("IOException: %s%n", e);
            }
            System.out.println(Crono.print() + " s");
        }
    }

    private static String parseProdutoCode(String prodCode) {
        return prodCode;
    }

    private static String parseClienteCode(String clienteCode) {
        return clienteCode;
    }

    private static String[] parseVendaCode(String vendaTokens) {
        String tokens [] = vendaTokens.split(" ");
        return tokens;
    }

    private static boolean validateProdutoCode(String prodCode) {
        if (prodCode.length() == 6 && Character.isLetter(prodCode.charAt(0)) && Character.isLetter(prodCode.charAt(1)) && Character.isDigit(prodCode.charAt(2)) && Character.isDigit(prodCode.charAt(3)) && Character.isDigit(prodCode.charAt(4)) && Character.isDigit(prodCode.charAt(5))){
            char c = prodCode.charAt(2);
            int a = Character.getNumericValue(c);
            if (a > 0) {
                return true;
            }
        }
        return false;
    }

    private static boolean validateClienteCode(String clienteCode) {
        if (clienteCode.length() == 5 && Character.isLetter(clienteCode.charAt(0)) && Character.isDigit(clienteCode.charAt(1)) && Character.isDigit(clienteCode.charAt(2)) && Character.isDigit(clienteCode.charAt(3)) && Character.isDigit(clienteCode.charAt(4))){
            char c = clienteCode.charAt(1);
            int a = Character.getNumericValue(c);
            if (a > 5 || a == 0) return false;
            if (a == 5) {
                for (int i = 2; i < 5; i++) {
                  c=clienteCode.charAt(i);
                  a=Character.getNumericValue(c);
                  if (a != 0) return false;
                }
            }
            return true;
        }
        return false;
    }

    private static boolean validateVendaCode(String[] vendaTokens, CatProdutos cp, CatClientes cc) {
        double preco = Double.parseDouble(vendaTokens[1]);
        int un = Integer.parseInt(vendaTokens[2]);
        int length = vendaTokens[3].length();
        char tipo = vendaTokens[3].charAt(0);
        int mes = Integer.parseInt(vendaTokens[5]);
        int fil = Integer.parseInt(vendaTokens[6]);

        if (preco > 0 && preco < 1000 && un > 0 && un <= 200 && length == 1 && (tipo == 'P' || tipo == 'N') && mes > 0 && mes < 13 && fil > 0 && fil < 4) {
            if (cp.existeProduto(vendaTokens[0]) && cc.existeCliente(vendaTokens[4]))
            {
                return true;
            }
        }
        return false;
    }
}
