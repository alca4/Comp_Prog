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

const int MAXN = 200010;
int N;
int arr[MAXN];
string str;
map<int, int> occ;
vector<int> cand;
int pow10[5] = {1, 10, 100, 1000, 10000};

void solve() {
    cin >> str;
    N = str.length();
    for (int i = 0; i < str.length(); i++) {
        arr[i] = str[i] - 'A';
    }

    ll ans = -LINF;
    for (int i = 0; i < N; i++) {
        if (occ.count(arr[i]) == 0) cand.pb(i);
        occ[arr[i]]++;
    }

    for (int n : cand) {
        int t = arr[n];
        for (int aah = 0; aah < 5; aah++) {
            occ.clear();
            arr[n] = aah;
            ll tans = 0;
            for (int j = N - 1; j >= 0; j--) {
                int pos = 1;
                for (int k = arr[j] + 1; k < 5; k++) if (occ.count(k)) pos = -1;
                tans += pos * pow10[arr[j]];
                occ[arr[j]]++;
            }
            arr[n] = t;
            ans = max(ans, tans);
        }
    }
    
    cout << ans << endl;
    occ.clear();
    for (int i = 0; i < N; i++) arr[i] = 0;
    str.clear();
    cand.clear();
}

int main() {
    // freopen(".in", "r", stdin);
    // freopen(".out", "w", stdout);
    srand(time(NULL));
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    int T;
    cin >> T;
    while (T--) solve();

    return 0;
} 