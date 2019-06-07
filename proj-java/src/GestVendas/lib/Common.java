package GestVendas.lib;

public final class Common {

    public static final int MES_MAX = 12;

    private Common() {
    }

    public static boolean intervaloInclusivo(int x, int min, int max) {
        return min <= x && x <= max;
    }

    public static boolean intervaloInclusivo(char x, char min, char max) {
        return min <= x && x <= max;
    }

    public static boolean intervaloInclusivo(double x, double min, double max) {
        return min <= x && x <= max;
    }
}
