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

extern vector<int> nbs[];

struct Euler {
    int T;
    vector<int> in, out, euler;

    Euler(int n) {
        T = 0;
        in.resize(n + 1);
        out.resize(n + 1);
        euler.resize(n * 2 + 1);
    }

    ~Euler() {
        T = 0;
        in.clear();
        out.clear();
        euler.clear();
    }

    void tour(int a, int p) {
        in[a] = ++T;
        euler[T] = a;
        for (int nb : nbs[a]) if (nb != p) tour(nb, a);
        out[a] = ++T;
        euler[T] = -a;
    }

    bool childOf(int a, int b) {
        return (in[b] <= in[a] && out[a] <= out[b]);
    }
};

const int MAXN = 400010;
int N;
int w[MAXN];
vector<int> nbs[MAXN];
set<int, greater<int>> wvs;
vector<int> freq[MAXN];
Euler et = Euler(0);

void reset_tc() {
    for (int i = 1; i <= N; i++) {
        w[i] = 0;
        nbs[i].clear();
        freq[i].clear();
    }
    wvs.clear();
    et = Euler(0);
}

bool Comp(int a, int b) {
    return et.in[a] > et.in[b];
}

void solve() {
    cin >> N;
    for (int i = 1; i <= N; i++) {
        cin >> w[i];
        wvs.insert(w[i]);
        freq[w[i]].pb(i);
    }

    for (int i = 1; i < N; i++) {
        int a, b;
        cin >> a >> b;
        nbs[a].pb(b);
        nbs[b].pb(a);
    }

    et = Euler(N);
    et.tour(1, 0);

    for (int i = 1; i <= N; i++) 
        sort(freq[i].begin(), freq[i].end(), Comp);
    
    // for (int i = 1; i <= N; i++) {
    //     for (int n : freq[i]) cout << n << " ";
    //     cout << endl;
    // }

    auto right = wvs.begin();
    auto left = right;
    right++;
    while (right != wvs.end()) {
        if (freq[*right].size() > 1) {
            int cnt = 0;
            for (int n : freq[*left]) {
                if (et.childOf(n, freq[*right][0])) cnt++;
            }
            // cout << cnt << endl;

            int non_child = 0;
            for (int i = 1; i < freq[*right].size(); i++) {
                if (!non_child && !(et.childOf(freq[*right][i - 1], freq[*right][i]))) 
                    non_child = freq[*right][i];
            }

            if (cnt != freq[*left].size()) cout << freq[*right][0] << endl;
            else if (non_child) cout << non_child << endl;
            else {
                left++;
                right++;
                continue;
            }

            reset_tc();
            return;
        }
        else {
            int cnt = 0;
            for (int n : freq[*left]) {
                if (et.childOf(n, freq[*right][0])) cnt++;
            }
            // cout << cnt << endl;

            if (cnt < freq[*left].size()) {
                cout << freq[*right][0] << endl;
                reset_tc();
                return;
            }
        }

        left++;
        right++;
    }
    cout << 0 << endl;

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