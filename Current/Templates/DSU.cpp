int p[MAXN], sz[MAXN];
int root(int a) {return p[a] = (a == p[a] ? a : root(p[a]));}
int combine(int a, int b)
{
    a = root(a), b = root(b);
    if (a == b) return 0;

    if (sz[a] < sz[b]) swap(a, b);
    nbs2[a].pb(b);
    p[b] = a;
    sz[a] += sz[b];
    return 1;
}