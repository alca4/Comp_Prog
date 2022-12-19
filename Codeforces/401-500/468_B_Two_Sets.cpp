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
ll MOD = 1000000007;

ifstream fin(".in");
ofstream fout(".out");

typedef pair<int, int> pii;
typedef pair<ll, ll> pll;

ll add(const ll& a, const ll& b) {return (a + b) % MOD;}
ll sub(const ll& a, const ll& b) {return (a + MOD - b) % MOD;}
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

void tleassert(bool b, int a)
{
    if (!b) 
    {
        cout << a << endl;
        while (1);
    }
}

const int MAXN = 100010;
int N, A, B;
int arr[MAXN];
int choice[MAXN];
int use[MAXN];
map<int, int> vals;

int p[MAXN], sz[MAXN];
int root(int a) {return p[a] = (a == p[a] ? a : root(p[a]));}
int combine(int a, int b)
{
    a = root(a), b = root(b);
    if (a == b) return 0;

    if (sz[a] < sz[b]) swap(a, b);
    p[b] = a;
    sz[a] += sz[b];
    return 1;
}

int main()
{
    srand(time(NULL));
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    cin >> N >> A >> B;
    for (int i = 1; i <= N; i++) 
    {
        cin >> arr[i];
        vals[arr[i]] = i;
        p[i] = i;
    }

    for (int i = 1; i <= N; i++)
    {
        if (vals.count(A - arr[i])) 
        {
            combine(i, vals[A - arr[i]]);
            use[i] |= 1;
        }
        if (vals.count(B - arr[i])) 
        {
            combine(i, vals[B - arr[i]]);
            use[i] |= 2;
        }
    }

    for (int i = 1; i <= N; i++) choice[i] = 3;
    for (int i = 1; i <= N; i++) choice[root(i)] &= use[i];

    int ans = 1;
    for (int i = 1; i <= N; i++) if (!choice[i]) ans = 0;

    if (ans) 
    {
        cout << "YES" << endl;
        for (int i = 1; i <= N; i++) 
        {
            if (choice[root(i)] == 3) cout << 1 << " ";
            else cout << choice[root(i)] - 1 << " ";
        }
        cout << endl;
    }
    else cout << "NO" << endl;
    return 0;
} 