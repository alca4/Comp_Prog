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
ll MOD = 998244353;

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
ll binexp[32];
ll power(ll a, ll b)
{
    ll n = b;
    ll ans = 1;

    binexp[0] = a;
    for (int i = 1; i < 32; i++) binexp[i] = mult(binexp[i - 1], binexp[i - 1]);

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

const int MAXN = 300010;
int N, M;

ll fact[1000010], factinv[1000010];

ll choose(int a, int b)
{
    return mult(fact[a], mult(factinv[b], factinv[a - b]));
}

void get_fact(int x)
{
    fact[0] = 1;
    for (int i = 1; i <= x; i++) fact[i] = mult(i, fact[i - 1]);
    factinv[x] = divide(1, fact[x]);
    for (int i = x - 1; i >= 0; i--) factinv[i] = mult(factinv[i + 1], i + 1);
}

ll hashval[MAXN];
vector<int> s[MAXN];
vector<int> e[MAXN];
map<ll, int> times;

void solve() {
    // cout << "==========" << endl;
    cin >> N >> M;

    for (int i = 1; i <= M; i++) {
        int a, b;
        cin >> a >> b;
        s[a].pb(i);
        e[b].pb(i);
    }

    ll chash = 0;
    for (int i = 1; i <= N; i++) {
        for (int n : s[i]) chash ^= hashval[n];
        times[chash]++;
        for (int n : e[i]) chash ^= hashval[n];
    }

    ll ans = 1;
    for (pll n : times) {
        if (n.SS % 2 == 0) 
            multeq(ans, mult(divide(fact[n.SS], n.SS / 2 + 1), 
                             mult(factinv[n.SS / 2], factinv[n.SS / 2])));
        else ans = 0;
    }

    cout << ans << endl;

    for (int i = 1; i <= N; i++) s[i].clear(), e[i].clear();
    times.clear();
}

int main()
{
    // freopen(".in", "r", stdin);
    // freopen(".out", "w", stdout);
    srand(time(NULL));
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    for (int i = 1; i <= 300000; i++) {
        hashval[i] = rand();
        for (int j = 0; j < 3; j++) hashval[i] = (hashval[i] << 16) | rand();
    }

    get_fact(600000);

    int T;
    cin >> T;
    while (T--) solve();

    return 0;
} 