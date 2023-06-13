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
#define EPS 1e-9
// #define cout cerr
ll INF = 1000000000;
ll LINF = 1000000000000000000;
ll MOD = 0;

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

const int MAXN = 200010;
int N;
ll M;
vector<int> disrupt[MAXN];

void solve() {
    // cout << "=====" << endl;
    cin >> N;
    for (int i = 1; i <= N; i++) {
        int n;
        cin >> n;
        disrupt[n].pb(i);
    }
    cin >> M;

    set<pii> ranges;
    ranges.insert({1, N});

    ll ans = 0;
    int cont = N - 1;
    int inserted = 0;
    int remain = N;
    for (int i = N; i >= 1; i--) {
        if (inserted >= M) break;
        for (int d : disrupt[i]) {
            remain--;
            pii p = *(--ranges.upper_bound({d, INF}));
            // cout << p.FF << " " << p.SS << endl;
            cont -= p.SS - p.FF;

            pii p1 = pii(p.FF, d - 1);
            pii p2 = pii(d + 1, p.SS);

            if (p1.FF <= p1.SS) {
                ranges.insert(p1);
                cont += p1.SS - p1.FF;
            }
            if (p2.FF <= p2.SS) {
                ranges.insert(p2);
                cont += p2.SS - p2.FF;
            }
        }
        if (inserted + remain > M) {
            set<ll> vals;
            for (auto n : ranges) vals.insert(n.SS - n.FF);

            while (inserted < M) {
                ans += min(*vals.begin(), M - inserted - 1);
                inserted += *vals.begin() + 1;
            }
            break;
        }
        ans += cont;
        inserted += remain;
    }

    cout << ans << endl;

    for (int i = 1; i <= N; i++) disrupt[i].clear();
}

int main() {
    // freopen(".in", "r", stdin);
    // freopen(".out", "w", stdout);
    srand(time(NULL));
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    int T;
    cin >> T;
    while (T--) solve();

    return 0;
} 