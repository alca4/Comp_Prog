/*
  ___
 (o,o)
<  .  >
--"-"---
Rowlet is orz
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
#include <bitset>
using namespace std;

#define F first
#define S second
#define pb push_back
#define ll long long
#define ld long double
#define INF 1000000000ull
#define MOD 1000000007ull

typedef pair<int, int> pii;
typedef pair<ll, ll> pll;

int read()
{
    int a;
    cin >> a;
    return a;
}

struct Ad
{
    int l, r, x, y;
};

const int MAXN = 50010;
int N, M, W, H;
bitset<MAXN> width[2010];
bitset<MAXN> height[2010];
bitset<MAXN> day[2010];
Ad posters[MAXN];
vector<int> spec[MAXN];
#define BUF 50000
int vis[2 * MAXN];
int comp[2 * MAXN];
int sign[2 * MAXN];

bool overlap(int a, int i)
{
    bool ans = 1;
    ans &= (min(posters[a].r, posters[i].r) >= 
            max(posters[a].l, posters[i].l));
    ans &= (abs(posters[a].x - posters[i].x) < W);
    ans &= (abs(posters[a].y - posters[i].y) < H);
    return ans;
}

void DFS(int a)
{
    // cout << a << endl;
    if (a > BUF)
    {
        bitset<MAXN> ans;
        ans.set();
        ans &= day[posters[a - BUF].l];
        ans &= width[posters[a - BUF].x];
        ans &= height[posters[a - BUF].y];

        for (int i = 1; i <= N; i++) 
        {
            if (a - BUF == i) continue;
            if (!ans[i]) continue;
            // cout << a - BUF << " and " << i << " overlap: " << overlap(a - BUF, i) << endl;
            // cout << "can reach " << i << endl;
            if (!vis[i])
            {
                vis[i] = 1;
                DFS(i);
            }
        }
    }
    else
    {
        for (int i = 0; i < spec[a].size(); i++)
        {
            // cout << "going to " << spec[a][i] + BUF << endl;
            if (!vis[spec[a][i] + BUF])
            {
                vis[spec[a][i] + BUF] = 1;
                DFS(spec[a][i] + BUF);
            }
        }
    }
    // cout << a << endl;
}

int main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    cin >> N >> W >> H;
    for (int i = 1; i <= N; i++)
    {
        // cout << i << endl;
        posters[i] = {read(), read(), read(), read()};
        for (int j = -W + 1; j < W; j++) 
        {
            if (0 < j + posters[i].x && j + posters[i].x <= 2000)
            {
                // cout << "good with " << j + posters[i].x << endl;
                width[j + posters[i].x].set(i);
            }
        }
        for (int j = -H + 1; j < H; j++) 
        {
            if (0 < j + posters[i].y && j + posters[i].y <= 2000)
            {
                // cout << "good with " << j + posters[i].y << endl;
                height[j + posters[i].y].set(i);
            }
        }
        for (int j = 1; j <= posters[i].r; j++) 
        {
            // cout << "good with " << j << endl;
            day[j].set(i);
        }
    }

    cin >> M;
    for (int i = 1; i <= M; i++) 
    {
        int a = read();
        int b = read();
        spec[a].pb(b);
        spec[b].pb(a);
    }
    
    for (int i = 1; i <= N; i++)
    {
        if (vis[i] || vis[i + BUF]) continue;
        vis[i] = 1;
        DFS(i);
    }
    bool b1 = 1;
    for (int i = 1; i <= N; i++)
        if (vis[i] && vis[i + BUF]) b1 = 0;
    if (b1)
    {   
        cout << "Yes" << endl;
        for (int i = 1; i <= N; i++)
        {
            if (vis[i]) cout << "0";
            else cout << "1";
        }
        cout << endl;
        return 0;
    }

    for (int i = 1; i <= N; i++) vis[i] = vis[i + BUF] = 0;

    // cout << "round 2 " << endl;
    for (int i = 1; i <= N; i++)
    {
        if (vis[i] || vis[i + BUF]) continue;
        vis[i + BUF] = 1;
        DFS(i + BUF);
    }
    bool b2 = 1;
    for (int i = 1; i <= N; i++)
        if (vis[i] && vis[i + BUF]) b2 = 0;
    if (b2)
    {
        cout << "Yes" << endl;
        for (int i = 1; i <= N; i++)
        {
            if (vis[i]) cout << "0";
            else cout << "1";
        }
        cout << endl;
        return 0;
    }
    
    cout << "No" << endl;
    return 0;
}