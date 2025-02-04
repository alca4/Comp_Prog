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
typedef complex<ld> cd;

ll add(const ll& a, const ll& b) {return (a + b) % MOD;}
ll sub(const ll& a, const ll& b) {return (a - b + MOD) % MOD;}
ll mult(const ll& a, const ll& b) {return (a * b) % MOD;}
ll power(ll a, ll b) {
    ll n = a;
    ll ans = 1;

    for (int i = 0; i < 32; i++) {
        if (b & 1) ans = (ans * n) % MOD;
        n = (n * n) % MOD;
        b >>= 1;
    }

    return ans;
}
ll divide(const ll& a, const ll& b) {return (a * power(b, MOD - 2)) % MOD;}
template<class X, class Y> void maxeq(X& x, Y y) {if (x < y) x = y;}
template<class X, class Y> void mineq(X& x, Y y) {if (x > y) x = y;}
template<class X, class Y> void addeq(X& x, Y y) {x = add(x, y);}
template<class X, class Y> void subeq(X& x, Y y) {x = sub(x, y);}
template<class X, class Y> void multeq(X& x, Y y) {x = mult(x, y);}
template<class X, class Y> void diveq(X& x, Y y) {x = divide(x, y);}

mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());
// mt19937_64 rng(chrono::steady_clock::now().time_since_epoch().count());

const int MAXN = 200010;
int N;
struct Range {
    int s;
    int e;
    int id;

    int lb = 0;
    int rb = INF;
} rngs[MAXN];

bool Comp1(const Range& r1, const Range& r2) {
    return pii(r1.s, -r1.e) < pii(r2.s, -r2.e);
}

bool Comp2(const Range& r1, const Range& r2) {
    return pii(r1.e, -r1.s) > pii(r2.e, -r2.s);
}

int ans[MAXN];

void solve() {
    cin >> N;
    for (int i = 1; i <= N; i++) cin >> rngs[i].s >> rngs[i].e;
    for (int i = 1; i <= N; i++) rngs[i].id = i;

    sort(rngs + 1, rngs + 1 + N, Comp1);
    set<int> duck;
    for (int i = 1; i <= N; i++) {
        if (duck.size() && *duck.rbegin() >= rngs[i].e) {
            rngs[i].rb = min(rngs[i].rb, *duck.lower_bound(rngs[i].e));
        }

        duck.insert(rngs[i].e);
    }
    duck.clear();

    sort(rngs + 1, rngs + 1 + N, Comp2);
    for (int i = 1; i <= N; i++) {
        if (duck.size() && *duck.begin() <= rngs[i].s) {
            rngs[i].lb = max(rngs[i].lb, *(--duck.upper_bound(rngs[i].s)));
        }

        duck.insert(rngs[i].s);
    }

    for (int i = 1; i <= N; i++) {
        if (rngs[i].lb == 0 && rngs[i].rb == INF) {
            ans[rngs[i].id] = 0;
            continue;
        }

        // cout << rngs[i].s << " " << rngs[i].e << " " << rngs[i].lb << " " << rngs[i].rb << endl;
        ans[rngs[i].id] = (rngs[i].rb - rngs[i].e) + (rngs[i].s - rngs[i].lb);
    }

    set<pii> checky;
    set<pii> baddy;
    for (int i = 1; i <= N; i++) {
        if (checky.count(pii(rngs[i].s, rngs[i].e))) {
            baddy.insert(pii(rngs[i].s, rngs[i].e));
        }
        checky.insert(pii(rngs[i].s, rngs[i].e));
    }

    for (int i = 1; i <= N; i++) if (baddy.count(pii(rngs[i].s, rngs[i].e))) ans[rngs[i].id] = 0;

    for (int i = 1; i <= N; i++) cout << ans[i] << endl;

    for (int i = 1; i <= N; i++) {
        ans[i] = 0;
        rngs[i] = {0, 0, 0, 0, (int) INF};
    }
}

int main() {
    // freopen("tc.in", "r", stdin);
    // freopen("tc.out", "w", stdout);
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    int T;
    // T = 1;
    cin >> T;
    // T = "change";
    while (T--) solve();

    return 0;
} 