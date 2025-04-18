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

const int MAXN = 200010;
int N, M, P;
ll masks[MAXN];
ll best;
int num;
int dp[(1 << 15)];

void test()
{
    int a = rand();
    int b = rand();
    ll mask = masks[abs((a << 15) | b) % N + 1];

    vector<int> pos;
    for (int i = 0; i < M; i++) if (mask & (1ll << i)) pos.pb(i);

    int S = pos.size();
    for (int i = 1; i <= N; i++) 
    {
        int x = 0;
        for (int j = 0; j < S; j++) 
            if (masks[i] & (1ll << pos[j])) x |= (1 << j);
        dp[x]++;
    }
    for (int i = 0; i < (1 << S); i++) for (int s = i; s; --s &= i) 
        if (s != i) dp[s] += dp[i];
    
    for (int i = 0; i < (1 << S); i++) if (dp[i] >= (N + 1) / 2) 
    {
        bitset<15> tmp(i);
        if (tmp.count() > num)
        {
            num = tmp.count();
            best = 0;
            for (int j = 0; j < S; j++) if (i & (1 << j)) best |= (1ll << pos[j]);
        }
    }

    for (int i = 0; i < (1 << S); i++) dp[i] = 0;
}

int main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    cin >> N >> M >> P;
    for (int i = 1; i <= N; i++)
    {
        for (int j = M - 1; j >= 0; j--)
        {
            char c;
            cin >> c;
            if (c == '1') masks[i] |= (1ll << j);
        }
    }

    srand(time(NULL));
    for (int i = 1; i <= 50; i++) test();

    for (int j = M - 1; j >= 0; j--) 
    {
        if (best & (1ll << j)) cout << 1;
        else cout << 0;
    }
    cout << endl;
    return 0;
}