import java.util.Arrays;
import java.util.Random;

public class SortBenchmark {
    interface Sorter { void sort(double[] a); }

    static void bubble(double[] a) {
        for (int end = a.length - 1; end > 0; end--) {
            boolean changed = false;
            for (int i = 0; i < end; i++) if (a[i] > a[i + 1]) { double t = a[i]; a[i] = a[i + 1]; a[i + 1] = t; changed = true; }
            if (!changed) break;
        }
    }

    static void merge(double[] a) { merge(a, new double[a.length], 0, a.length); }
    static void merge(double[] a, double[] tmp, int lo, int hi) {
        if (hi - lo < 2) return;
        int mid = (lo + hi) >>> 1;
        merge(a, tmp, lo, mid); merge(a, tmp, mid, hi);
        int i = lo, j = mid, k = lo;
        while (i < mid && j < hi) tmp[k++] = a[i] <= a[j] ? a[i++] : a[j++];
        while (i < mid) tmp[k++] = a[i++];
        while (j < hi) tmp[k++] = a[j++];
        System.arraycopy(tmp, lo, a, lo, hi - lo);
    }

    static class Tree { double value; Tree left, right; Tree(double v) { value = v; } }
    static Tree insert(Tree n, double v) {
        if (n == null) return new Tree(v);
        if (v < n.value) n.left = insert(n.left, v); else n.right = insert(n.right, v);
        return n;
    }
    static int writeInOrder(Tree n, double[] a, int i) {
        if (n == null) return i;
        i = writeInOrder(n.left, a, i); a[i++] = n.value; return writeInOrder(n.right, a, i);
    }
    static void treeSort(double[] a) { Tree root = null; for (double v : a) root = insert(root, v); writeInOrder(root, a, 0); }

    static void heap(double[] a) {
        int n = a.length;
        for (int i = n / 2 - 1; i >= 0; i--) sift(a, n, i);
        for (int end = n - 1; end > 0; end--) { double t = a[0]; a[0] = a[end]; a[end] = t; sift(a, end, 0); }
    }
    static void sift(double[] a, int n, int root) {
        while (2 * root + 1 < n) {
            int child = 2 * root + 1;
            if (child + 1 < n && a[child + 1] > a[child]) child++;
            if (a[root] >= a[child]) return;
            double t = a[root]; a[root] = a[child]; a[child] = t; root = child;
        }
    }

    static void counting(double[] a) {
        double[] keys = a.clone(); Arrays.sort(keys);
        int unique = 0;
        for (double v : keys) if (unique == 0 || Double.compare(v, keys[unique - 1]) != 0) keys[unique++] = v;
        int[] counts = new int[unique];
        for (double v : a) counts[Arrays.binarySearch(keys, 0, unique, v)]++;
        int k = 0;
        for (int i = 0; i < unique; i++) while (counts[i]-- > 0) a[k++] = keys[i];
    }

    static long usedMemory() { Runtime r = Runtime.getRuntime(); return r.totalMemory() - r.freeMemory(); }
    static double[] data(int n, long seed) { Random r = new Random(seed); double[] a = new double[n]; for (int i = 0; i < n; i++) a[i] = r.nextDouble() * 2_000_000 - 1_000_000; return a; }
    static void measure(String name, Sorter sorter, int n, long seed) {
        double[] a = data(n, seed);
        System.gc(); long before = usedMemory(), start = System.nanoTime(); sorter.sort(a); long elapsed = System.nanoTime() - start, delta = Math.max(0, usedMemory() - before);
        System.out.printf("%s,%d,%.3f,%d%n", name, n, elapsed / 1e6, delta);
    }
    public static void main(String[] args) {
        int[] sizes = args.length == 0 ? new int[]{100_000, 1_000_000, 10_000_000, 100_000_000, 1_000_000_000} : Arrays.stream(args).mapToInt(Integer::parseInt).toArray();
        Sorter[] sorters = {SortBenchmark::bubble, SortBenchmark::merge, SortBenchmark::treeSort, SortBenchmark::heap, SortBenchmark::counting};
        String[] names = {"Bubble", "Merge", "Tree", "Heap", "Counting"};
        System.out.println("algoritmo,n,tiempo_ms,memoria_delta_bytes");
        for (int n : sizes) for (int i = 0; i < sorters.length; i++) measure(names[i], sorters[i], n, 42);
    }
}
