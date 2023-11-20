int p[MAXN];
void setup_dsu() {for (int i = 1; i <= N; i++) p[i] = i, sz[i] = 1;}
int root(int a) {return p[a] = (a == p[a] ? a : root(p[a]));}
int combine(int a, int b)
{
    a = root(a), b = root(b);
    if (a == b) return 0;

    p[b] = p[a] = p[++N] = N;
    lift[a][0] = N;
    lift[b][0] = N;
    return 1;
}