/*
  ___
 (o,o)
<  .  >
--"-"---
Rowlet is orz
  _      _      _
>(.)__ <(.)__ =(.)__
 (___/  (___/  (___/
I am dum duck
*/
#include <bits/stdc++.h>
using namespace std;

#define FF first
#define SS second
#define pb push_back
#define ll long long
#define ld long double
#define INF 1000000000ll
#define MOD 1000000007ll

typedef pair<int, int> pii;
typedef pair<ll, ll> pll;

const int MAXN = 3010;
int N;
bitset<MAXN * MAXN> dp;
int arr[MAXN];
int S;

int main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    cin >> N;
    for (int i = 1; i <= N; i++) 
    {
        cin >> arr[i];
        S += arr[i];
    }

    dp[0] = 1;
    for (int i = 1; i <= N; i++) dp |= (dp << arr[i]);

    for (int i = S / 2; i >= 0; i--) if (dp[i]) 
    {
        cout << S - i << endl;
        return 0;
    }
}