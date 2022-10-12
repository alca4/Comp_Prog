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
#define INF 1000000000ll
#define MOD 1000000007ll

typedef pair<int, int> pii;
typedef pair<ll, ll> pll;

ll add(ll a, ll b) {return (a + b) % MOD;}
ll mult(ll a, ll b) {return (a * b) % MOD;}

const int MAXN = 100010;
int N, K, S;
ll dp[110][100010];
int vals[100010];

int main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    cin >> N >> K;
    S = sqrt(N);

    set<int> cand;
    for (int i = 1; i <= S; i++) 
    {
        cand.insert(N / i);
        cand.insert(N / (N / i));
    }

    int V = 0;
    for (auto it = cand.begin(); it != cand.end(); ++it) vals[++V] = *it;

    for (int i = 1; i <= V; i++) dp[1][i] = vals[i];

    for (int i = 2; i <= K; i++)
    {
        for (int j = 1; j <= V; j++)
        {
            int k = V + 1 - j;
            dp[i][j] = add(dp[i][j - 1], mult(dp[i - 1][k], vals[j] - vals[j - 1]));
        }
    }

    cout << dp[K][V] << endl;
    return 0;
}