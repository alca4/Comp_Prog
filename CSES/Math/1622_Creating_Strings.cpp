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

typedef pair<int, int> pii;
typedef pair<ll, ll> pll;

int read()
{
    int a;
    cin >> a;
    return a;
}

const int MAXN = 100010;
set<string> ans;

int main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    string str;
    cin >> str;

    vector<int> indices;
    for (int i = 0; i < str.length(); i++) indices.pb(i);

    do
    {
        string tmp;
        for (int i = 0; i < indices.size(); i++) tmp += str[indices[i]];
        ans.insert(tmp);
    } while (next_permutation(all(indices)));

    cout << ans.size() << endl;
    for (auto n : ans) cout << n << endl;
    return 0;
}