package GestVendas.lib;

import java.io.Serializable;

public class Par<K, V> implements Serializable {

    private K key;
    private V value;

    public Par(K key, V value) {
        this.key = key;
        this.value = value;
    }

    public K getKey() {
        return key;
    }

    public V getValue() {
        return value;
    }

    @Override
    public boolean equals(Object o) {
        if (this == o) return true;
        if (o == null || getClass() != o.getClass()) return false;
        Par<?, ?> par = (Par<?, ?>) o;
        return key.equals(par.getKey()) &&
                value.equals(par.getValue());
    }

    @Override
    public int hashCode() {
        return key.hashCode();
    }

}
