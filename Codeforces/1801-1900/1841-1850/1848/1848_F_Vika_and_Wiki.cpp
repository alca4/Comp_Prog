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

const int MAXN = (1 << 20);
int N;
int arr[MAXN];
int arr2[MAXN];

int main() {
    // freopen("tc.in", "r", stdin);
    // freopen("tc.out", "w", stdout);
    srand(time(NULL));
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    cin >> N;
    int logN = 32 - __builtin_clz(N - 1);
    for (int i = 0; i < N; i++) cin >> arr[i];

    int allzero = 1;
    for (int i = 0; i < N; i++) {
        if (arr[i]) allzero = 0;
    }

    if (allzero) {
        cout << 0 << endl;
        return 0;
    }

    int ans = 0;
    for (int i = logN - 1; i >= 0; i--) {
        int nonzero = 0;
        for (int j = 0; j < N; j++) {
            if (arr[j] ^ arr[(j + (1 << i)) % N]) nonzero = 1;
        }

        if (nonzero) {
            ans += (1 << i);
            for (int j = 0; j < N; j++) {
                arr2[j] = arr[j] ^ arr[(j + ans) % N];
            }
            for (int j = 0; j < N; j++) {
                arr[j] = arr2[j];
            }
        }
    }

    cout << ans + 1 << endl;

    return 0;
} 

/*
1 2 1 2     0
3 3 3 3     1
0 0 0 0     2

0 1 2 3 4 5 6 7     1
1 3 1 7 1 3 1 7     2
2 2 6 6 2 2 6 6     3
0 4 0 4 0 4 0 4     4
4 4 4 4 4 4 4 4     5
0 0 0 0 0 0 0 0     6

0 1 2 3 4 5 6       1
1 3 1 7 1 3 6       2
2 2 6 6 2 7 7       3
0 4 0 4 5 0 5       4
4 4 4 1 5 5 5       5
0 0 5 4 0 0 1       6
0 5 1 4 0 1 1       7
5 4 5 4 1 0 1       8
1 1 1 5 1 1 4       9
0 0 4 4 0 5 5       10
0 4 0 4 5 0 5       11
*/