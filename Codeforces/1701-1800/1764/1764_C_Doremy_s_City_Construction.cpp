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

int main()
{
    srand(time(NULL));
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    int T;
    cin >> T;
    while (T--)
    {
        int N;
        cin >> N;
        map<int, int> nums;

        for (int i = 1; i <= N; i++)
        {
            int a;
            cin >> a;
            nums[a]++;
        }

        ll ans = 0;

        ll s1 = 0;
        ll s2 = 0;
        for (auto n : nums) s2 += n.SS;

        for (auto n : nums)
        {
            ans = max(ans, s1 * s2);
            s1 += n.SS;
            s2 -= n.SS;
        }
        ans = max(ans, s1 * s2);

        if (nums.size() > 1) cout << ans << endl;
        else cout << N / 2 << endl;
    }

    return 0;
} 