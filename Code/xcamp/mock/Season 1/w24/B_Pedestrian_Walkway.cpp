/*
  ___
 (o,o)
<  .  >
--"-"---
Rowlet hard carrying
*/
#include <iostream>
#include <algorithm>
#include <vector>
#include <cmath>
#include <set>
#include <map>
#include <deque>
#include <queue>
#include <stack>
#include <unordered_set>
#include <unordered_map>
using namespace std;

#define F first
#define S second
#define pb push_back
#define ll long long
#define ld long double
#define MOD 1000000009

typedef pair<int, int> pii;
typedef pair<ll, ll> pll;

int readInt()
{
    int a;
    cin >> a;
    return a;
}

ll N;
int M;
ll choice[20];
ll mat[110][110][80];
ll tmp[110][110];
ll b_n[110][110];
ll dp[20];

int main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    cin >> N >> M;
    for (int i = 1; i <= M; i++) cin >> choice[i];

    for (int i = 0; i <= 100; i++)
    {
        if (i == 0)
        {
            for (int j = 1; j <= M; j++)
                for (int h = 1; h <= M; h++)
                {
                    mat[i][(j - 1) * 10 + h - 1][0] += (choice[j] * choice[h]) % MOD;
                    mat[i][(j - 1) * 10 + h - 1][0] %= MOD;
                }
            mat[i][i][0] += choice[2];
            mat[i][i][0] %= MOD;
        }
        else if (i % 10 == 0)
        {
            for (int j = 1; j <= M; j++)
            {
                // cout << i << " " << (j + i / 10 - 1) * 10 + i % 10 - 1 << " " << choice[j] << endl;
                int t = (i / 10 - 1) * 10 + j - 1;
                mat[i][t][0] += choice[j];
                mat[i][t][0] %= MOD;
            }
        }
        else if (i / 10 == 0)
        {
            for (int j = 1; j <= M; j++)
            {
                // cout << i << " " << (j + i / 10 - 1) * 10 + i % 10 - 1 << " " << choice[j] << endl;
                int t = (j - 1) * 10 + i % 10 - 1;
                mat[i][t][0] += choice[j];
                mat[i][t][0] %= MOD;
            }
        }
        else 
        {
            mat[i][i - 11][0] += 1;
            mat[i][i - 11][0] %= MOD;
        }
    }

    for (int i = 1; i <= 70; i++)
        for (int j = 0; j <= 100; j++)
            for (int k = 0; k <= 100; k++)
                for (int h = 0; h <= 100; h++)
                {
                    mat[j][k][i] += (mat[j][h][i - 1] * mat[h][k][i - 1]) % MOD;
                    mat[j][k][i] %= MOD;
                }

    for (int i = 0; i <= 100; i++)
        b_n[i][i] = 1;

    while (N > 0)
    {
        for (int j = 0; j <= 100; j++)
        {
            for (int k = 0; k <= 100; k++)
            {
                tmp[j][k] = b_n[j][k];
                // if (tmp[j][k] > 1) cout << tmp[j][k] << " ";
                b_n[j][k] = 0;
            }
        }
        
        int p = (int) log2(N & -N);

        for (int j = 0; j <= 100; j++)
            for (int k = 0; k <= 100; k++)
            {
                for (int h = 0; h <= 100; h++)
                {
                    // if (j == 0 && k == 0) cout << "adding " << tmp[j][h] * mat[h][k][p] << endl;
                    b_n[j][k] += (tmp[j][h] * mat[h][k][p]) % MOD;
                    b_n[j][k] %= MOD;
                }
                // cout << b_n[j][k] << " ";
            }
        N -= (N & -N);
    }

    cout << b_n[0][0] % MOD << endl;
    return 0;
}