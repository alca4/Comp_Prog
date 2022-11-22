/*
  ___
 (o,o)
<  .  >
--"-"---
Rowlet is orz
*/
#include <bits/stdc++.h>
using namespace std;
 
#define FF first
#define SS second
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
ll arr[MAXN];
 
int main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
 
    int N, Q;
    cin >> N >> Q;
    for (int i = 1; i <= N; i++) arr[i] = arr[i - 1] ^ read();
 
    while (Q--)
    {
        int a = read(), b = read();
        cout << (arr[b] ^ arr[a - 1]) << endl;
    }
    return 0;
}