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
ll INF = 1000000000;
ll MOD = 1000000007;

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
ll div(const ll& a, const ll& b) {return (a * power(b, MOD - 2)) % MOD;}

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
int N;
ll arr[MAXN];
int dist[MAXN];
vector<int> nbs[MAXN];

int SP(int a)
{
    for (int i = 1; i <= N; i++) dist[i] = INF;
    int ans = INF;

    queue<pii> q;
    q.push({a, 0});
    while (!q.empty())
    {
        int n = q.front().FF;
        int w = q.front().SS;
        q.pop();

        if (dist[n] != INF) 
        {
            ans = min(ans, dist[n] + w);
            continue;
        }
        else dist[n] = w;

        for (int i = 0; i < nbs[n].size(); i++)
        {
            if (dist[nbs[n][i]] >= w) 
            {
                q.push({nbs[n][i], w + 1});
            }
        }
    }

    return ans;
}

int main()
{
    srand(time(NULL));
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    cin >> N;
    for (int i = 1; i <= N; i++) 
    {
        cin >> arr[i];
        if (arr[i] == 0)
        {
            i--;
            N--;
        }
    }

    if (N > 64 * 2) cout << 3 << endl;
    else
    {
        for (int i = 1; i <= N; i++) for (int j = 1; j < i; j++) if (arr[i] & arr[j]) 
        {
            nbs[i].pb(j);
            nbs[j].pb(i);
        }

        int ans = INF;
        for (int i = 1; i <= N; i++) ans = min(ans, SP(i));
        
        if (ans == INF) cout << -1 << endl;
        else cout << ans << endl;
    }

    return 0;
} 