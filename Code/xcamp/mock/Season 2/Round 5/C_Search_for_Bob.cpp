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

void maxeq(ll& a, ll b) {a = max(a, b);}
void mineq(ll& a, ll b) {a = min(a, b);}
void add(ll& a, ll b) {a = (a + b) % MOD;}
void mult(ll& a, ll b) {a = (a * b) % MOD;}

const int MAXN = 110;
int N;
vector<int> nbs[MAXN];
int dist[MAXN];
int ans = 0;
int T = -1;

void DFS(int a, int p)
{
    ++T;
    if (a != 1) ans += T;
    for (int i = 0; i < nbs[a].size(); i++) if (nbs[a][i] != p)
    {
        DFS(nbs[a][i], a);
    }
    ++T;
}

int main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    cin >> N;
    for (int i = 1; i < N; i++)
    {
        int a, b;
        cin >> a >> b;
        nbs[a].pb(b);
        nbs[b].pb(a);
    }

    DFS(1, 0);

    cout << setprecision(12) << fixed << 1.0 * ans / (N - 1) << endl;
    return 0;
}