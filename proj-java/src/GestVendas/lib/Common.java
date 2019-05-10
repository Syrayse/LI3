package GestVendas.lib;

public final class Common {

    private Common() {
    }

    public static boolean intervaloInclusivo(int x, int min, int max) {
        return min <= x && x <= max;
    }

}
