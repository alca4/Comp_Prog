#include <iostream>
#include <algorithm>
#include <vector>
#include <cmath>
using namespace std;

#define ll long long
#define P 1000000009

int comp[100010];
vector<int> primes;

ll pows[50][80];

ll power(ll a, ll k)
{
    ll ans = 1;
    while (k > 0)
    {
        int b = log2(k & -k) + 1;
        ans *= pows[a][b];
        ans %= P;
        k -= (k & -k);
    }
    return ans;
}

void solve()
{
    ll K, D, M;
    cin >> K >> D >> M;

    ll dfac[10010];
    ll mfac[10010];
    for (int i = 0; i <= 10000; i++) dfac[i] = mfac[i] = 0;

    for (int i = 0; i < primes.size(); i++)
    {
        if (D == 1) break;
        while (D % primes[i] == 0)
        {
            D /= primes[i];
            dfac[i]++;
        }
    }
    if (D > 1) dfac[10000] = D;

    // for (int i = 0; i < 2; i++)
    //     cout << dfac[i] << " ";
    // cout << endl;

    for (int i = 0; i < primes.size(); i++)
    {
        if (M == 1) break;
        while (M % primes[i] == 0)
        {
            M /= primes[i];
            mfac[i]++;
        }
    }
    if (M > 1) mfac[10000] = M;

    // for (int i = 0; i < 2; i++)
    //     cout << mfac[i] << " ";
    // cout << endl;

    ll ans = 1;
    for (int i = 0; i < primes.size(); i++)
    {
        ll d = mfac[i] - dfac[i] + 1;
        if (d <= 0) 
        {
            cout << 0 << endl;
            return;
        }

        ll n1 = power(d, K) % P;
        ll n2 = 0;
        if (d > 1) n2 = 2 * power(d - 1, K) % P;
        ll n3 = 0;
        if (d > 2) n3 = power(d - 2, K) % P;

        ans *= ((n1 - n2 + n3 + P) % P);
        ans %= P;
    }
    if (dfac[10000] != mfac[10000])
    {
        cout << 0 << endl;
        return;
    }
    
    cout << ans << endl;
}

int main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    for (int i = 2; i <= 100000; i++)
    {
        if (!comp[i]) 
        {
            primes.push_back(i);
            for (int j = i; j <= 100000; j += i)
                comp[j] = 1;
        }
    }

    for (int i = 1; i <= 40; i++)
    {
        pows[i][0] = 1;
        pows[i][1] = i;
        for (int j = 2; j <= 70; j++)
        {
            pows[i][j] = (pows[i][j - 1] * pows[i][j - 1]);
            pows[i][j] %= P;
        }
    }

    int T;
    cin >> T;
    while (T--) solve();
}