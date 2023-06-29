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
int N, M;
int arr[MAXN];
int id[MAXN];

int check(int a) {return id[a] <= id[a - 1];}

int main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    cin >> N >> M;
    for (int i = 1; i <= N; i++) cin >> arr[i];
    for (int i = 1; i <= N; i++) id[arr[i]] = i;
    id[0] = 0, id[N + 1] = INF;

    int cost = 1;
    for (int i = 2; i <= N; i++) 
        cost += check(i);

    while (M--)
    {
        int a = read(), b = read();

        if (arr[a] > arr[b]) swap(a, b);
        int d = check(arr[a]) + check(arr[a] + 1) + check(arr[b]) + check(arr[b] + 1);
        if (arr[a] + 1 == arr[b]) 
        {
            // cout << "dup? " << endl;
            d -= check(arr[b]);
        }

        // cout << "at " << a << " is " << arr[a] << endl;
        // cout << "at " << b << " is " << arr[b] << endl;

        swap(id[arr[a]], id[arr[b]]);
        swap(arr[a], arr[b]);
        swap(a, b);

        int d2 = check(arr[a]) + check(arr[a] + 1) + check(arr[b]) + check(arr[b] + 1);
        // cout << "at " << a << " is " << arr[a] << endl;
        // cout << "at " << b << " is " << arr[b] << endl;
        if (arr[a] + 1 == arr[b]) 
        {
            // cout << "dup! " << endl;
            d2 -= check(arr[b]);
        }

        // cout << d << " " << d2 << endl;
        cost = cost - d + d2;
        cout << cost << endl;
    }
    return 0;
}