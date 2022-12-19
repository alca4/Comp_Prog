int in[MAXN];
int out[MAXN];
int euler[2 * MAXN];
int T = 0;
void tour(int a, int p)
{
    in[a] = ++T;
    euler[T] = a;
    for (int i = 0; i < nbs[a].size(); i++) if (nbs[a][i] != p) tour(nbs[a][i], a);
    out[a] = ++T;
    euler[T] = -a;
}