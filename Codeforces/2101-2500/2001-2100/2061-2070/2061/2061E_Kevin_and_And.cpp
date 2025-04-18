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
int N, M, K;
int arr[MAXN];
int spells[20];
vector<int> dagenham[20];
deque<int> dock[MAXN];

void solve() {
    cin >> N >> M >> K;
    for (int i = 1; i <= N; i++) cin >> arr[i];
    for (int i = 1; i <= M; i++) cin >> spells[i];

    for (int i = 1; i <= N; i++) dock[i].resize(M + 1);

    for (int i = 1; i < (1 << M); i++) {
        int n = (1 << 30) - 1;
        for (int j = 0; j < M; j++) if ((1 << j) & i) n &= spells[j + 1];
        dagenham[__builtin_popcount(i)].pb(n);
    }

    for (int i = 1; i <= N; i++) {
        int grays = 0;
        for (int c = 1; c <= M; c++) {
            for (int n : dagenham[c]) dock[i][c - 1] = max(dock[i][c - 1], arr[i] - (arr[i] & n));
            if (c > 1) dock[i][c - 1] -= grays;
            grays += dock[i][c - 1];
        }
    }

    // for (int i = 1; i <= N; i++) {
    //     for (int c = 1; c <= M; c++) {
    //         cout << dock[i][c - 1] << " ";
    //     }
    //     cout << endl;
    // }

    ll ans = 0;
    for (int i = 1; i <= N; i++) ans += arr[i];

    multiset<pii, greater<pii>> chooser;
    for (int i = 1; i <= N; i++) chooser.insert(pii(dock[i][0], i));
    while (K-- && !chooser.empty()) {
        pii n = *chooser.begin();
        chooser.erase(chooser.begin());

        ans -= n.FF;
        dock[n.SS].pop_front();
        if (!dock[n.SS].empty()) chooser.insert(pii(dock[n.SS].front(), n.SS));
    }
    
    cout << ans << endl;

    for (int i = 1; i <= N; i++) {
        arr[i] = 0;
        dock[i].clear();
    }
    for (int i = 1; i <= M; i++) {
        spells[i] = 0;
        dagenham[i].clear();
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