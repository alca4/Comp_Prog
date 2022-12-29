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

const int MAXN = 1010;
int N;
int sieve[MAXN * MAXN];
set<int> odd;
set<int> even;
vector<pii> pairs;
int grid[MAXN][MAXN];

int main()
{
    srand(time(NULL));
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    cin >> N;

    int c1 = -1, c2 = -1;
    for (int i = 2; i <= 1000000; i++)
    {
        if (!sieve[i])
        {
            for (int j = 2; i * j <= 1000000; j++)
                sieve[i * j] = 1;
        }
        else if (i % 2 && i > 2 * N)
        {
            if (c1 == -1) c1 = i;
            else if (c2 == -1) c2 = i;
            else break;
        }
    }

    for (int i = 1; i <= N * N; i++)
    {
        if (i % 2) odd.insert(i);
        else even.insert(i);
    }

    int P = N + (N % 2);
    if (N % 2)
    {
        pairs.pb({c2 - c1 + 1, 2 * c1 - c2 - 1});
        odd.erase(c2 - c1 + 1);
        even.erase(2 * c1 - c2 - 1);
        pairs.pb({1, c1 - 1});
        odd.erase(1);
        even.erase(c1 - 1);
        
        P -= 3;
    }

    int cnt = 2;
    while (P)
    {
        if (cnt % 2)
        {
            if (odd.count(cnt) && even.count(c1 - cnt))
            {
                odd.erase(cnt);
                even.erase(c1 - cnt);
                pairs.pb({cnt, c1 - cnt});
                P--;
            }
        }
        else
        {
            if (even.count(cnt) && odd.count(c1 - cnt))
            {
                odd.erase(c1 - cnt);
                even.erase(cnt);
                pairs.pb({c1 - cnt, cnt});
                P--;
            }
        }
        cnt++;
    }

    if (N % 2)
    {
        grid[(N + 1) / 2][(N + 1) / 2] = pairs[0].FF;
        grid[(N + 1) / 2 + 1][(N + 1) / 2] = pairs[0].SS;
        grid[(N + 1) / 2 - 1][(N + 1) / 2 + 1] = pairs[1].FF;
        grid[(N + 1) / 2][(N + 1) / 2 + 1] = pairs[1].SS;

        for (int i = 1; i <= N / 2; i++)
        {
            grid[(N + 1) / 2][i] = pairs[i + 1].FF;
            grid[(N + 1) / 2 + 1][i] = pairs[i + 1].SS;
        }

        for (int i = (N + 1) / 2 + 2; i <= N; i++)
        {
            grid[(N + 1) / 2 - 1][i] = pairs[i - 1].FF;
            grid[(N + 1) / 2][i] = pairs[i - 1].SS;
        }

        for (int i = 1; i <= N; i++) for (int j = 1; j <= N; j++)
        {
            if (!odd.empty()) 
            {
                grid[i][j] = *odd.begin();
                odd.erase(odd.begin());
            }
        }

        for (int i = N; i >= 1; i--) for (int j = N; j >= 1; j--)
        {
            if (!even.empty()) 
            {
                grid[i][j] = *even.begin();
                even.erase(even.begin());
            }
        }
    }
    else
    {
        for (int i = 1; i <= N; i++)
        {
            grid[N / 2][i] = pairs[i - 1].FF;
            grid[N / 2 + 1][i] = pairs[i - 1].SS;
        }

        for (int i = 1; i <= N; i++) for (int j = 1; j <= N; j++)
        {
            if (!odd.empty()) 
            {
                grid[i][j] = *odd.begin();
                odd.erase(odd.begin());
            }
        }

        for (int i = N; i >= 1; i--) for (int j = N; j >= 1; j--)
        {
            if (!even.empty()) 
            {
                grid[i][j] = *even.begin();
                even.erase(even.begin());
            }
        }
    }

    for (int i = 1; i <= N; i++) 
    {
        for (int j = 1; j <= N; j++) cout << grid[i][j] << " ";
        cout << endl;
    }
    return 0;
} 