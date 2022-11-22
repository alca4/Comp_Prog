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
#define MOD 1000000007

typedef pair<int, int> pii;
typedef pair<ll, ll> pll;

int read()
{
    int a;
    cin >> a;
    return a;
}

const int MAXN = 200010;
int N;
vector<int> child[MAXN];
ll l[MAXN], r[MAXN];
int ans = 0;

int findAns(int a)
{
    ll carry = 0;
    for (int i = 0; i < child[a].size(); i++)
        carry += findAns(child[a][i]);
    
    if (carry < l[a])
    {
        // cout << "extra for " << a << endl;
        ans++;
        carry = r[a];
    }
    return min(carry, r[a]);
}

void solve()
{
    // cout << "===" << endl;
    cin >> N;
    for (int i = 2; i <= N; i++)
        child[read()].pb(i);

    for (int i = 1; i <= N; i++) cin >> l[i] >> r[i];

    findAns(1);
    cout << ans << endl;

    for (int i = 1; i <= N; i++) l[i] = r[i] = 0;
    for (int i = 1; i <= N; i++) child[i].clear();
    ans = 0;
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