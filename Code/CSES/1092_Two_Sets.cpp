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
#define print(a, x, y) {for (int i = x; i <= y; i++) cout << a[i] << " "; cout << endl;}

typedef pair<int, int> pii;
typedef pair<ll, ll> pll;

int read()
{
    int a;
    cin >> a;
    return a;
}

const int MAXN = 100010;

int main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    ll N;
    cin >> N;

    ll sum = (N * N + N) / 2;
    if (sum % 2 != 0) cout << "NO" << endl;
    else
    {
        cout << "YES" << endl;
        if (N % 2 == 0)
        {
            cout << N / 2 << endl;
            for (int i = 1; i <= N / 2; i += 2) cout << i << " " << N + 1 - i << " ";
            cout << endl;
            cout << N / 2 << endl;
            for (int i = 2; i <= N / 2; i += 2) cout << i << " " << N + 1 - i << " ";
        }
        else
        {
            cout << N / 2 + 1 << endl;
            cout << "1 2 ";
            for (int i = 4; i <= (N - 3) / 2 + 3; i += 2) cout << i << " " << N + 4 - i << " ";
            cout << endl;
            cout << N / 2 << endl;
            cout << "3 ";
            for (int i = 5; i <= (N - 3) / 2 + 3; i += 2) cout << i << " " << N + 4 - i << " ";
        }
        cout << endl;
    }
}