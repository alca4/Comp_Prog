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

int N, M;
vector<string> table;
vector<string> best;
vector<string> cur;

int main()
{
    srand(time(NULL));
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    cin >> N >> M;
    for (int i = 0; i < N; i++) 
    {
        string str;
        cin >> str;
        table.pb(str);
    }

    cur.resize(N);
    for (int i = 0; i < N; i++) cur[i].resize(M);

    int ans = INF;
    string tmp = "ACGT";
    do
    {
        int score = 0;

        for (int i = 0; i < N; i++) 
        {
            int t1 = 0;
            for (int j = 0; j < M; j++) 
                t1 += 1 - (table[i][j] == tmp[2 * (i % 2) + j % 2]);
            
            int t2 = 0;
            for (int j = 0; j < M; j++) 
                t2 += 1 - (table[i][j] == tmp[2 * (i % 2) + (j + 1) % 2]);

            if (t1 < t2)
            {
                score += t1;
                for (int j = 0; j < M; j++) 
                    cur[i][j] = tmp[2 * (i % 2) + j % 2];
            }
            else
            {
                score += t2;
                for (int j = 0; j < M; j++) 
                    cur[i][j] = tmp[2 * (i % 2) + (j + 1) % 2];
            }
        }

        if (score < ans)
        {
            ans = score;
            best = cur;
        }

        score = 0;
        for (int i = 0; i < M; i++) 
        {
            int t1 = 0;
            for (int j = 0; j < N; j++) 
                t1 += 1 - (table[j][i] == tmp[2 * (i % 2) + j % 2]);
            
            int t2 = 0;
            for (int j = 0; j < N; j++) 
                t2 += 1 - (table[j][i] == tmp[2 * (i % 2) + (j + 1) % 2]);

            if (t1 < t2)
            {
                score += t1;
                for (int j = 0; j < N; j++) 
                    cur[j][i] = tmp[2 * (i % 2) + j % 2];
            }
            else
            {
                score += t2;
                for (int j = 0; j < N; j++) 
                    cur[j][i] = tmp[2 * (i % 2) + (j + 1) % 2];
            }
        }

        if (score < ans)
        {
            ans = score;
            best = cur;
        }
    } while (next_permutation(tmp.begin(), tmp.end()));

    for (int i = 0; i < N; i++) cout << best[i] << endl;
    return 0;
} 