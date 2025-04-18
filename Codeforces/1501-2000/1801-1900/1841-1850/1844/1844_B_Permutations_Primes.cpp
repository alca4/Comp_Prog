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
int N;

int sieve[1000010];
vector<int> primes;
struct NT {
    static void get_primes(int x) {
        sieve[1] = 1;
        for (int i = 2; i <= x; i++) if (!sieve[i]) {
            primes.pb(i);
            for (int j = 2; i * j <= x; j++) sieve[i * j] = 1;
        }
    }

    static vector<pii> factorize(int n) {
        vector<pii> v;
        for (int p : primes) {
            v.pb(pii(p, 0));
            while (n % p == 0) {
                v.back().SS++;
                n /= p;
            }
            if (v.back().SS == 0) v.pop_back();
            else v.back().SS++;
        }
        if (n > 1) v.pb(pii(n, 2));
        return v;
    }

    static int num_div(int n) {
        int x = 1;
        for (pii p : factorize(n)) x *= p.SS;
        return x;
    }

    static vector<int> gen_div(int n) {
        vector<pii> v = factorize(n);
        int x = 1;
        for (pii p : v) x *= p.SS;
        vector<int> divs;
        for (int i = 0; i < x; i++) {
            int t = i;
            int d = 1;
            for (pii p : v) {
                if (t % p.SS) d *= power(p.FF, t % p.SS);
                t /= p.SS;
            }
            divs.pb(d);
        }
        return divs;
    }

    static int modsqrt(int n) {
        n %= MOD;
        if (power(n, (MOD - 1) / 2) == MOD - 1) return -1;
        ll a = 2;
        for (; a < MOD; a++) {
            if (power(sub(mult(a, a), n), (MOD - 1) / 2) == MOD - 1) break;
        }

        pll m = pll(a, 1);
        pll ans = pll(1, 0);

        int b = (MOD + 1) / 2;

        for (int i = 0; i < 32; i++) {
            if (b & 1) {
                ans = pll(add(mult(ans.FF, m.FF), mult(mult(ans.SS, m.SS), sub(mult(a, a), n))),
                        add(mult(ans.FF, m.SS), mult(ans.SS, m.FF)));
            }
            m = pll(add(mult(m.FF, m.FF), mult(mult(m.SS, m.SS), sub(mult(a, a), n))),
                    add(mult(m.FF, m.SS), mult(m.SS, m.FF)));
            b >>= 1;
        }

        return (ans.FF + MOD) % MOD;
    }
};

deque<int> a1;
deque<int> a2;

void solve() {
    cin >> N;
    int p = 0;
    for (int i = 2; i <= N; i++) {
        int divides = 0;
        for (int j = 2; j * j <= i; j++) if (i % j == 0) divides = 1;
        if (!divides) {
            if (p == 0) a1.pb(i);
            else a2.push_front(i);
            p = 1 - p;
        }
        else {
            if (p == 0) a1.push_front(i);
            else a2.pb(i);
            p = 1 - p;
        }
    }
    a1.push_front(1);
    for (int i = 0; i < a2.size(); i++) cout << a2[i] << " ";
    for (int i = 0; i < a1.size(); i++) cout << a1[i] << " ";
    cout << endl;
    a1.clear(), a2.clear();
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