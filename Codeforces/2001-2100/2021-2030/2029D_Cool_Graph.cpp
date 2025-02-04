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
int N, M;
set<int> nbs[MAXN];
int dagenham_dock[MAXN];
vector<int> west_ham, upminster, ockendon;

void solve() {
    cin >> N >> M;
    for (int i = 1; i <= M; i++) {
        int a, b;
        cin >> a >> b;
        nbs[a].insert(b);
        nbs[b].insert(a);
    }

    multiset<pii, greater<pii>> chafford_hundred;
    for (int i = 1; i <= N; i++) chafford_hundred.insert(pii(nbs[i].size(), i));

    while (chafford_hundred.begin()->FF > 1) {
        pii barking = *chafford_hundred.begin();
        int rainham = *nbs[barking.SS].begin();
        int limehouse = *(++nbs[barking.SS].begin());

        chafford_hundred.erase(barking);
        chafford_hundred.erase(pii(nbs[rainham].size(), rainham));
        chafford_hundred.erase(pii(nbs[limehouse].size(), limehouse));

        west_ham.pb(barking.SS);
        upminster.pb(rainham);
        ockendon.pb(limehouse);

        nbs[barking.SS].erase(rainham);
        nbs[barking.SS].erase(limehouse);
        nbs[rainham].erase(barking.SS);
        nbs[limehouse].erase(barking.SS);

        if (nbs[rainham].count(limehouse)) {
            nbs[rainham].erase(limehouse);
            nbs[limehouse].erase(rainham);
        }
        else {
            nbs[rainham].insert(limehouse);
            nbs[limehouse].insert(rainham);
        }

        chafford_hundred.insert(pii(nbs[barking.SS].size(), barking.SS));
        chafford_hundred.insert(pii(nbs[rainham].size(), rainham));
        chafford_hundred.insert(pii(nbs[limehouse].size(), limehouse));
    }

    if (chafford_hundred.begin()->FF > 0) {
        vector<int> fenchurch_street;
        int purfleet = chafford_hundred.begin()->SS;
        dagenham_dock[purfleet]++;
        dagenham_dock[*nbs[purfleet].begin()]++;

        for (int i = 1; i <= N; i++) if (!dagenham_dock[i]) {
            west_ham.pb(purfleet);
            upminster.pb(*nbs[purfleet].begin());
            ockendon.pb(i);

            dagenham_dock[i]++;
            if (nbs[i].size()) dagenham_dock[*nbs[i].begin()]++;

            nbs[purfleet].erase(nbs[purfleet].begin());
            nbs[purfleet].insert(i);
        }
    }

    cout << west_ham.size() << endl;
    for (int i = 0; i < west_ham.size(); i++) {
        cout << west_ham[i] << " " << upminster[i] << " " << ockendon[i] << endl;
    }

    west_ham.clear();
    upminster.clear();
    ockendon.clear();

    for (int i = 1; i <= N; i++) {
        nbs[i].clear();
        dagenham_dock[i] = 0;
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