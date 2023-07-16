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
ll MOD = 998244353;

typedef pair<int, int> pii;
typedef pair<ll, ll> pll;
typedef complex<ld> cd;

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
template<class X, class Y> void maxeq(X &x, Y y) {if (x < y) x = y;}
template<class X, class Y> void mineq(X &x, Y y) {if (x > y) x = y;}
template<class X, class Y> void addeq(X &x, Y y) {x = add(x, y);}
template<class X, class Y> void subeq(X &x, Y y) {x = sub(x, y);}
template<class X, class Y> void multeq(X &x, Y y) {x = mult(x, y);}
template<class X, class Y> void diveq(X &x, Y y) {x = divide(x, y);}

const int MAXN = 1000010;
int N, K;

int arr[MAXN];
int col[MAXN];

vector<int> chains, cycles;
vector<int> nodes;

void DFS(int a, int c) {
    nodes.pb(a);
    if (col[a]) {
        if (col[a] != c) return;
        int cyc = 1;
        nodes.pop_back();
        while (nodes.back() != a) {
            cyc++;
            nodes.pop_back();
        }
        nodes.pop_back();
        cycles.pb(cyc);
        return;
    }

    col[a] = c;
    DFS(arr[a], c);
}

int cnt[MAXN];

int SolveMin() {
    int sz = (1 << (32 - __builtin_clz(K + K - 1)));

    int tmp = K;
    for (int n : cycles) {
        cnt[n]++;
    }

    bitset<MAXN> zero;
    zero[0] = 1;
    for (int i = 1; i <= N; i++) if (cnt[i]) {
        bitset<MAXN> thing;
        for (int j = 0; j < cnt[i]; j++) thing[j * i] = 1;
    }

    vector<cd> ans;
    ans.pb(1);
    ans.resize(sz);
    dft(ans, 0);

    for (int i = 1; i <= N; i++) if (cnt[i]) {
        dft(polys[i], 0);
        for (int j = 0; j <= K; j++) ans[j] *= polys[i][j];
        ans.resize(sz);
    }

    dft(ans, 1);
    // for (int j = 0; j <= K; j++) cout << ans[j] << " ";
    // cout << endl;
    return K + 1 - (ans[K].real() > 0.5);
}

int SolveMax() {
    int tmp = K;
    int ans = 0;
    for (int i = 0; i < cycles.size(); i++) {
        ans += min(tmp, cycles[i] / 2) * 2;
        tmp -= min(tmp, cycles[i] / 2);
    }
    for (int i = 0; i < cycles.size(); i++) if (cycles[i] % 2 && tmp) {
        ans++;
        tmp--;
    }
    return ans;
}

int main() {
    // freopen("tc.in", "r", stdin);
    // freopen("tc.out", "w", stdout);
    srand(time(NULL));
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    cin >> N >> K;
    for (int i = 1; i <= N; i++) cin >> arr[i];

    int c = 0;
    for (int i = 1; i <= N; i++) if (!col[i]) DFS(i, ++c);

    sort(cycles.begin(), cycles.end());

    cout << SolveMin() << " " << SolveMax() << endl;

    return 0;
}