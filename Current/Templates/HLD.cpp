struct ST
{
    vector<ll> seg;

    ST() {ST(0);}

    ST(int n) {seg.resize(1 + 4 * n);}

    void update(int a, int v, int cid, int ss, int se)
    {
        if (ss == se)
        {
            seg[cid] = v;
            return;
        }

        int mid = (ss + se) / 2;
        if (a <= mid) update(a, v, cid * 2, ss, mid);
        else update(a, v, cid * 2 + 1, mid + 1, se);
        seg[cid] = seg[cid * 2] + seg[cid * 2 + 1];
    }

    ll query(int a, int b, int cid, int ss, int se)
    {
        if (a <= ss && se <= b) return seg[cid];

        ll ans = 0;
        int mid = (ss + se) / 2;
        if (a <= mid) ans += query(a, b, cid * 2, ss, mid);
        if (b > mid) ans += query(a, b, cid * 2 + 1, mid + 1, se);
        return ans;
    }
};

int w[MAXN];
int sz[MAXN];
vector<int> nbs[MAXN];
int hchild[MAXN];
pii loc[MAXN];
ST chains[MAXN];
vector<int> nodes[MAXN];
int chainsz[MAXN];

int in[MAXN];
int out[MAXN];
int euler[2 * MAXN];
int lift[MAXN][32];
int T = 0;
void tour(int a, int p)
{
    lift[a][0] = p;
    for (int j = 1; j < 32; j++) 
        lift[a][j] = lift[lift[a][j - 1]][j - 1];
    in[a] = ++T;
    euler[T] = a;
    for (int i = 0; i < nbs[a].size(); i++) if (nbs[a][i] != p) tour(nbs[a][i], a);
    out[a] = ++T;
    euler[T] = -a;
}
bool is_anc(int a, int b) {return in[a] <= in[b] && out[b] <= out[a];}
void setup_lca() {tour(1, 0);}
int lca(int a, int b)
{
    if (is_anc(a, b)) return a;
    if (is_anc(b, a)) return b;

    for (int i = 31; i >= 0; i--)
        if (lift[a][i] != 0 && !is_anc(lift[a][i], b)) a = lift[a][i];
    
    return lift[a][0];
}

bool Comp(int a, int b)
{
    return sz[a] < sz[b];
}

int C = 0;
void DFS(int a, int p)
{
    sz[a] = 1;
    vector<int> check;
    for (int nb : nbs[a]) if (nb != p)
    {
        DFS(nb, a);
        sz[a] += sz[nb];
        lift[nb][0] = a;
        check.pb(nb);
    }
    
    sort(check.rbegin(), check.rend(), Comp);
    if (check.size())
    {
        hchild[a] = check[0];
        loc[a] = pii(loc[hchild[a]].FF, loc[hchild[a]].SS + 1);
    }
    else 
    {
        loc[a] = pii(++C, 1);
        nodes[C].pb(0);
    }
    nodes[loc[a].FF].pb(a);
    chainsz[loc[a].FF]++;
}

void setup_hld()
{
    DFS(1, 0);
    setup_lca();
    for (int i = 1; i <= C; i++) 
    {
        chains[i] = ST(chainsz[i]);
        for (int j = 1; j <= chainsz[i]; j++)
            chains[i].update(j, w[nodes[i][j]], 1, 1, chainsz[i]);
    }
}

ll answer(int a, int b)
{
    int c = lca(a, b);

    int aloc = loc[a].FF;
    int bloc = loc[b].FF;
    ll ans = 0;
    while (a && loc[a].FF != loc[c].FF)
    {
        ans += chains[aloc].query(loc[a].SS, chainsz[aloc], 1, 1, chainsz[aloc]);
        a = lift[nodes[aloc][chainsz[aloc]]][0];
        aloc = loc[a].FF;
    }
    if (a) ans += chains[aloc].query(loc[a].SS, loc[c].SS, 1, 1, chainsz[aloc]);

    while (b && loc[b].FF != loc[c].FF)
    {
        ans += chains[bloc].query(loc[b].SS, chainsz[bloc], 1, 1, chainsz[bloc]);
        b = lift[nodes[bloc][chainsz[bloc]]][0];
        bloc = loc[b].FF;
    }
    if (b) ans += chains[bloc].query(loc[b].SS, loc[c].SS, 1, 1, chainsz[bloc]);

    ans -= w[c];
    return ans;
}