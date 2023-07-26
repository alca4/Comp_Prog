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

    while (b) {
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
int X, Q;

vector<int> primes;
vector<int> sieve;
struct NT {
    static void get_primes(int x) {
        sieve.resize(x + 1);
        sieve[1] = 1;
        for (int i = 2; i <= x; i++) if (!sieve[i]) {
            primes.pb(i);
            for (int j = 2; i * j <= x; j++) sieve[i * j] = 1;
        }
    }

    static vector<pii> factorize(int n) {
        vector<pii> v;
        for (int p : primes) {
            if (p > n) break;
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
        vector<int> divs;
        for (int i = 0; i < num_div(n); i++) {
            int t = i;
            int d = 1;
            for (pii p : v) {
                if (t % p.SS) d *= power(p.FF, t % p.SS);
                t /= p.SS;
            }
            divs.pb(d);
        }
        sort(divs.begin(), divs.end());
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

ll ans = 1;
int cnt[MAXN];
int inv[MAXN * 2];
int zeros = 0;

int main() {
    // freopen("tc.in", "r", stdin);
    // freopen("tc.out", "w", stdout);
    srand(time(NULL));
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    cin >> X >> Q >> MOD;

    for (int i = 1; i <= 1300000; i++) inv[i] = divide(1, i);

    NT::get_primes(1000);
    while (X % 2 == 0) X /= 2;
    for (int n : primes) if (X >= n && X % n == 0) {
        // cout << a << " " << n << " ";
        if (cnt[n] + 1 == MOD) zeros--;
        else ans *= inv[cnt[n] + 1];
        ans %= MOD;

        int in_num = 0;
        while (X % n == 0) {
            in_num++;
            X /= n;
        }
        cnt[n] += in_num;
        cnt[n] %= MOD;
        
        if (cnt[n] + 1 == MOD) zeros++;
        else ans *= cnt[n] + 1;
        ans %= MOD;
    }
    if (X != 1) {
        for (int i = 1001; i <= 1000000; i += 2) if (X >= i && X % i == 0) {
            int in_num = 0;
            while (X % i == 0) {
                in_num++;
                X /= i;
            }
            cnt[i] += in_num;
            cnt[i] %= MOD;

            if (cnt[i] + 1 == MOD) zeros++;
            else ans *= cnt[i] + 1;
            ans %= MOD;
        }

        if (X != 1) {
            ans *= 2;
            ans %= MOD;
        }
    }

    while (Q--) {
        int a;
        cin >> a;
        
        while (a % 2 == 0) a /= 2;
        for (int n : primes) if (a >= n && a % n == 0) {
            // cout << a << " " << n << " ";
            if (cnt[n] + 1 == MOD) zeros--;
            else ans *= inv[cnt[n] + 1];
            ans %= MOD;

            int in_num = 0;
            while (a % n == 0) {
                in_num++;
                a /= n;
            }

            cnt[n] += in_num;
            cnt[n] %= MOD;
            
            if (cnt[n] + 1 == MOD) zeros++;
            else ans *= cnt[n] + 1;
            ans %= MOD;
        }

        if (a != 1) {
            if (cnt[a] + 1 == MOD) zeros--;
            else ans *= inv[cnt[a] + 1];
            ans %= MOD;

            cnt[a]++;
            cnt[a] %= MOD;

            if (cnt[a] + 1 == MOD) zeros++;
            else ans *= cnt[a] + 1;
            ans %= MOD;
        }

        cout << (zeros ? 0 : ans) << endl;
    }

    return 0;
} 