int p[MAXN], sz[MAXN];
void setup_dsu() {for (int i = 1; i <= N; i++) p[i] = i, sz[i] = 1;}
int root(int a) {return p[a] = (a == p[a] ? a : root(p[a]));}
int combine(int a, int b)
{
    a = root(a), b = root(b);
    if (a == b) return 0;

    if (sz[a] < sz[b]) swap(a, b);
    p[b] = a;
    sz[a] += sz[b];
    return 1;
}