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
ll INF = 1000000000;
ll LINF = 1000000000000000000;
ll MOD = LINF;
// ll MOD = 1000000007;
// ll MOD = 998244353;

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
ll power(ll a, ll b)
{
    ll n = b;
    ll ans = 1;

    ll binexp[64];
    binexp[0] = a;
    for (int i = 1; i < 64; i++) binexp[i] = binexp[i - 1] * binexp[i - 1];

    while (n > 0)
    {
        int id = (int) log2(n & -n);
        ans *= binexp[id];
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

int rand32()
{
    int a = rand();
    int b = rand();
    return (a << 16) | b;
}

ll rand64()
{
    ll a = rand32();
    ll b = rand32();
    return (a << 32) | b;
}

const int MAXN = 20;
int N;
ll powt[MAXN];
// ll fact[MAXN], factinv[MAXN];

// ll choose(int a, int b)
// {
//     return mult(fact[a], mult(factinv[b], factinv[a - b]));
// }

// void get_fact(int x)
// {
//     fact[0] = 1;
//     for (int i = 1; i <= x; i++) fact[i] = mult(i, fact[i - 1]);
//     factinv[x] = divide(1, fact[x]);
//     for (int i = x - 1; i >= 0; i--) factinv[i] = mult(factinv[i + 1], i + 1);
// }

int numdigs(ll n)
{
    int c = 0;
    while (n) 
    {
        n /= 10;
        c++;
    }
    return c;
}

int get(ll v, int d)
{
    while (d--) v /= 10;
    return v % 10;
}

ll count2(ll n, int l, int r)
{
    if (n == 0) return (l == 0);
    ll ans = 1;
    int digs = numdigs(n);
    for (int i = digs - 1; i >= 0; i--)
    {
        int d = get(n, i);
        if (d < l) 
        {
            ans--;
            break;
        }

        for (int j = l; j <= min(r, d - 1); j++) ans += power(r - l + 1, i);

        if (d > r) 
        {
            ans--;
            break;
        }
    }

    if (l != 0 && digs > 1)
    {
        if (r > l) ans += (r - l + 1) * (power(r - l + 1, digs - 1) - 1) / (r - l);
        else ans += digs - 1; 
    }

    return ans;
}

ll count(ll n, int l, int r)
{
    ll ans = count2(n, l, r);
    if (l + 1 <= r) ans -= count2(n, l + 1, r) + count2(n, l, r - 1);
    if (l + 2 <= r) ans += count2(n, l + 1, r - 1);
    return ans;
}

ll count(ll l, ll r, int a, int b)
{
    return (count(r, a, b) - count(l - 1, a, b)) > 0;
}

void solve()
{
    ll l, r;
    cin >> l >> r;

    int diff, a, b;

    for (int d = 0; d <= 9; d++)
    {
        int found = 0;
        for (int i = 0; i <= 9 - d; i++)
        {
            int j = i + d;
            if (count(l, r, i, j)) 
            {
                // cout << i << " " << j << " " << count(l, r, i, j) << endl;
                diff = d;
                a = i;
                b = j;
                found = 1;
                break;
            }
        }
        if (found) break;
    } 

    ll ans = -1;
    ll lb = l, ub = r;
    while (lb <= ub)
    {
        ll mid = (lb + ub) / 2;

        if (count(l, mid, a, b))
        {
            ub = mid - 1;
            ans = mid;
        }
        else lb = mid + 1;
    }

    cout << ans << endl;
}

int main()
{
    // freopen('.in', 'r', cin);
    // freopen('.out', 'w', cout);
    srand(time(NULL));
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    powt[0] = 1;
    for (int i = 1; i <= 18; i++) powt[i] = powt[i - 1] * 10;

    int T;
    cin >> T;
    while (T--) solve();

    return 0;
} 