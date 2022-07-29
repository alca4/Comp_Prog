/*
  ___
 (o,o)
<  .  >
--"-"---
Rowlet hard carrying
Start time:
End time:
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
using namespace std;

#define F first
#define S second
#define pb push_back
#define ll long long
#define ld long double
#define INF 1000000000
#define MOD 1000000007

typedef pair<int, int> pii;
typedef pair<ll, ll> pll;

int readInt()
{
    int a;
    cin >> a;
    return a;
}

const int MAXN = 100010;

void solve()
{
    int N;
    cin >> N;

    int arr[MAXN];
    for (int i = 1; i <= N; i++) cin >> arr[i];

    map<int, vector<int>> occ;
    for (int i = 1; i <= N; i++) occ[arr[i]].pb(i);

    int ans[MAXN];
    for (int i = 1; i <= N; i++) ans[i] = 0;
    for (auto n : occ)
    {
        int mval = 0;
        int cval = 0;
        int l = 0;
        for (int j = 0; j < n.S.size(); j++)
        {
            if (cval == 0) cval++;
            else
            {
                if ((n.S[j] - n.S[l]) % 2 != 0 || n.S[j] - n.S[l] == 1)
                {
                    l = j;
                    cval++;
                }
            }
        }
        mval = max(mval, cval);
        ans[n.F] = mval;
    }

    for (int i = 1; i <= N; i++) cout << ans[i] << " ";
    cout << endl;

    occ.clear();
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