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

const int MAXN = 300010;

int sieve[1000010];
vector<int> primes;
map<int, int> prime_id;
struct NumberTheory {
        
    static void get_primes(int x) {
        sieve[1] = 1;
        for (int i = 2; i <= x; i++) if (!sieve[i])
        {
            primes.pb(i);
            prime_id[i] = primes.size();
            for (int j = 2; i * j <= x; j++) sieve[i * j] = 1;
        }
    }

    static vector<pii> factorize(int x) {
        vector<pii> v;
        int x0 = x;
        for (int i = 0; i < primes.size(); i++) {
            if (1ll * primes[i] * primes[i] > 1ll * x) break;
            v.pb(pii(primes[i], 0));
            while (x % primes[i] == 0) {
                v.back().SS++;
                x /= primes[i];
            }
            if (v.back().SS == 0) v.pop_back();
        }
        if (x != 1) v.pb(pii(x, 1));
        return v;
    }

    static vector<int> gen_div(int x) {
        vector<pii> v = factorize(x);
        int nd = 1;
        for (pii p : v) nd *= p.SS + 1;

        vector<int> divs;
        for (int i = 0; i < nd; i++) {
            int t = i;
            int d = 1;
            for (pii p : v) {
                if (t % (p.SS + 1)) d *= power(primes[p.FF], t % (p.SS + 1));
                t /= p.SS + 1;
            }
            divs.pb(d);
        }
        return divs;
    }

    static ll pollard(ll a) {
        MOD = a;
        ll div = -1;
        for (int g = 2; g <= 10; g++) {
            ll x = g;
            ll y = 2;
            ll d = 1;
            
            while (d == 1) {
                x = add(mult(x, x), 1);
                y = add(mult(y, y), 1);
                y = add(mult(y, y), 1);
                d = gcd(a, abs(x - y));
            }

            if (d != a) {
                div = d;
                break;
            }
        }
        return div;
    }
};

int N;
vector<int> nbs[2 * MAXN];
ll dist[2 * MAXN];
int vis[2 * MAXN];
int before[2 * MAXN];

int main() {
    // freopen("tc.in", "r", stdin);
    // freopen("tc.out", "w", stdout);
    srand(time(NULL));
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    NumberTheory::get_primes(300000);

    cin >> N;
    int S, T;
    for (int i = 1; i <= N; i++) {
        int n;
        cin >> n;
        vector<pii> vec = NumberTheory::factorize(n);
        for (pii p : vec) {
            nbs[prime_id[p.FF] + N].pb(i);
            nbs[i].pb(prime_id[p.FF] + N);
        }
    }

    for (int i = 1; i <= 600000; i++) dist[i] = LINF;
    cin >> S >> T;
    
    deque<pll> pq;
    dist[S] = 0;
    pq.pb(pll(0, S));
    while (!pq.empty()) {
        ll d = pq.front().FF;
        int n = pq.front().SS;
        pq.pop_front();

        if (n == T) break;

        if (vis[n]) continue;
        vis[n] = 1;

        for (int nb : nbs[n]) {
            int w = (nb <= N ? 0 : 1);
            if (dist[nb] > dist[n] + w) {
                dist[nb] = dist[n] + w;
                before[nb] = n;
                
                if (!vis[nb]) {
                    if (w == 0) pq.push_front({dist[nb], nb});
                    else pq.push_back({dist[nb], nb});
                }
            }
        }
    }

    if (dist[T] != LINF) {
        cout << dist[T] + 1 << endl;
        int t = T;
        stack<int> a;
        int ops = 0;
        while (t != S) {
            if (t <= N) a.push(t);
            t = before[t];
            ops++;
        }
        a.push(t);
        while (!a.empty()) {
            cout << a.top() << " ";
            a.pop();
        }
        cout << endl;
    }
    else cout << -1 << endl;

    return 0;
} 