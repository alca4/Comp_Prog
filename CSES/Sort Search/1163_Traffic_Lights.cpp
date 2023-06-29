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

const int MAXN = 500010;
int X, N;
multiset<int> lights;
multiset<int> segs;

int main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    int X, N;
    cin >> X >> N;
    lights.insert(0);
    lights.insert(X);
    segs.insert(X);

    while (N--)
    {
        int a = read();
        if (a == 0 || a == X) 
        {
            cout << *segs.rbegin() << " ";
            continue;
        }
        auto ub = lights.upper_bound(a);
        auto lb = --ub;
        ub++;

        // cout << *lb << " " << *ub << endl;
        segs.erase(segs.find(*ub - *lb));
        segs.insert(a - *lb);
        segs.insert(*ub - a);
        lights.insert(a);
        // for (auto n : segs) cout << n << endl;
        // cout << endl;
        cout << *segs.rbegin() << " ";
    }
    cout << endl;
    return 0;
}