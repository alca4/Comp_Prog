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

const int MAXN = 2010;
int N, Q;
ll h[MAXN];
vector<ll> visible[MAXN];

bool better(int i, int j, int k)
{
    return (h[j] - h[i]) * (k - i) <= (h[k] - h[i]) * (j - i);
}

void insert(int i, int j)
{
    auto it = lower_bound(visible[i].begin(), visible[i].end(), j);
    int id = distance(visible[i].begin(), it);
    visible[i].insert(it, j);

    if (id > 0 && visible[i][id - 1] > i && !better(i, visible[i][id - 1], j))
    {
        visible[i].erase(visible[i].begin() + id);
        return;
    }
    id++;
    while (id != visible[i].size() && !better(i, j, visible[i][id]))
        visible[i].erase(visible[i].begin() + id);
}

int main()
{
    srand(time(NULL));
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    cin >> N;
    for (int i = 1; i <= N; i++) cin >> h[i];

    for (int i = 1; i <= N; i++) for (int j = i + 1; j <= N; j++) 
        insert(i, j);

    cin >> Q;

    while (Q--)
    {
        // cout << "==========" << endl;
        int n, d;
        cin >> n >> d;
        h[n] += d;
        for (int i = 1; i <= N; i++) 
        {
            int it = distance(visible[i].begin(), lower_bound(visible[i].begin(), visible[i].end(), n));
            if (it < visible[i].size() && visible[i][it] == n) visible[i].erase(visible[i].begin() + it);
        }
        for (int i = 1; i < n; i++) insert(i, n);
        visible[n].clear();
        for (int i = n + 1; i <= N; i++) insert(n, i);

        int ans = 0;
        for (int i = 1; i <= N; i++) ans += visible[i].size();
        cout << ans << endl;
    }

    return 0;
} 