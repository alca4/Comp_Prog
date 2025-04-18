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

const int MAXN = 200010;
extern vector<int> nbs[MAXN];

struct LCA {
    vector<int> in, out, depth;
    vector<int> lift[32];
    int T = 0;

    LCA() {LCA(0);}
    LCA(int n) {
        in.resize(n + 1);
        out.resize(n + 1);
        depth.resize(n + 1);
        for (int i = 0; i < 32; i++) lift[i].resize(n + 1);

        out[0] = 2 * n + 1;
        if (n) tour(1, 0);
    }

    void tour(int a, int p) {
        depth[a] = depth[p] + 1;

        lift[0][a] = p;
        for (int j = 1; j < 32; j++) 
            lift[j][a] = lift[j - 1][lift[j - 1][a]];
        
        in[a] = ++T;
        for (int nb : nbs[a]) if (nb != p) tour(nb, a);
        out[a] = ++T;
    }
    bool is_anc(int a, int b) {return in[a] <= in[b] && out[b] <= out[a];}
    int lca(int a, int b) {
        if (is_anc(a, b)) return a;
        if (is_anc(b, a)) return b;

        for (int i = 31; i >= 0; i--) 
            if (!is_anc(lift[i][a], b)) a = lift[i][a];
                
        return lift[0][a];
    }
};

struct VT{
    vector<int> key;
    vector<int> key_nodes;
    vector<int> extras;
    vector<vector<int>> vnbs;
    LCA lca;
    int root = 0;

    vector<ll> dp, latent;

    VT() {VT(0);}
    VT(int n) {
        key.resize(n + 1);
        vnbs.resize(n + 1);
        dp.resize(n + 1);
        latent.resize(n + 1);
        lca = LCA(n);
    }

    void setup_virtual_tree(const vector<int>& kn) {
        key_nodes = kn;
        sort(key_nodes.begin(), key_nodes.end(), [this](const int& a, const int& b) -> bool {
            return lca.in[a] < lca.in[b];
        });
    
        for (int n : key_nodes) key[n] = 1;

        vector<int> chain;
        chain.pb(key_nodes[0]);

        for (int j = 1; j < key_nodes.size(); j++) {
            int c = lca.lca(chain.back(), key_nodes[j]);

            while (chain.size() > 1 && lca.depth[c] <= lca.depth[chain[chain.size() - 2]]) {
                vnbs[chain[chain.size() - 2]].pb(chain[chain.size() - 1]);
                chain.pop_back();
            }

            if (!key[c]) {
                vnbs[c].pb(chain.back());
                chain.pop_back();
                chain.pb(c);
                extras.pb(c);
                key[c] = 2;
            }

            chain.pb(key_nodes[j]);
        }

        while (chain.size() > 1) {
            int x = chain.back();
            chain.pop_back();
            vnbs[chain.back()].pb(x);
        }
        
        for (int n : key_nodes) if (!root || lca.is_anc(n, root)) root = n;
        for (int n : extras) if (!root || lca.is_anc(n, root)) root = n;

        chain.pop_back();
    }

    ll count(int n) {
        if (key[n] == 1) {
            // cout << n << " real" << endl;
            for (int nb : vnbs[n]) {
                dp[n] += count(nb);

                if (key[nb] == 1) dp[n]++;
                else dp[n] += latent[nb];
            }
        }
        else {
            // cout << n << " fake" << endl;
            ll keys = 0;
            for (int nb : vnbs[n]) {
                dp[n] += count(nb);
                latent[n] += latent[nb];

                if (key[nb] == 1) keys++;
            }
            dp[n] += 1ll * keys * (keys - 1) / 2;

            ll interlatent = 0;
            for (int nb : vnbs[n]) {
                if (key[nb] == 2) {
                    dp[n] += 1ll * keys * latent[nb];
                    interlatent += 1ll * latent[nb] * (latent[n] - latent[nb]);
                }
            }
            dp[n] += interlatent / 2;

            latent[n] += keys;
        }

        return dp[n];
    }

    void clear_virtual_tree() {
        for (int i : key_nodes) {
            vnbs[i].clear();
            dp[i] = latent[i] = key[i] = 0;
        }

        for (int i : extras) {
            vnbs[i].clear();
            dp[i] = latent[i] = key[i] = 0;
        }

        extras.clear();
        key_nodes.clear();
        root = 0;
    }
};

int N;
vector<int> nbs[MAXN];
vector<int> nodesets[MAXN];
VT vt;

void reset_tc() {
    vt = VT(0);
    for (int i = 1; i <= N; i++) {
        nbs[i].clear();
        nodesets[i].clear();
    }
}

void solve() {
    cin >> N;
    for (int i = 1; i <= N; i++) {
        int n;
        cin >> n;
        nodesets[n].pb(i);
    }

    for (int i = 1; i < N; i++) {
        int a, b;
        cin >> a >> b;
        nbs[a].pb(b);
        nbs[b].pb(a);
    }

    vt = VT(N);

    ll ans = 0;
    for (int i = 1; i <= N; i++) if (nodesets[i].size() > 1) {
        vt.setup_virtual_tree(nodesets[i]);

        // for (int n : vt.key_nodes) {
        //     cout << "real " << n << ": ";
        //     for (int nb : vt.vnbs[n]) cout << nb << " ";
        //     cout << endl;
        // }

        // for (int n : vt.extras) {
        //     cout << "fake " << n << ": ";
        //     for (int nb : vt.vnbs[n]) cout << nb << " ";
        //     cout << endl;
        // }
        // cout << endl;

        // cout << vt.root << endl;
        ans += vt.count(vt.root);
        
        vt.clear_virtual_tree();
    }

    cout << ans << endl;

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