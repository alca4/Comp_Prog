struct Euler {
    static int T;
    static vector<int> in, out, euler;

    Euler() {Euler(0);}
    Euler(int n) {
        T = 0;
        in.resize(n + 1);
        out.resize(n + 1);
        euler.resize(n * 2 + 1);
    }

    static void tour(int a, int p) {
        in[a] = ++T;
        euler[T] = a;
        for (int nb : nbs[a]) if (nb != p) tour(nb, a);
        out[a] = ++T;
        euler[T] = -a;
    }
};