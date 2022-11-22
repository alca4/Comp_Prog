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
int N, K;
int arr[MAXN];
multiset<int> vals;

int main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    cin >> N >> K;
    for (int i = 1; i <= N; i++) cin >> arr[i];

    for (int i = 1; i <= K; i++) vals.insert(arr[i]);
    auto med = vals.begin();
    if (K % 2 == 1) for (int i = 1; i <= K / 2; i++) med++;
    else for (int i = 1; i < K / 2; i++) med++;
    cout << *med << " ";
    
    for (int i = K + 1; i <= N; i++)
    {
        vals.insert(arr[i]);
        if (arr[i - K] == *med)
        {
            if (arr[i] < *med) med--;
            else med++;
        }
        else
        {
            int a = arr[i - K] < *med;
            int b = arr[i] < *med;

            if (a && !b) med++;
            if (!a && b) med--;
        }

        auto it = vals.find(arr[i - K]);
        if (it == med)
        {
            med++;
            vals.erase(it);
        }
        else vals.erase(it);
        cout << *med << " ";
    }
    cout << endl;
    return 0;
}