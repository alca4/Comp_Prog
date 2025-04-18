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
struct Edge
{
    int s, d, w;
} edgelist[MAXN];
int dist[MAXN];
int tmp[MAXN];

bool operator<(const Edge& e1, const Edge& e2)
{
    return e1.w < e2.w;
}

int main()
{
    srand(time(NULL));
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    cin >> N >> M;
    for (int i = 1; i <= M; i++)
        cin >> edgelist[i].s >> edgelist[i].d >> edgelist[i].w;

    sort(edgelist + 1, edgelist + 1 + M);

    for (int i = 1; i <= M; i++)
    {
        int n = i;
        int w = edgelist[i].w;
        for (; i <= M; i++) if (edgelist[i].w > w) break;
        i--;

        for (int j = n; j <= i; j++) 
            tmp[edgelist[j].d] = max(tmp[edgelist[j].d], dist[edgelist[j].s] + 1);
        for (int j = n; j <= i; j++) 
        {
            dist[edgelist[j].d] = max(dist[edgelist[j].d], tmp[edgelist[j].d]);
            tmp[edgelist[j].d] = 0;
        }
    }

    int best = 0;
    for (int i = 1; i <= N; i++) best = max(best, dist[i]);
    cout << best << endl;
    return 0;
} 