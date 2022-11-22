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

const int MAXN = 1000010;
ll a[MAXN], b[MAXN], c[MAXN];
int N;

int main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    cin >> N;
    for (int i = 0; i < N; i++) cin >> a[i] >> b[i];

    bool made_move = 1;
    while (made_move)
    {
        made_move = 0;
        for (int i = 0; i < N; i++)
        {
            if (a[i] >= b[i] + 1) 
            {
                ll diff = (a[i] - b[i] + 1) / 2;
                if (a[i] - 2 * diff < 0) continue;
                a[i] -= 2 * diff;
                a[(i + 1) % N] += diff;
                c[i] += diff;
                made_move = 1;
            }
        }
    }

    for (int i = 0; i < N; i++) if (a[i] != b[i]) 
    {
        cout << "No" << endl;
        return 0;
    }
    cout << "Yes" << endl;
    return 0;
}