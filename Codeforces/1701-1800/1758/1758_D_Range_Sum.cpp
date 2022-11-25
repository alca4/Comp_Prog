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
        ll N;
        cin >> N;

        if (N % 2 == 0)
        {
            int x = N / 2;
            for (int i = N - x; i < N; i++) cout << i << " ";
            for (int i = N + x; i > N; i--) cout << i << " ";
            cout << endl;
        }
        else
        {
            vector<ll> vec;
            ll x = ((N + 2) * (N + 2)) % N;
            ll y = N / 2;
            ll r = ((N + 2) * (N + 2)) / N + y;
            for (int i = 1; i <= x; i++) 
            {
                vec.pb(r + 1);
                r--;
            }
            r = ((N + 2) * (N + 2)) / N - y;
            for (int i = x + 1; i <= N; i++)
            {
                vec.pb(r);
                r++;
            }
            
            sort(vec.begin(), vec.end());
            while (N + 2 - (vec[N - 1] - vec[0]) >= 2) 
            {
                vec[N - 1]++;
                vec[0]--;
            }
            for (int i = 0; i < N; i++) cout << vec[i] << " ";
            cout << endl;
        }
    }
    return 0;
} 