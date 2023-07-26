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

const int MAXN = 200010;
int N, C;
int arr[MAXN];
vector<int> freq[MAXN];

void solve() {
    cin >> N >> C;
    for (int i = 1; i <= C; i++) freq[i].pb(0);
    for (int i = 1; i <= N; i++) {
        cin >> arr[i];
        freq[arr[i]].pb(i);
    }
    for (int i = 1; i <= C; i++) freq[i].pb(N + 1);

    int best = N + 1;
    for (int i = 1; i <= C; i++) {
        multiset<int> gaps;
        for (int j = 1; j < freq[i].size(); j++) {
            gaps.insert(freq[i][j] - freq[i][j - 1]);
        }
        int x = *gaps.rbegin();
        gaps.erase(--gaps.end());
        gaps.insert(x / 2);
        gaps.insert(x - x / 2);
        best = min(best, *gaps.rbegin());
    }

    cout << best - 1 << endl;
    for (int i = 1; i <= N; i++) arr[i] = 0;
    for (int i = 1; i <= C; i++) freq[i].clear();
}

int main() {
    // freopen("tc.in", "r", stdin);
    // freopen("tc.out", "w", stdout);
    srand(time(NULL));
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    int T;
    cin >> T;
    while (T--) solve();

    return 0;
} 