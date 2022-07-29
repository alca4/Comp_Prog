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

const int MAXN = 100010;
int N, M;
ll quest[MAXN];
ll dmg[MAXN];
ll bdmg[MAXN];

int main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    cin >> N >> M;
    for (int i = 1; i <= N; i++) quest[i] = read();

    for (int i = 2; i <= N; i++) 
    {
        dmg[i] = dmg[i - 1];
        if (quest[i] < quest[i - 1]) dmg[i] += quest[i - 1] - quest[i];
    }

    for (int i = N - 1; i >= 1; i--) 
    {
        bdmg[i] = bdmg[i + 1];
        if (quest[i] < quest[i + 1]) bdmg[i] += quest[i + 1] - quest[i];
    }

    while (M--)
    {
        int a = read();
        int b = read();

        if (a < b) cout << dmg[b] - dmg[a] << endl;
        else cout << bdmg[b] - bdmg[a] << endl;
    }
    return 0;
}