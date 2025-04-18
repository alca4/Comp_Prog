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

const int MAXN = 300010;
int N, Q;
int arr[MAXN];
ll sets[2 * MAXN];

struct BIT
{
    ll arr[MAXN];

    void update(int a, ll v)
    {
        while (a <= N)
        {
            arr[a] += v;
            a += (a & -a);
        }
    }

    ll query(int a)
    {
        ll ans = 0;
        while (a)
        {
            ans += arr[a];
            a -= (a & -a);
        }
        return ans;
    }
    ll query(int a, int b) {return query(b) - query(a - 1);}
} bits[64];

struct Query
{
    ll t, a, b, k;
} queries[MAXN];

int main()
{
    srand(time(NULL));
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    cin >> N >> Q;
    map<int, int> compress;
    for (int i = 1; i <= N; i++)
    {
        cin >> arr[i];
        compress[arr[i]]++;
    }
    for (int i = 1; i <= Q; i++)
    {
        cin >> queries[i].t >> queries[i].a >> queries[i].b;
        if (queries[i].t == 2) cin >> queries[i].k;
        if (queries[i].t == 1) compress[queries[i].b]++;
    }

    int cnt = 0;
    for (auto n : compress) compress[n.FF] = ++cnt;

    for (int i = 1; i <= N; i++) arr[i] = compress[arr[i]];
    for (int i = 1; i <= Q; i++)
        if (queries[i].t == 1) queries[i].b = compress[queries[i].b];

    int N2 = compress.size();

    for (int i = 1; i <= N2; i++) sets[i] = rand64();
    for (int i = 0; i < 32; i++)
    {
        for (int j = 1; j <= N; j++) if (sets[arr[j]] & (1ll << i))
            bits[i].update(j, 1);
    }

    for (int i = 1; i <= Q; i++)
    {
        if (queries[i].t == 1)
        {
            int x = queries[i].a;
            for (int j = 0; j < 32; j++) if (sets[arr[x]] & (1ll << j))
                bits[j].update(x, -1);
            arr[x] = queries[i].b;
            for (int j = 0; j < 32; j++) if (sets[arr[x]] & (1ll << j))
                bits[j].update(x, 1);
        }
        else
        {
            int ans = 1;
            for (int j = 0; j < 32; j++) 
                ans = ans && (bits[j].query(queries[i].a, queries[i].b) % queries[i].k == 0);
            if (ans) cout << "YES" << endl;
            else cout << "NO" << endl;
        }

        // for (int i = 1; i <= N; i++) cout << arr[i] << " ";
        // cout << endl;
    }

    return 0;
} 