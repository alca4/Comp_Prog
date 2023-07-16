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

const int MAXN = 510;
int N, M;

int dp[MAXN][10010];
int previous[MAXN][10010];

struct App {
    int d, s, id;   
} apps[MAXN];

bool Comp(const App& p1, const App& p2) {
    if (p1.s + max(p2.d, p2.s) < p2.s + max(p1.d, p2.s)) return 1;
    else return 0;
}

int main() {
    // freopen("tc.in", "r", stdin);
    // freopen("tc.out", "w", stdout);
    srand(time(NULL));
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    cin >> N >> M;
    for (int i = 1; i <= N; i++) {
        cin >> apps[i].d >> apps[i].s;
        apps[i].id = i;
    }

    sort(apps + 1, apps + 1 + N, Comp);

    dp[0][0] = 1;
    for (int i = 0; i < N; i++) for (int j = 0; j <= M; j++) {
        if (dp[i][j]) {
            if (j + max(apps[i + 1].d, apps[i + 1].s) <= M && 
                dp[i + 1][j + apps[i + 1].s] < dp[i][j] + 1) {
                dp[i + 1][j + apps[i + 1].s] = dp[i][j] + 1;
                previous[i + 1][j + apps[i + 1].s] = j;
            }
            if (dp[i + 1][j] < dp[i][j]) {
                dp[i + 1][j] = dp[i][j];
                previous[i + 1][j] = j;
            }
        }
    }

    int best = 0;
    for (int i = 1; i <= M; i++) {
        if (dp[N][best] < dp[N][i]) best = i;
    }
    
    vector<int> choices;
    for (int i = N - 1; i >= 0; i--) {
        if (previous[i + 1][best] < best) choices.pb(apps[i + 1].id);
        best = previous[i + 1][best];
    }

    cout << choices.size() << endl;
    for (int i = choices.size() - 1; i >= 0; i--) cout << choices[i] << " ";
    if (choices.size()) cout << endl;

    return 0;
} 