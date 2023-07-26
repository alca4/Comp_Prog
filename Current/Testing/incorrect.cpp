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
const int MAXS = 130;
const int S = 125;
int N, K;

int arr[MAXN];
int col[MAXN];

vector<int> chains, cycles;

int p[MAXN], sz[MAXN];
void setup_dsu() {for (int i = 1; i <= N; i++) p[i] = i, sz[i] = 1;}
int root(int a) {return p[a] = (a == p[a] ? a : root(p[a]));}
int combine(int a, int b)
{
    a = root(a), b = root(b);
    if (a == b) return 0;

    if (sz[a] < sz[b]) swap(a, b);
    p[b] = a;
    sz[a] += sz[b];
    return 1;
}

int cnt[MAXN];
bitset<MAXN> dp;

int s[MAXS];
queue<int> modulo[MAXS];

int SolveMin() {
    for (int n : cycles) cnt[n]++;
    dp[0] = 1;
    int ops = 0;
    for (int i = 2; i <= S; i++) if (cnt[i]) {
        for (int j = 0; j <= N; j++) {
            int rem = j % i;
            modulo[rem].push(dp[j]);
            s[rem] += dp[j];
            if (s[rem]) {
                dp[j] = 1;
            }
            if (modulo[rem].size() > cnt[i]) {
                s[rem] -= modulo[rem].front();
                modulo[rem].pop();
            }
        }
        for (int j = 0; j < i; j++) {
            s[j] = 0;
            while (modulo[j].size()) {
                modulo[j].pop();
                ops++;
            }
        }
    }

    // for (int j = 0; j <= K; j++) cout << dp[j];
    // cout << endl;
    
    for (int n : cycles) if (n > S) {
        for (int j = 0; j < cnt[n]; j++) {
            dp = dp | (dp << n);
        }
    }
    return K + 1 - dp[K];
}

int SolveMax() {
    int tmp = K;
    int ans = 0;
    for (int n : cycles) {
        ans += min(tmp, n / 2) * 2;
        tmp -= min(tmp, n / 2);
    }
    for (int n : cycles) if (n % 2 && tmp) {
        ans++;
        tmp--;
    }
    return ans;
}

int main() {
    freopen("tc.in", "r", stdin);
    freopen("tc.out", "w", stdout);
    srand(time(NULL));
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    cin >> N >> K;
    setup_dsu();
    for (int i = 1; i <= N; i++) cin >> arr[i];

    int c = 0;
    for (int i = 1; i <= N; i++) {
        if (!combine(i, arr[i])) cycles.pb(sz[root(i)]);
    }

    sort(cycles.begin(), cycles.end());

    cout << SolveMin() << " " << SolveMax() << endl;

    return 0;
}