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
ll binexp[32];
ll power(ll a, ll b)
{
    ll n = b;
    ll ans = 1;

    binexp[0] = a;
    for (int i = 1; i < 32; i++) binexp[i] = mult(binexp[i - 1], binexp[i - 1]);

    while (n > 0)
    {
        int id = __builtin_ctz(n & -n);
        ans = mult(ans, binexp[id]);
        n -= (n & -n);
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

const int MAXN = 100010;
int N, M;

int vis[MAXN];
int in_stack[MAXN];
vector<int> nbs[MAXN];

deque<int> nodes;
int DFS(int a) {
    if (vis[a] && !in_stack[a]) return 0;
    nodes.pb(a);
    if (in_stack[a]) return 1;
    in_stack[a] = 1;
    vis[a] = 1;
    for (int nb : nbs[a]) {
        if (DFS(nb)) return 1;
    }
    in_stack[a] = 0;
    nodes.pop_back();
    return 0;
}

int main() {
    // freopen("tc.in", "r", stdin);
    // freopen("tc.out", "w", stdout);
    srand(time(NULL));
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    cin >> N >> M;
    for (int i = 1; i <= M; i++) {
        int a, b;
        cin >> a >> b;
        nbs[a].pb(b);
    }

    int has_ans = 0;
    for (int i = 1; i <= N; i++) if (!vis[i]) {
        if (DFS(i) && !has_ans) {
            // cerr << "answer found!" << endl;
            while (nodes.front() != nodes.back()) nodes.pop_front();
            cout << nodes.size() << endl;
            for (int n : nodes) cout << n << " ";
            cout << endl;
            has_ans = 1;
        }
    }

    if (!has_ans) cout << "IMPOSSIBLE" << endl;

    return 0;
} 