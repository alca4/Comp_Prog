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

int read()
{
    int a;
    cin >> a;
    return a;
}

const int MAXN = 200010;
int N;
map<int, vector<int>> mappy;
set<int> avail;
struct Interval
{
    int a, b, id;
}itv[MAXN];
int ans[MAXN];

int main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    cin >> N;
    for (int i = 1; i <= N; i++) itv[i] = {read(), read(), i};
    for (int i = 1; i <= N; i++)
    {
        mappy[itv[i].a].pb(itv[i].id);
        mappy[itv[i].b + 1].pb(itv[i].id * -1);
    }

    int K = 0;
    int sum = 0;
    for (auto n : mappy) 
    {
        for (int i = 0; i < n.second.size(); i++)
        {
            if (n.second[i] > 0) sum++;
            else sum--;
        }
        K = max(sum, K);
    }
    cout << K << endl;

    for (int i = 1; i <= N; i++) avail.insert(i);

    for (auto n : mappy) 
    {
        sort(all(n.second));
        for (int i = 0; i < n.second.size(); i++)
        {
            // cout << n.second[i] << " ";
            if (n.second[i] > 0)
            {
                ans[n.second[i]] = *avail.begin();
                avail.erase(*avail.begin());
            }
            else
                avail.insert(ans[n.second[i] * -1]);
        }
        // cout << endl;
    }

    for (int i = 1; i <= N; i++) cout << ans[i] << " ";
    cout << endl;
    return 0;
}