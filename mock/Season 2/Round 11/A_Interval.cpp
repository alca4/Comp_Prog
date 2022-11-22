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
#define INF 1000000000000000000ll
#define MOD 1000000007ll

typedef pair<int, int> pii;
typedef pair<ll, ll> pll;

ll gcd(ll a, ll b)
{
    if (a < b) swap(a, b);
    if (b == 0) return a;
    return gcd(b, a % b);
}

void solve()
{
    // cout << "===========" << endl;
    ll N;
    cin >> N;
    
    pll a1 = {INF, INF}, a2 = {INF, INF}, a3 = {INF, INF};

    // b - a = 1
    ll lo = 1;
    ll hi = 1000000000;
    while (lo <= hi)
    {
        ll mid = (lo + hi) / 2;
        // cout << mid << endl;
        if (mid * (mid + 1) < N) lo = mid + 1;
        else if (mid * (mid + 1) == N) 
        {
            a1 = pll(mid, mid + 1);
            break;
        }
        else hi = mid - 1;
    }

    // b - a = 2
    lo = 1; 
    hi = 1000000;
    while (lo <= hi)
    {
        ll mid = (lo + hi) / 2;
        ll q = mid * (mid + 1) * (mid + 2);
        if (q < N) lo = mid + 1;
        else if (q == N && mid % 2 == 1)
        {
            a2 = pll(mid, mid + 2);
            break;
        }
        else hi = mid - 1;
    }

    lo = 1; 
    hi = 1000000;
    while (lo <= hi)
    {
        ll mid = (lo + hi) / 2;
        ll q = 2ll * mid * (mid + 1) * (2 * mid + 1);
        if (q < N) lo = mid + 1;
        else if (q == N)
        {
            a2 = pll(2 * mid, 2 * mid + 2);
            break;
        }
        else hi = mid - 1;
    }

    // b - a >= 3
    for (ll a = 1; a <= 50000; a++) 
    {
        ll lcm = a * (a + 1) * (a + 2);
        if (a % 2 == 0) lcm /= 2;
        for (ll b = a + 3; b <= N; b++)
        {
            if (N % b != 0) break;
            if (lcm / gcd(lcm, b) > N / b) break;
            lcm = lcm / gcd(lcm, b) * b;
            if (a3.FF == a3.SS && a3.FF == INF && lcm == N && a != b) 
                a3 = pll(a, b);
        }
    }

    pll ans = min({a1, a2, a3});
    if (ans.FF == ans.SS && ans.FF == INF) cout << "NIE" << endl;
    else cout << ans.FF << " " << ans.SS << endl;
}

int main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    // cout << 999999ll * 1000000 * 1000001 << endl;

    int T;
    cin >> T;
    while (T--) solve();
}