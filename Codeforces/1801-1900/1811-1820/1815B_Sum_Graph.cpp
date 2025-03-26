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

Tooting Bec
*/
#include <bits/stdc++.h>
using namespace std;

#define FF first
#define SS second
#define pb push_back
#define ll long long
#define ld long double
#define ull unsigned ll
// #define endl "\n"
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

const int MAXN = 1010;
int N;
int dist[MAXN];
int loc[MAXN];
int ans1[MAXN];
int ans2[MAXN];

void reset_tc() {
    for (int i = 1; i <= N; i++) ans1[i] = ans2[i] = dist[i - 1] = 0;
}

void solve() {
    cin >> N;

    cout << "+ " << N + 1 << endl;
    int ok;
    cin >> ok;
    assert(ok != -2);

    cout << "+ " << N + 2 << endl;
    cin >> ok;
    assert(ok != -2);

    int maximal = 0;
    int maxi = 0;
    for (int i = 2; i <= N; i++) {
        cout << "? " << 1 << " " << i << endl;

        int v;
        cin >> v;
        assert(v != -2);
        dist[v + 1] = i;
        if (v > maximal) {
            maxi = i;
            maximal = v;
        }
    }
    
    if (maximal < N - 1) {
        for (int i = 1; i <= N; i++) if (i != maxi) {
            cout << "? " << maxi << " " << i << endl;

            int v;
            cin >> v;
            assert(v != -2);
            dist[v + 1] = i;
        }
    }
    else maxi = 1;

    int l = 1, r = N;
    for (int i = 1; i <= N; i++) {
        if (i % 2) loc[i] = l++;
        else loc[i] = r--;
    }

    dist[1] = maxi;
    // for (int i = 1; i <= N; i++) cout << loc[i] << " ";
    // cout << endl;
    // for (int i = 1; i <= N; i++) cout << dist[i] << " ";
    // cout << endl;

    for (int i = 1; i <= N; i++) {
        ans1[dist[i]] = loc[i];
        ans2[dist[i]] = loc[N + 1 - i];
    }

    cout << "!";
    for (int i = 1; i <= N; i++) cout << " " << ans1[i];
    for (int i = 1; i <= N; i++) cout << " " << ans2[i];
    cout << endl;

    cin >> ok;
    assert(ok != -2);

    reset_tc();
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