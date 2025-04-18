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

const int MAXN = 100010;
int N, K;
int target = 0;
int arr[MAXN];
vector<int> nbs[MAXN];
map<int, int> freq;

void DFS(int a, int p)
{
    for (int i = 0; i < nbs[a].size(); i++) if (nbs[a][i] != p)
    {
        DFS(nbs[a][i], a);
        if (arr[nbs[a][i]] != target) arr[a] ^= arr[nbs[a][i]];
    }
    freq[arr[a]]++;
}

int main()
{
    srand(time(NULL));
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    int T;
    cin >> T;
    while (T--)
    {
        cin >> N >> K;
        for (int i = 1; i <= N; i++) cin >> arr[i];
        for (int i = 1; i < N; i++)
        {
            int a, b;
            cin >> a >> b;
            nbs[a].pb(b);
            nbs[b].pb(a);
        }

        for (int i = 1; i <= N; i++) target ^= arr[i];

        DFS(1, 0);
        
        int ans = 1;
        if (target != 0)
            ans = (freq[target] % 2) && (freq[target] >= 3) && (K > 2);

        if (ans) cout << "YES" << endl;
        else cout << "NO" << endl;

        freq.clear();
        for (int i = 1; i <= N; i++) nbs[i].clear();
        for (int i = 1; i <= N; i++) arr[i] = 0;
        target = 0;
    }

    return 0;
} 