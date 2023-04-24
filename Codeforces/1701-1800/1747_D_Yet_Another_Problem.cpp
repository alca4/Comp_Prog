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
ll power(ll a, ll b)
{
    ll n = b;
    ll ans = 1;

    ll binexp[64];
    binexp[0] = a;
    for (int i = 1; i < 64; i++) binexp[i] = mult(binexp[i - 1], binexp[i - 1]);

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

const int MAXN = 200010;
int N, Q;
int arr[MAXN];
map<int, set<int>> freq[2];
set<int> nz, nzb;

int main()
{
    // freopen(".in", "r", stdin);
    // freopen(".out", "w", stdout);
    srand(time(NULL));
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    cin >> N >> Q;
    for (int i = 1; i <= N; i++)
    {
        cin >> arr[i];
        if (arr[i] != 0) 
        {
            nz.insert(i);
            nzb.insert(-i);
        }
        arr[i] ^= arr[i - 1];
        freq[i % 2][arr[i]].insert(i);
    }

    while (Q--)
    {
        int l, r;
        cin >> l >> r;

        if (arr[r] != arr[l - 1]) cout << -1 << endl;
        else if (nz.lower_bound(l) == nz.end() || nzb.lower_bound(-r) == nzb.end())
            cout << 0 << endl;
        else if (*nz.lower_bound(l) > r) cout << 0 << endl;
        else 
        {
            bool change = 0;
            if (l != *nz.lower_bound(l)) change = 1;
            l = *nz.lower_bound(l);
            if (r != -*nzb.lower_bound(-r)) change = 1;
            r = -*nzb.lower_bound(-r);

            if ((r - l) % 2 == 0) cout << 1 << endl;
            else if (change) cout << 1 << endl;
            else 
            {
                auto it = freq[l % 2][arr[l - 1]].upper_bound(l);
                if (it != freq[l % 2][arr[l - 1]].end() && *it < r) cout << 2 << endl;
                else cout << -1 << endl;
            }
        }
    }

    return 0;
} 