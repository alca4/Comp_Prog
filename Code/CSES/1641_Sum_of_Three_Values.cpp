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
ll X;
ll arr[MAXN];
map<ll, vector<int>> vals;

int main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    cin >> N >> X;
    for (int i = 1; i <= N; i++) cin >> arr[i];
    for (int i = 1; i <= N; i++) vals[arr[i]].pb(i);

    for (int i = 1; i <= N; i++)
        for (int j = i + 1; j <= N; j++)
        {
            int last = X - arr[i] - arr[j];
            if (vals.find(last) == vals.end()) continue;
            if (last == arr[i]) 
            {
                if (arr[i] == arr[j]) 
                {
                    if (vals[last].size() < 3) continue;
                    cout << vals[last][0] << " " << vals[last][1] << " " << 
                            vals[last][2] << endl;
                    return 0;
                }
                if (vals[last].size() < 2) continue;
                cout << vals[last][0] << " " << vals[last][1] << " " << vals[arr[j]][0] << endl;
                return 0;
            }
            if (last == arr[j])
            {
                if (vals[last].size() < 2) continue;
                cout << vals[last][0] << " " << vals[last][1] << " " << vals[arr[i]][0] << endl;
                return 0;
            }
            cout << i << " " << j << " " << vals[last][0] << endl;
            return 0;
        }
    cout << "IMPOSSIBLE" << endl;
    return 0;
}