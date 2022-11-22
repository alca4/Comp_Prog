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

ll add(const ll& a, const ll& b) {return (a + b) % MOD;}
ll mult(const ll& a, const ll& b) {return (a * b) % MOD;}

ll modInverse(ll a)
{
    ll n = MOD - 2;
    ll ans = 1;

    ll binexp[64];
    binexp[0] = a;
    for (int i = 1; i < 64; i++) binexp[i] = mult(binexp[i - 1], binexp[i - 1]);

    while (n > 0)
    {
        int id = (int) log2(n & -n);
        ans = mult(ans, binexp[id]);
        n -= (n & -n);
    }

    return ans;
}

const int MAXN = 25010;
bitset<MAXN> ans;

void solve()
{
    int N;
    cin >> N;
    int arr[MAXN];
    for (int i = 1; i <= N; i++) cin >> arr[i];

    sort(arr + 1, arr + 1 + N);

    int need = 0;
    ans[0] = 1;
    for (int i = 1; i <= N; i++)
    {
        if (!ans[arr[i]])
        {
            for (int j = 1; j <= (MAXN - 10) / arr[i]; j++) ans |= (ans << arr[i]);
            // cout << ans << endl;
            need++;
        }
    }

    cout << need << endl;
    ans.reset();
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