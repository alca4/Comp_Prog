vector<ll> fact, factinv;
vector<vector<int>> stirling;
vector<vector<int>> stirling2;
struct Comb {
    static void get_fact(int x) {
        fact.resize(x + 1);
        factinv.resize(x + 1);
        fact[0] = 1;
        for (int i = 1; i <= x; i++) fact[i] = mult(i, fact[i - 1]);
        factinv[x] = divide(1, fact[x]);
        for (int i = x - 1; i >= 0; i--) factinv[i] = mult(factinv[i + 1], i + 1);
    }

    static void gen_stirling2(int i, int j) {
        stirling2.resize(i + 1);
        for (auto& n : stirling2) n.resize(j + 1);
        for (int n = 0; n <= i; n++) for (int k = 0; k <= n; k++) {
            if (n == k) stirling2[n][k] = 1;
            if (n && k) 
                stirling2[n][k] = add(stirling2[n - 1][k - 1], mult(k, stirling2[n - 1][k]));
        }
    }

    static ll choose(int a, int b) {
        return mult(fact[a], mult(factinv[b], factinv[a - b]));
    }

    static ll fallpow(int a, int b) {
        return mult(fact[a], factinv[a - b]);
    }

    static ll stars_bars(int n, int k) {
        return choose(n + k - 1, k - 1);
    }
};