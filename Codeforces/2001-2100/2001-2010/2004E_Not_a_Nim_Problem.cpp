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

Tooting Bec
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

const int MAXN = 300010;

struct NT {
    vector<int> primes;
    vector<int> sieve;
    // vector<vector<int>> divisors;
    // vector<vector<pii>> factorization;

    NT(int x) {
        sieve.resize(x + 1);

        for (int i = 2; i <= x; i++) if (!sieve[i]) {
            primes.pb(i);
            for (int j = 1; i * j <= x; j++) if (sieve[i * j] < 2) sieve[i * j] = primes.size();
        }

        // divisors.resize(x + 1);
        // for (int i = 2; i <= x; i++) {
        //     if (!sieve[i]) {
        //         divisors[i].pb(1);
        //         divisors[i].pb(i);
        //     }
        //     else {
        //         divisors[i] = divisors[i / sieve[i]];
        //         for (int n : divisors[i / sieve[i]]) if ((i / sieve[i] / n) % sieve[i]) {
        //             divisors[i].pb(n * sieve[i]);
        //         }
        //     }
        // }

        // for (int i = 2; i <= x; i++) {
        //     if (!sieve[i]) factorization[i].pb(pii(i, 1));
        //     else {
        //         factorization[i] = factorization[i / sieve[i]];
        //         for (int j = 0; j < factorization[i / sieve[i]].size(); j++) {
        //             if (factorization[i / sieve[i]][j].FF == sieve[i]) 
        //                 factorization[i / sieve[i]][j].SS++;
        //         }
        //     }
        // }
    }

    int modsqrt(int n) {
        n %= MOD;
        if (power(n, (MOD - 1) / 2) == MOD - 1) return -1;
        ll a = 2;
        for (; a < MOD; a++) {
            if (power((a * a - n) % MOD, (MOD - 1) / 2) == MOD - 1) break;
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

NT nt(10000000);
int N;

void reset_tc() {

}

void solve() {
    cin >> N;
    int xorsum = 0;
    for (int i = 1; i <= N; i++) {
        int n;
        cin >> n;
        
        if (n % 2 == 0) continue;

        int found_duck = 0;
        for (int j = 3; j * j <= max(n, 9); j += 2) if (found_duck && n % j == 0) {
            found_duck = 1;
            xorsum ^= nt.sieve[j];
        }
        if (!found_duck) {
            if (n == 1) xorsum ^= 1;
            else xorsum ^= nt.sieve[n];
        }
        // cout << xorsum << " ";
    }
    // cout << endl;

    cout << (xorsum ? "Alice" : "Bob") << endl;
    reset_tc();
}

int main() {
    // freopen("tc.in", "r", stdin);
    // freopen("tc.out", "w", stdout);
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    // for (int i = 1; i <= 10; i++) cout << nt.sieve[i] << " ";
    // cout << endl;

    int T;
    // T = 1;
    cin >> T;
    // T = "change";
    while (T--) solve();

    return 0;
} 