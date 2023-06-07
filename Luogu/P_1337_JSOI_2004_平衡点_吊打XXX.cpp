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
ll INF = 1000000000;
ll LINF = 1000000000000000000;
ll MOD = 0;

typedef pair<int, int> pii;
typedef pair<ll, ll> pll;
typedef pair<ld, ld> pld;

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

const int MAXN = 1010;
int N;
int x[MAXN], y[MAXN], w[MAXN];

ld T = 1e5, A = 0.99;

ld mag(pld coords) {
    return sqrt(coords.FF * coords.FF + coords.SS * coords.SS);
}

pld move(pld coords) {
    ld da = 0, db = 0;
    for (int i = 1; i <= N; i++) {
        if (abs(x[i] - coords.FF) < EPS && abs(y[i] - coords.SS) < EPS) continue;
        da += 1.0 * w[i] * (x[i] - coords.FF) / mag(pld(x[i] - coords.FF, y[i] - coords.SS));
        db += 1.0 * w[i] * (y[i] - coords.SS) / mag(pld(x[i] - coords.FF, y[i] - coords.SS));
    }
    // cout << coords.FF << " " << coords.SS << endl;
    // cout << da << " " << db << endl;
    return pld(da * T, db * T);
}

int main()
{
    // freopen(".in", "r", stdin);
    // freopen(".out", "w", stdout);
    srand(time(NULL));
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    auto start = clock();
    mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());
    uniform_real_distribution<ld> urd;

    cin >> N;
    for (int i = 1; i <= N; i++) cin >> x[i] >> y[i] >> w[i];
    
    ld a = 0, b = 0;
    pld olds = pld(0, 0);
    pld olddelta = move(olds);
    while (clock() - start < (ld) 0.95 * CLOCKS_PER_SEC) {
        pld news = pld(olds.FF + olddelta.FF, olds.SS + olddelta.SS);
        pld newdelta = move(news);

        if (mag(newdelta) < mag(olddelta) || 
            urd(rng) < exp((mag(olddelta) - mag(newdelta)) / T)) {
            olds = news;
            olddelta = newdelta;
        }
        T *= A;
    }

    cout << fixed << setprecision(3) << olds.FF << " " << olds.SS << endl;

    return 0;
} 
