/*
  ___
 (o,o)
<  .  >
--"-"---
Rowlet is orz
  _      _      _
>(.)__ <(.)__ =(.)__
 (___/  (___/  (___/
I am dum duck
*/
#include <bits/stdc++.h>
using namespace std;

#define FF first
#define SS second
#define pb push_back
#define ll long long
#define ld long double
#define INF 1000000000ll
#define MOD 1000000007ll

typedef pair<int, int> pii;
typedef pair<ll, ll> pll;

ll add(const ll& a, const ll& b) {return (a + b) % MOD;}
ll mult(const ll& a, const ll& b) {return (a * b) % MOD;}

ll modInverse(ll a)
{
    ll n = MOD - 2;
    ll ans = 1;

    ll binexp[64];
    binexp[0] = a;
    for (int i = 1; i < 64; i++) binexp[i] = mult(binexp[i - 1], binexp[i - 1]);

    while (n > 0)
    {
        int id = (int) log2(n & -n);
        ans = mult(ans, binexp[id]);
        n -= (n & -n);
    }

    return ans;
}

const int MAXN = 100010;
int N, M;

int p[MAXN], sz[MAXN];
int root(int a) {return p[a] = (a == p[a] ? a : root(p[a]));}
int combine(int a, int b)
{
    a = root(a), b = root(b);
    if (root(a) == root(b)) return 0;

    if (sz[a] < sz[b]) swap(a, b);
    p[b] = a;
    sz[a] += sz[b];
    return 1;
}

struct ST
{
    int seg[8 * MAXN];

    void update(int a, int v, int cid, int ss, int se)
    {
        if (ss == se)
        {
            seg[cid] += v;
            return;
        }

        int mid = (ss + se) / 2;
        if (a <= mid) update(a, v, cid * 2, ss, mid);
        else update(a, v, cid * 2 + 1, mid + 1, se);
        seg[cid] = seg[cid * 2] + seg[cid * 2 + 1];
    }

    int query(int a, int b, int cid, int ss, int se)
    {
        if (a <= ss && se <= b) return seg[cid];

        int ans = 0;
        int mid = (ss + se) / 2;
        if (a <= mid) ans += query(a, b, cid * 2, ss, mid);
        if (b > mid) ans += query(a, b, cid * 2 + 1, mid + 1, se);
        return ans;
    } 
};

ST st;

int T = 0;
int in[MAXN], out[MAXN];
vector<int> nbs[MAXN];
void DFS(int a, int p)
{
    in[a] = ++T;
    for (int i = 0; i < nbs[a].size(); i++) if (nbs[a][i] != p) DFS(nbs[a][i], a);
    out[a] = ++T;
}

pii edges[2 * MAXN];

void Delete(int a, int b)
{
    if (in[a] > in[b]) swap(a, b);
    if (out[b] < out[a]) 
    {
        st.update(in[a] + 1, -1, 1, 1, 2 * N);
        st.update(in[b], 1, 1, 1, 2 * N);
        st.update(out[b] + 1, -1, 1, 1, 2 * N);
        st.update(out[a], 1, 1, 1, 2 * N);
    }
    else 
    {
        st.update(1, -1, 1, 1, 2 * N);
        st.update(in[a], 1, 1, 1, 2 * N);
        st.update(out[a] + 1, -1, 1, 1, 2 * N);
        st.update(in[b], 1, 1, 1, 2 * N);
        st.update(out[b] + 1, -1, 1, 1, 2 * N);
        st.update(2 * N, 1, 1, 1, 2 * N);
    }
}

int main()
{
    srand(time(NULL));
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    cin >> N >> M;
    for (int i = 1; i <= N; i++) p[i] = i, sz[i] = 1;
    int cnt = 0;
    for (int i = 1; i <= M; i++)
    {
        int a, b;
        cin >> a >> b;
        edges[i] = {a, b};
        if (combine(a, b)) 
        {
            edges[i] = {0, 0};
            nbs[a].pb(b);
            nbs[b].pb(a);
            ++cnt;
        }
    }
    assert(cnt == N - 1);

    st.update(1, 1, 1, 1, 2 * N);

    DFS(1, 0);

    for (int i = 1; i <= M; i++) if (edges[i] != pii(0, 0)) 
        Delete(edges[i].FF, edges[i].SS);

    for (int i = 1; i <= N; i++) 
    {
        if (st.query(1, in[i], 1, 1, 2 * N) <= 0) cout << 0;
        else cout << 1;
    }
    cout << endl;
    return 0;
} 