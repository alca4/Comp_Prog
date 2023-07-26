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
#define MOD 1000000007
#define reset(x) memset(x, 0, sizeof(x))
#define all(x) (x).begin(), (x).end()
#define range(x, y, z) (x) + (y), (x) + (y) + (z)

typedef pair<int, int> pii;
typedef pair<ll, ll> pll;

void maxeq(ll& a, ll b) {a = max(a, b);}
void mineq(ll& a, ll b) {a = min(a, b);}
void add(ll& a, ll b) {a = (a + b) % MOD;}
void mult(ll& a, ll b) {a = (a * b) % MOD;}

const int MAXN = 500010;
int N, M;
vector<vector<ll>> arrs;
vector<ll> finals;

void solve()
{
    // cout << "===========" << endl;

    cin >> N >> M;
    arrs.resize(N + 1);
    finals.resize(N + 1);
    for (int i = 1; i <= N; i++)
    {
        arrs[i].resize(M + 1);
        for (int j = 1; j <= M; j++) cin >> arrs[i][j];
        for (int j = 2; j <= M; j++) arrs[i][j] += arrs[i][j - 1];
        for (int j = 1; j <= M; j++) finals[i] += arrs[i][j];
    }

    map<ll, vector<int>> vals;
    for (int i = 1; i <= N; i++) vals[finals[i]].pb(i);

    cout << vals.begin()->SS[0] << " " << vals.rbegin()->FF - vals.begin()->FF << endl;
    arrs.clear();
    finals.clear();
}

int main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    int T;
    cin >> T;
    while (T--) solve();
}