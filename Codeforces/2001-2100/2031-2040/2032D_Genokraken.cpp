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
// #define endl "\n"
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

const int MAXN = 10010;
int N;
int p[MAXN];

void solve() {
    cin >> N;

    queue<int> ducks;

    int i = 2;
    for (; i < N; i++) {
        cout << "? " << 1 << " " << i << endl;
        int res;
        cin >> res;

        if (res == 0) {
            p[i] = 1;
            ducks.push(i);
            i++;
            break;
        }

        p[i] = 0;
        ducks.push(i);
    }

    for (; i < N; i++) {
        if (ducks.size() == 1) {
            p[i] = ducks.front();
            i++;
            break;
        }
        // assert(i != ducks.front());
        cout << "? " << i << " " << ducks.front() << endl;
        int res;
        cin >> res;

        if (res == 0) {
            p[i] = ducks.front();
            ducks.push(i);
            ducks.pop();
        }
        else {
            i--;
            ducks.pop();
        }
    }

    for (; i < N; i++) p[i] = i - 1;

    cout << "! ";
    for (int j = 1; j < N; j++) cout << p[j] << " ";
    cout << endl;

    for (int j = 1; j < N; j++) p[j] = 0;
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