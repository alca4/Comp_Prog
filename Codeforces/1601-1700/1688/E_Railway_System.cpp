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

const int MAXN = 210, MAXM = 510;
int N, M;
pii edges[MAXM];
int sum[MAXM];

int main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    cin >> N >> M;
    string str;
    for (int i = 1; i <= M; i++) str += '0';
    for (int i = 1; i <= M; i++)
    {
        str[i - 1] = '1';
        cout << "? " << str << endl;
        cout.flush();
        edges[i] = {read(), i};
        str[i - 1] = '0';
    }

    sort(edges + 1, edges + 1 + M);

    int ans = 0;
    for (int i = 1; i <= M; i++)
    {
        str[edges[i].S - 1] = '1';
        cout << "? " << str << endl;
        cout.flush();
        cin >> sum[i];
    }

    for (int i = 1; i <= M; i++) 
        if (sum[i] - sum[i - 1] == edges[i].F) ans += edges[i].F;
    cout << "! " << ans << endl;
    cout.flush();
    return 0;
}