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

const int MAXN = 100010;
int M;
int sz[MAXN];
vector<ll> nums[MAXN];
vector<ll> freq[MAXN];
map<ll, ll> mp[MAXN];
ll tot_freq[MAXN];
ll l[MAXN], r[MAXN];
map<ll, ll> no_contain;
map<ll, vector<ll>> contains;

void solve() {
    cin >> M;

    for (int i = 1; i <= M; i++) {
        cin >> sz[i] >> l[i] >> r[i];
        for (int j = 0; j < sz[i]; j++) {
            ll n;
            cin >> n;
            nums[i].pb(n);

            no_contain[n] += r[i];
            contains[n].pb(i);
        }

        ll nsum = 0;
        for (int j = 0; j < sz[i]; j++) {
            ll n;
            cin >> n;
            freq[i].pb(n);
            nsum += n;
        }

        for (int j = 0; j < sz[i]; j++) mp[i][nums[i][j]] = freq[i][j];
        tot_freq[i] = nsum;
    }

    ll suml = 0;
    for (int i = 1; i <= M; i++) suml += l[i];
    ll sumr = 0;
    for (int i = 1; i <= M; i++) sumr += r[i];

    for (pll n : no_contain) no_contain[n.FF];

    if (sumr - suml >= contains.size()) cout << 0 << endl;
    else {
        ll ans = LINF;
        for (ll sz = suml; sz <= sumr; sz++) {
            ll have = sumr - no_contain[sz];
            ll tans = 0;
            for (ll n : contains[sz]) {
                tans += max(0ll, l[n] - tot_freq[n] + mp[n][sz]);
                have += max(l[n], min(r[n], tot_freq[n] - mp[n][sz]));
            }
            tans += max(sz - have, 0ll);
            // cout << sz << " " << tans << endl;
            ans = min(ans, tans);
        }
        cout << ans << endl;
    }

    for (int i = 1; i <= M; i++) {
        nums[i].clear();
        freq[i].clear();
        mp[i].clear();
        sz[i] = l[i] = r[i] = tot_freq[i] = 0;
    }
    no_contain.clear();
    contains.clear();
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