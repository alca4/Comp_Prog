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

const int MAXN = 0;
int N;
string str;

void solve() {
    cin >> str;
    map<char, int> freq;
    for (int i = 0; i < str.length(); i++) freq[str[i]]++;

    string f, b;
    for (auto c = freq.begin(); c != freq.end(); ++c) {
        while (freq[c->FF] >= 2) {
            f += c->FF;
            b += c->FF;
            freq[c->FF] -= 2;
        }
        if (freq[c->FF]) {
            auto nxt = ++c;
            --c;
            if (++nxt == freq.end()) {
                --nxt;
                for (int i = 0; i < freq[nxt->FF] / 2; i++) b += nxt->FF;
                for (int i = 0; i < freq[nxt->FF] - freq[nxt->FF] / 2; i++) f += nxt->FF;
                b += c->FF;
            }
            else {
                b += c->FF;
                ++c;
                for (; c != freq.end(); c++) 
                    for (int i = 0; i < freq[c->FF]; i++) f += c->FF;
            }
            break;
        }
    }

    for (int i = 0; i < f.length(); i++) cout << f[i];
    for (int i = b.length() - 1; i >= 0; i--) cout << b[i];
    cout << endl;
    freq.clear();
    str.clear();
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