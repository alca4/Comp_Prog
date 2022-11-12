/*
  ___
 (o,o)
<  .  >
--"-"---
Rowlet is orz
*/
#include <bits/stdc++.h>
using namespace std;

#define FF first
#define SS second
#define pb push_back
#define ll long long
#define ld long double
#define INF 1000000000ull
#define MOD 1000000007ull
#define reset(x) memset(x, 0, sizeof(x))
#define all(x) (x).begin(), (x).end()
#define range(x, y, z) (x) + (y), (x) + (y) + (z)

typedef pair<int, int> pii;
typedef pair<ll, ll> pll;

void maxe(int& a, int b) {a = max(a, b);}
void mine(int& a, int b) {a = max(a, b);}

const int MAXN = 1010;
int N[2], M[2];
string S[2];
set<int> nbs[MAXN][2];

int indeg[MAXN][2];
multiset<pii> sorter;
int topsort[MAXN][2];

void input(int id)
{
    cin >> N[id] >> M[id] >> S[id];
    S[id] = '#' + S[id];
    for (int i = 1; i <= M[id]; i++)
    {
        int a, b;
        cin >> a >> b;
        nbs[a][id].insert(b);
    }

    for (int i = 1; i <= N[id]; i++)
        for (auto tar : nbs[i][id])
            indeg[tar][id]++;

    for (int i = 1; i <= N[id]; i++)
        sorter.insert({indeg[i][id], i});
    
    for (int i = 1; i <= N[id]; i++)
    {
        topsort[i][id] = sorter.begin()->SS;
        sorter.erase(sorter.begin());
        for (auto tar : nbs[topsort[i][id]][id])
        {
            sorter.erase(pii(indeg[tar][id], tar));
            indeg[tar][id]--;
            sorter.insert(pii(indeg[tar][id], tar));
        }
    }
}

int dp[MAXN][MAXN][2][2];

int main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    input(0), input(1);

    for (int i = 1; i <= N[0]; i++)
    {
        for (int j = 1; j <= N[1]; j++)
        {
            int a = topsort[i][0];
            int b = topsort[j][1];
            if (S[0][a] == S[1][b]) 
            {
                dp[a][b][1][1] = dp[a][b][0][0] + 1;
                // cout << "repeat" << endl;
            }
            else dp[a][b][1][1] = 0;

            // cout << "at " << a << " " << b << endl;
            for (auto nb : nbs[a][0])
            {
                // cout << "a want go " << nb << endl;
                for (int k = 0; k <= 1; k++) 
                {
                    maxe(dp[nb][b][0][k], dp[a][b][0][k]);
                    maxe(dp[nb][b][0][k], dp[a][b][1][k]);
                }
            }
            for (auto nb : nbs[b][1])
            {
                // cout << "b want go " << nb << endl;
                for (int k = 0; k <= 1; k++) 
                {
                    maxe(dp[a][nb][k][0], dp[a][b][k][0]);
                    maxe(dp[a][nb][k][0], dp[a][b][k][1]);
                }
            }
        }
    }

    int ans = 0;
    for (int i = 1; i <= N[0]; i++) for (int j = 1; j <= N[1]; j++)
        for (int k = 0; k < 2; k++) for (int h = 0; h < 2; h++)
            maxe(ans, dp[i][j][k][h]);
    
    cout << ans << endl;
    return 0;
}