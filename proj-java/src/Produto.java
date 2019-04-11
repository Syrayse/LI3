public class Produto {

    private String productCode;

    public Produto(String productCode) {
        this.productCode = productCode;
    }

    public Produto(Produto produto) {
        this.productCode = produto.getProductCode();
    }

    public String getProductCode() {
        return this.productCode;
    }

    public void setProductCode(String productCode) {
        this.productCode = productCode;
    }

    @Override
    public String toString() {
        final StringBuffer sb = new StringBuffer("Produto{");
        sb.append("productCode='").append(this.productCode).append('\'');
        sb.append('}');
        return sb.toString();
    }

    @Override
    public boolean equals(Object o) {
        if (this == o) return true;
        if (o == null || getClass() != o.getClass()) return false;
        Produto produto = (Produto) o;
        return this.productCode.equals(produto.getProductCode());
    }

    @Override
    public int hashCode() {
        return this.productCode.hashCode();
    }

    @Override
    public Produto clone() {
        return new Produto(this);
    }
}
