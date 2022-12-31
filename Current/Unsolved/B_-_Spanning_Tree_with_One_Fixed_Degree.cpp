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

Praise to the Cow God
*/
#include <bits/stdc++.h>
using namespace std;

#define FF first
#define SS second
#define pb push_back
#define ll long long
#define ld long double
#define ull unsigned ll
ll INF = 1000000000;
ll MOD = 1000000007;

ifstream fin(".in");
ofstream fout(".out");

typedef pair<int, int> pii;
typedef pair<ll, ll> pll;

ll add(const ll& a, const ll& b) {return (a + b) % MOD;}
ll sub(const ll& a, const ll& b) {return (a + MOD - b) % MOD;}
ll mult(const ll& a, const ll& b) {return (a * b) % MOD;}
ll power(ll a, ll b)
{
    ll n = b;
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
ll divide(const ll& a, const ll& b) {return (a * power(b, MOD - 2)) % MOD;}

int rand32()
{
    int a = rand();
    int b = rand();
    return (a << 16) | b;
}

ll rand64()
{
    ll a = rand32();
    ll b = rand32();
    return (a << 32) | b;
}

const int MAXN = 200010;
int N, M, D;

vector<int> onbs;
pii edgelist[MAXN];
int p[MAXN], sz[MAXN];
void setup_dsu() {for (int i = 1; i <= N; i++) p[i] = i, sz[i] = 1;}
int root(int a) {return p[a] = (a == p[a] ? a : root(p[a]));}
int combine(int a, int b)
{
    int a0 = a, b0 = b;
    a = root(a), b = root(b);
    if (a == b) return 0;

    if (sz[a] < sz[b]) swap(a, b);
    p[b] = a;
    sz[a] += sz[b];
    return 1;
}

int special[MAXN];
int assign[MAXN];

int main()
{
    srand(time(NULL));
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    cin >> N >> M >> D;
    setup_dsu();

    for (int i = 1; i <= M; i++)
    {
        int a, b;
        cin >> a >> b;
        if (a > b) swap(a, b);
        if (a == 1) onbs.pb(b);
        else combine(a, b);
        edgelist[i] = {a, b};
    }
    special[1] = 1;

    set<int> roots;
    for (int i = 2; i <= N; i++) roots.insert(root(i));

    if (roots.size() > D || onbs.size() < D) cout << "NO" << endl;
    else
    {
        cout << "YES" << endl;
        vector<pii> ans;
        int x = 0;
        for (int i = 0; i < onbs.size(); i++) 
        {
            if (roots.count(root(onbs[i]))) 
            {
                assign[onbs[i]] = root(onbs[i]);
                roots.erase(root(onbs[i]));
                ans.pb({1, onbs[i]});
                x++;
            }
        }
        for (int i = 0; i < onbs.size(); i++)
        {
            if (x == D) break;
            if (assign[onbs[i]] == 0)
            {
                ans.pb({1, onbs[i]});
                x++;
                special[onbs[i]] = 1;
            }
        }
        for (int i = 1; i <= M; i++) 
        {
            if (x == N - 1) break;
            if (!special[edgelist[i].FF] && !special[edgelist[i].SS] &&
                root(edgelist[i].FF) == root(edgelist[i].SS))
            {
                cout << edgelist[i].FF << " " << edgelist[i].SS << endl;
                ans.pb({edgelist[i].FF, edgelist[i].SS});
                x++;
            }
        }

        cout << endl;

        for (int i = 0; i < N - 1; i++) cout << ans[i].FF << " " << ans[i].SS << endl;
    }
    return 0;
} 