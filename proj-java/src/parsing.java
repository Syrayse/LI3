public class parsing {
    public static void main(String[] args) {
        String phrase = "the music made   it   hard      to        concentrate";
        String delims = "[ .]+";
        String[] tokens = phrase.split(delims);

        int i = 0;
        while (i < tokens.length){
            System.out.println(tokens[i] + " ");
            i++;
        }
    }
}
