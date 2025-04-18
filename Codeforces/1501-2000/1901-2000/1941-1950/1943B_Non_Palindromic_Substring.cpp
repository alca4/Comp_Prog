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
#define endl "\n"
#define EPS 1e-9
// #define cout cerr
ll INF = 1000000000;
ll LINF = 1000000000000000000;
ll MOD = 100000007;
ll MOD2 = 998244353;

typedef pair<int, int> pii;
typedef pair<ll, ll> pll;
typedef complex<ld> cd;

ll add(const ll& a, const ll& b) {return (a + b) % MOD;}
ll sub(const ll& a, const ll& b) {return (a - b + MOD) % MOD;}
ll mult(const ll& a, const ll& b) {return (a * b) % MOD;}
ll power(ll a, ll b, ll mod = MOD) {
    ll n = a;
    ll ans = 1;

    for (int i = 0; i < 32; i++) {
        if (b & 1) ans = (ans * n) % mod;
        n = (n * n) % mod;
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
int N, Q;
set<pii> seq1;
set<pii> seq2;
pll fhash[MAXN];
pll rhash[MAXN];
pll hmult[MAXN];

void reset_tc() {
    for (int i = 1; i <= N; i++) fhash[i] = rhash[i] = hmult[i] = pll(0, 0);
    seq1.clear();
    seq2.clear();
}

void solve() {
    cin >> N >> Q;
    string str;
    cin >> str;

    for (int i = 0; i < N; i++) {
        int j = i + 1;
        while (j < N && str[j] == str[i]) j++;
        j--;
        
        // cout << i << " " << j + 1 << endl;
        seq1.insert(pii(i + 1, j + 1));
        i = j;
    }

    for (int i = 1; i < N; i++) {
        int j = i + 1;
        while (j < N && str[j] == ((i % 2) != (j % 2) ? str[i - 1] : str[i])) j++;
        j--;
        
        if (j != i) seq2.insert(pii(i, j + 1));
        i = j;
    }

    hmult[0] = pll(1, 1);
    for (int i = 1; i <= N; i++) {
        fhash[i] = pll((fhash[i - 1].FF + (str[i - 1] - 'a') * hmult[i - 1].FF) % MOD,
                       (fhash[i - 1].SS + (str[i - 1] - 'a') * hmult[i - 1].SS) % MOD2);
        rhash[i] = pll((rhash[i - 1].FF + (str[N - i] - 'a') * hmult[i - 1].FF) % MOD,
                       (rhash[i - 1].SS + (str[N - i] - 'a') * hmult[i - 1].SS) % MOD2);
        
        hmult[i] = pll((hmult[i - 1].FF * 26) % MOD, (hmult[i - 1].SS * 26) % MOD2);
    }

    for (int i = 1; i <= N; i++) {
        pll sanity = hmult[i];
        hmult[i] = pll(power(hmult[i].FF, MOD - 2, MOD), power(hmult[i].SS, MOD2 - 2, MOD2));
        // cout << (hmult[i].FF * sanity.FF) % MOD << " " << (hmult[i].SS * sanity.SS) % MOD2 << endl;
    }

    // cout << N << endl;
    // for (pii n : seq) cout << n.FF << " " << n.SS << endl;
    // cout << endl;

    while (Q--) {
        int l, r;
        cin >> l >> r;

        pll maybe = pll(((fhash[r].FF + MOD - fhash[l - 1].FF) * hmult[l - 1].FF) % MOD,
                        ((fhash[r].SS + MOD2 - fhash[l - 1].SS) * hmult[l - 1].SS) % MOD2);
            
        // cout << l << " " << r << endl;
        r = N + 1 - r;
        l = N + 1 - l;
        // cout << l << " " << r << endl;

        pll maybe2 = pll(((rhash[l].FF + MOD - rhash[r - 1].FF) * hmult[r - 1].FF) % MOD,
                         ((rhash[l].SS + MOD2 - rhash[r - 1].SS) * hmult[r - 1].SS) % MOD2);
        
        r = N + 1 - r;
        l = N + 1 - l;
        // cout << l << " " << r << endl;
        
        // cout << maybe.FF << " " << maybe.SS << " " << maybe2.FF << " " << maybe2.SS << endl;

        bool is_palin = (maybe == maybe2);
        bool bad_seq = 0;
        auto it2 = seq2.upper_bound(pii(l, INF));
        if (it2 != seq2.begin()) bad_seq = (--it2)->SS >= r;

        bool really_bad_seq = 0;
        auto it1 = seq1.upper_bound(pii(l, INF));
        if (it1 != seq1.begin()) really_bad_seq = (--it1)->SS >= r;

        if (really_bad_seq) cout << 0 << endl;
        else if (bad_seq) cout << 1ll * ((r - l + 1) / 2 + 1) * ((r - l + 1) / 2) << endl;
        else if (is_palin) cout << 1ll * (r - l + 1) * (r - l) / 2 - 1 << endl;
        else cout << 1ll * (r - l + 2) * (r - l + 1) / 2 - 1 << endl;
    }

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