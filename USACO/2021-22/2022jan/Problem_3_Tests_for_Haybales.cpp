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
#define INF 1000000000ll
#define MOD 1000000007ll
#define reset(x) memset(x, 0, sizeof(x))
#define all(x) (x).begin(), (x).end()
#define range(x, y, z) (x) + (y), (x) + (y) + (z)

typedef pair<int, int> pii;
typedef pair<ll, ll> pll;

int read()
{
    int a;
    cin >> a;
    return a;
}

const int MAXN = 100010;
int N;
vector<int> child[MAXN];
ll arr[MAXN];

int n = 0;
void DFS(int a, ll d)
{
    for (int i = 0; i < child[a].size(); i++) DFS(child[a][i], d + 1);
    arr[a] = (N - d) * 1000000000 + ++n;
}

int main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    cin >> N;
    for (int i = 1; i <= N; i++) 
    {
        int t;
        cin >> t;
        child[t + 1].pb(i);
    }

    DFS(N + 1, 0);

    cout << 1000000000 << endl;
    for (int i = 1; i <= N; i++) cout << arr[i] << endl;
    assert(n == N + 1);
    return 0;
}