/*
  ___
 (o,o)
<  .  >
--"-"---
Rowlet is orz
  _      _      _
>(.)__ >(.)__ >(.)__
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
#define ull unsigned ll
#define endl "\n"
ll INF = 1000000000;
ll LINF = 1000000000000000000;
ll MOD = LINF;
// ll MOD = 1000000007;
// ll MOD = 998244353;

typedef pair<int, int> pii;
typedef pair<ll, ll> pll;

ll add(const ll& a, const ll& b) 
{
    ll x = a + b;
    if (a + b >= MOD) x -= MOD;
    return x;
}
ll sub(const ll& a, const ll& b) 
{
    ll x = a - b;
    if (a - b < 0) x += MOD;
    return x;
}
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
        int id = __builtin_ctz(n & -n);
        ans = mult(ans, binexp[id]);
        n -= (n & -n);
    }

    return ans;
}
ll divide(const ll& a, const ll& b) {return (a * power(b, MOD - 2)) % MOD;}
template<class X, class Y> void maxeq(X &x, Y y) {if (x < y) x = y;}
template<class X, class Y> void mineq(X &x, Y y) {if (x > y) x = y;}
template<class X, class Y> void addeq(X &x, Y y) {x = add(x, y);}
template<class X, class Y> void subeq(X &x, Y y) {x = sub(x, y);}
template<class X, class Y> void multeq(X &x, Y y) {x = mult(x, y);}
template<class X, class Y> void diveq(X &x, Y y) {x = divide(x, y);}

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

const int MAXN = 100010;
int N;
vector<int> nbs[MAXN];
int v[MAXN];
map<int, vector<int>> freq;
pii edges[MAXN];
int ans[MAXN];
map<pii, int> remedy;
map<int, int> freq2[2];
map<int, map<int, int>> belong;
// ll fact[MAXN], factinv[MAXN];

// ll choose(int a, int b)
// {
//     return mult(fact[a], mult(factinv[b], factinv[a - b]));
// }

// void get_fact(int x)
// {
//     fact[0] = 1;
//     for (int i = 1; i <= x; i++) fact[i] = mult(i, fact[i - 1]);
//     factinv[x] = divide(1, fact[x]);
//     for (int i = x - 1; i >= 0; i--) factinv[i] = mult(factinv[i + 1], i + 1);
// }

vector<pii> e;
bool DFS(int a, int p, int t)
{
    int found = 0;
    for (int nb : nbs[a]) if (nb != p)
    {
        e.pb(pii(a, nb));
        if (nb == t)
        {
            found = 1;
            break;
        }
        if (DFS(nb, a, t)) 
        {
            found = 1;
            break;
        }
    }
    if (!found && p != 0) e.pop_back();
    return found;
}

void DFS2(int r, int a, int p, int x1, int x2)
{
    if (freq.count(v[a])) belong[r][v[a]]++;
    for (int nb : nbs[a]) if (nb != p && nb != x1 && nb != x2)
        DFS2(r, nb, a, x1, x2);
}

int main()
{
    // freopen('.in', 'r', cin);
    // freopen('.out', 'w', cout);
    srand(time(NULL));
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    cin >> N;
    for (int i = 1; i < N; i++)
    {
        int a, b;
        cin >> a >> b;
        nbs[a].pb(b);
        nbs[b].pb(a);
        edges[i] = pii(a, b);
    }
    for (int i = 1; i <= N; i++) 
    {
        cin >> v[i];
        freq[v[i]].pb(i);
    }

    vector<int> rem;
    for (auto n : freq) if (n.SS.size() == 1) rem.pb(n.FF);
    for (int n : rem) freq.erase(n);

    if (freq.size()) 
    {
        for (int i = 1; i < N; i++) ans[i] = freq.rbegin()->FF;
        if (freq.rbegin()->SS.size() == 2)
        {
            DFS(freq.rbegin()->SS[0], 0, freq.rbegin()->SS[1]);
            vector<pii> tmp = e;
            DFS2(tmp.back().SS, tmp.back().SS, 0, tmp.back().FF, 0);
            
            while (!tmp.empty())
            {
                int cv = tmp.back().FF;
                int v1 = tmp.back().SS;
                tmp.pop_back();
                int v2 = 0;
                if (tmp.size()) v2 = tmp.back().FF;
                DFS2(cv, cv, 0, v1, v2);
            }

            for (auto n : belong[e.back().SS]) freq2[1][n.FF] += n.SS;
            for (int i = 0; i < e.size(); i++)
                for (auto n : belong[e[i].FF]) freq2[0][n.FF] += n.SS;

            set<int> a1, a2;
            for (auto n : freq2[0]) if (n.SS >= 2) a1.insert(n.FF);
            for (auto n : freq2[1]) if (n.SS >= 2) a2.insert(n.FF);

            while (e.size())
            {
                // cout << e.back().FF << " is the other node" << endl;
                remedy[e.back()] = 0;
                if (a1.size()) maxeq(remedy[e.back()], *a1.rbegin());
                if (a2.size()) maxeq(remedy[e.back()], *a2.rbegin());
                e.pop_back();

                if (e.size())
                {
                    for (auto n : belong[e.back().SS])
                    {
                        // cout << e.back().FF << " " << n.FF << " " << n.SS << endl;
                        freq2[0][n.FF] -= n.SS;
                        if (freq2[0][n.FF] < 2 && freq2[0][n.FF] + n.SS >= 2) 
                            a1.erase(n.FF);
                        
                        freq2[1][n.FF] += n.SS;
                        if (freq2[1][n.FF] >= 2 && freq2[1][n.FF] - n.SS < 2) 
                            a2.insert(n.FF);
                    }
                }

                // cout << e.back().SS << endl;
                // for (auto n : freq2[0]) cout << n.FF << " " << n.SS << endl;
                // cout << endl;
                // for (auto n : freq2[1]) cout << n.FF << " " << n.SS << endl;
                // cout << endl;
            }
        }
    }

    for (int i = 1; i < N; i++) 
    {
        if (remedy.count(edges[i])) ans[i] = remedy[edges[i]];
        if (remedy.count(pii(edges[i].SS, edges[i].FF))) 
            ans[i] = remedy[pii(edges[i].SS, edges[i].FF)];
        cout << ans[i] << endl;
    }

    return 0;
} 