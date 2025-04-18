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
int N, M;
int arr[MAXN];
int nextv[MAXN];
int vis[MAXN];

int DFS(int a, int s)
{
    if (vis[a]) return 0;
    vis[a] = 1;
    if (a == s) return 1;
    return DFS(nextv[a], s) + 1;
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
        cin >> N >> M;
        // cout << "===" << endl;
        for (int i = 1; i <= N; i++) cin >> arr[i];

        map<int, int> freq;

        for (int i = 1; i <= N; i++)
        {
            int dist = i - arr[i];
            if (dist < 0) dist += N;
            freq[dist]++;
        }

        vector<int> anses;
        for (int i = 0; i < N; i++) if (freq[i] >= (N + 2) / 3)
        {
            // cout << i << " " << freq[i] << endl;
            for (int j = 1; j <= N; j++)
            {
                nextv[arr[j]] = (j - i + N - 1) % N + 1;
            }
            int c = 0;
            for (int j = 1; j <= N; j++) 
                if (!vis[j]) c += DFS(nextv[j], j) - 1;
            // for (int j = 1; j <= N; j++) cout << nextv[j] << " ";
            // cout << endl;
            if (c <= M) anses.pb(i);
            for (int j = 1; j <= N; j++) nextv[j] = vis[j] = 0;
        }
        
        cout << anses.size() << " ";
        for (auto n : anses) cout << n << " ";
        cout << endl;

        for (int i = 1; i <= N; i++) arr[i] = 0;
        anses.clear();
    }
    return 0;
}