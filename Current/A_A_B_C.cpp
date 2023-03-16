/*
  ___
 (o,o)
<  .  >
--"-"---
Rowlet is orz
  _      _      _
>(.)__ <(.)__ =(.)__
 (___/  (___/  (___/
I am dum duck

Praise to the Cow God
*/
#include <bits/stdc++.h>
using namespace std;

#define FF first
#define SS second
#define pb push_back
#define ll long long
#define ld long double
#define ull unsigned ll
ll INF = 1000000000;
ll LINF = 1000000000000000000;
ll MOD = 1000000007;
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
    for (int i = 1; i < 64; i++) binexp[i] = mult(binexp[i - 1], binexp[i - 1]);

    while (n > 0)
    {
        int id = (int) log2(n & -n);
        ans = mult(ans, binexp[id]);
        n -= (n & -n);
    }

    return ans;
}
ll divide(const ll& a, const ll& b) {return (a * power(b, MOD - 2)) % MOD;}
template<class X, class Y> void maxeq(X &x, Y y) {if (x < y) x = y;}
template<class X, class Y> void mineq(X &x, Y y) {if (x > y) x = y;}

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

const int MAXN = 2010;
int N;
ll fact[MAXN], factinv[MAXN];

ll choose(int a, int b)
{
    return mult(fact[a], mult(factinv[b], factinv[a - b]));
}

void get_fact()
{
    fact[0] = 1;
    for (int i = 1; i <= N; i++) fact[i] = mult(fact[i], fact[i - 1]);
    factinv[N] = divide(1, fact[N]);
    for (int i = N - 1; i >= 0; i--) factinv[i] = mult(factinv[i + 1], i + 1);
}

bool get(int a, int b, int c)
{
    cout << "? " << a << " " << b << " " << c << endl;
    string str;
    cin >> str;
    if (str == "Yes") return 1;
    else return 0;
}

map<int, int> m;
int ans[MAXN];

void solve(int a, int b, vector<int>& ids)
{
    cout << "solving " << a << " to " << b << endl;
    cout << "indices are: ";
    for (int id : ids) cout << id << " ";
    cout << endl;
    if (a == b)
    {
        m[a] = ids[0];
        ans[ids[0]] = a;
        // cout << a << " is " << ids[0] << endl;
        return;   
    }

    vector<int> left, right;
    if (a == 1)
    {
        for (int i = 1; i < ids.size(); i++) 
        {
            if (ids[i] == ids[0]) continue;
            if (get(ids[i], ids[i], ids[0])) right.pb(ids[i]);
            else left.pb(ids[i]);
        }
        if (!left.empty()) right.pb(ids[0]);
        else left.pb(ids[0]);
    }
    else
    {
        int num = m[(a + b) / 4 < a ? (a + b) / 4 : a - 1];
        for (int i = 0; i < ids.size(); i++)
        {
            if (ids[i] == num) continue;
            if (get(num, num, ids[i])) left.pb(ids[i]);
            else right.pb(ids[i]);
        }
    }
    solve(a, a + left.size() - 1, left);
    solve(a + left.size(), b, right);
}

int main()
{
    // freopen('.in', 'r', cin);
    // freopen('.out', 'w', cout);
    srand(time(NULL));
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    cin >> N;
    vector<int> ids;
    for (int i = 1; i <= N; i++) ids.pb(i);
    solve(1, N, ids);

    cout << "!" << endl;
    for (int i = 1; i <= N; i++) cout << ans[i] << " ";
    cout << endl;

    return 0;
} 