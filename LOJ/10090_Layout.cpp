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
#include <cstring>
#include <cassert>
using namespace std;

#define F first
#define S second
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

int read() {
    int a;
    cin >> a;
    return a;
}

const int MAXN = 1010;
int N;
int L, G;
int E = 0;
struct Edge
{
    int n1, n2, w;  
} edges[MAXN * MAXN];
int dist[MAXN];

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    cin >> N >> L >> G;

    for (int i = 1; i <= L; i++) 
    {
        int a = read(), b = read(), c = read();
        edges[++E] = {a, b, c};
        edges[++E] = {b, a, c};
    }
    for (int i = 1; i <= G; i++) 
    {
        int a = read(), b = read(), c = read();
        edges[++E] = {b, a, c * -1};
    }

    for (int i = 1; i <= N; i++)
        dist[i] = INF;

    dist[1] = 0;
    for (int i = 1; i < N; i++)
        for (int j = 1; j <= E; j++)
            dist[edges[j].n2] = min(dist[edges[j].n2], dist[edges[j].n1] + edges[j].w);
    
    for (int j = 1; j <= E; j++)
        if (dist[edges[j].n2] != INF && dist[edges[j].n2] > dist[edges[j].n1] + edges[j].w)
        {
            cout << -1 << endl;
            return 0;
        }

    if (dist[N] == INF)
        cout << -2 << endl;
    else
        cout << dist[N] << endl;
    return 0;
}