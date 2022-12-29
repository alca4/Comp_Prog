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
#define ll long long
#define pb push_back
#define ld long double
#define INF 1000000000
#define BASE 94716179
#define INV 2009181436
#define INV2 111171958
#define MOD 2147483647
#define MOD2 1000000007

typedef pair<int, int> pii;
typedef pair<ll, ll> pll;

int readInt()
{
    int a;
    cin >> a;
    return a;
}

const int MAXN = 100010;

int N;
pll powb[2 * MAXN], powinv[2 * MAXN];
vector<int> child[MAXN];
vector<int> depth[MAXN];
int height[MAXN];

int T, D;
int in[MAXN], out[MAXN];
pll h[2 * MAXN];

void DFS(int a, int d)
{
    D = max(D, d);
    h[++T] = {1, 1};
    in[a] = T;
    depth[d].pb(a);
    for (int i = 0; i < child[a].size(); i++) 
    {
        DFS(child[a][i], d + 1);
        height[a] = max(height[a], height[child[a][i]] + 1);
    }
    if (child[a].size() == 0) height[a] = 0;
    h[++T] = {0, 0};
    out[a] = T;
}

pll concat(int len, pll v1, pll v2)
{
    return {(v1.F + ((v2.F % MOD) * powb[len].F) % MOD) % MOD,
           (v1.S + ((v2.S % MOD2) * powb[len].S) % MOD2) % MOD2};
}

pll getHash(int a, int b)
{
    return {(((h[b].F - h[a - 1].F + MOD) % MOD) * powinv[a - 1].F) % MOD,
            (((h[b].S - h[a - 1].S + MOD2) % MOD2) * powinv[a - 1].S) % MOD2};
}

int main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    cin >> N;
    for (int i = 1; i <= N; i++)
    {
        int a = readInt();
        for (int j = 1; j <= a; j++) child[i].pb(readInt());
    }

    powb[0] = {1, 1};
    powinv[0] = {1, 1};
    for (int i = 1; i <= 2 * N; i++) 
    {
        powb[i].F = (powb[i - 1].F * BASE) % MOD;
        powb[i].S = (powb[i - 1].S * BASE) % MOD2;
        powinv[i].F = (powinv[i - 1].F * INV) % MOD;
        powinv[i].S = (powinv[i - 1].S * INV2) % MOD2;
    }

    DFS(1, 1);
    
    for (int i = 1; i <= 2 * N; i++)
    {
        h[i].F = (h[i - 1].F + h[i].F * powb[i].F) % MOD;
        h[i].S = (h[i - 1].S + h[i].S * powb[i].S) % MOD2;
    }

    int lb = 1;
    int ub = N;
    int ans = 0;
    while (lb <= ub)
    {
        int K = (lb + ub) / 2;

        set<pll> vals;
        int n = 0;
        for (int i = D - K; i >= 1; i--)
        {
            int kid = 0;
            for (int j = 0; j < depth[i].size(); j++)
            {
                if (height[depth[i][j]] < K) continue;
                n++;
                int cur = depth[i][j];
                pll val = {0, 0};
                int len = 0;
                int l = in[cur];
                int r;
                while (kid < depth[i + K + 1].size() && 
                       out[depth[i + K + 1][kid]] < out[cur])
                {
                    r = in[depth[i + K + 1][kid]] - 1;
                    if (l <= r)
                    {
                        val = concat(len, val, getHash(l, r));
                        len += r - l + 1;
                    } 
                    l = out[depth[i + K + 1][kid]] + 1;
                    kid++;
                }
                r = out[cur];
                val = concat(len, val, getHash(l, r));
                vals.insert(val);
            }
        }
        if (vals.size() < n)
        {
            ans = max(ans, K);
            lb = K + 1;
        }
        else
        {
            ub = K - 1;
        }
    }
    cout << ans << endl;
    return 0;
}