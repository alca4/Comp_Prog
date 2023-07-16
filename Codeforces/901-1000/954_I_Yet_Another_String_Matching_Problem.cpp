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

const int MAXN = 125010;
int N;

int reverse(int num, int lg_n) {
    int res = 0;
    for (int i = 0; i < lg_n; i++) {
        if (num & (1 << i)) res |= 1 << (lg_n - 1 - i);
    }
    return res;
}

void dft(vector<cd>& a, bool invert) {
    int n = a.size();
    int lg_n = 0;
    while ((1 << lg_n) < n)
        lg_n++;
 
    for (int i = 0; i < n; i++) {
        if (i < reverse(i, lg_n)) swap(a[i], a[reverse(i, lg_n)]);
    }
 
    for (int len = 2; len <= n; len <<= 1) {
        double ang = 2 * acos(-1) / len * (invert ? -1 : 1);
        cd wlen = exp(1i * ang);
        for (int i = 0; i < n; i += len) {
            cd w = 1;
            for (int j = 0; j < len / 2; j++) {
                cd u = a[i + j], v = a[i + j + len / 2] * w;
                a[i + j] = u + v;
                a[i + j + len / 2] = u - v;
                w *= wlen;
            }
        }
    }
 
    if (invert) {
        for (cd& x : a)
            x /= n;
    }
}

string S, T;
vector<cd> t[6];
vector<cd> s[6];

int vis[6];
bool nbs[6][6][MAXN];

void DFS(int a, int t) {
    vis[a] = 1;
    for (int i = 0; i < 6; i++) 
        if (!vis[i] && (nbs[a][i][t] || nbs[i][a][t])) {
            DFS(i, t);
        }
}

int main() {
    // freopen("tc.in", "r", stdin);
    // freopen("tc.out", "w", stdout);
    srand(time(NULL));
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    cin >> S >> T;
    int totsz = 32 - __builtin_clz(S.length() + T.length() - 1);
    N = (1 << totsz);

    for (int i = 0; i < 6; i++) {
        for (int k = 0; k < T.length(); k++) {
            if (T[T.length() - 1 - k] == 'a' + i) t[i].pb(1);
            else t[i].pb(0);
        }
        for (int k = 0; k < S.length(); k++) {
            if (S[k] == 'a' + i) s[i].pb(1);
            else s[i].pb(0);
        }

        s[i].resize(N);
        t[i].resize(N);
    }

    for (int i = 0; i < 6; i++) dft(s[i], 0);
    for (int i = 0; i < 6; i++) dft(t[i], 0);
    
    for (int i = 0; i < 6; i++) for (int j = 0; j < 6; j++) if (i != j) {
        vector<cd> tmp(N);
        for (int k = 0; k < N; k++) {
            tmp[k] = s[i][k] * t[j][k];
        }
        dft(tmp, 1);
        int v = T.length() - 1;
        for (int k = v; k < S.length(); k++) {
            if (abs(tmp[k].real()) > 0.5) {
                nbs[i][j][k - v] = 1;
                nbs[j][i][k - v] = 1;
            }
        }
    }
    
    for (int i = 0; i <= S.length() - T.length(); i++) {
        int c = 0;
        for (int j = 0; j < 6; j++) if (!vis[j]) {
            DFS(j, i);
            c++;
        }
        cout << 6 - c << " ";

        for (int j = 0; j < 6; j++) vis[j] = 0;
    }
    cout << endl;

    return 0;
} 