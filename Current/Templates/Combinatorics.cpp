ll fact[1000010], factinv[1000010];

struct Comb {
    static void get_fact(int x) {
        fact[0] = 1;
        for (int i = 1; i <= x; i++) fact[i] = mult(i, fact[i - 1]);
        factinv[x] = divide(1, fact[x]);
        for (int i = x - 1; i >= 0; i--) factinv[i] = mult(factinv[i + 1], i + 1);
    }

    static ll choose(int a, int b) {
        return mult(fact[a], mult(factinv[b], factinv[a - b]));
    }

    static ll stars_bars(int n, int k) {
        return choose(n + k - 1, k - 1);
    }
};