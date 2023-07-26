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

Praise to the Cow God
*/
#include <bits/stdc++.h>
using namespace std;

#define FF first
#define SS second
#define pb push_back
#define ll long long
#define ld long double
#define ull unsigned ll
ll INF = 1000000000;
ll MOD = 1000000007;

ifstream fin(".in");
ofstream fout(".out");

typedef pair<int, int> pii;
typedef pair<ll, ll> pll;

ll add(const ll& a, const ll& b) {return (a + b) % MOD;}
ll sub(const ll& a, const ll& b) {return (a + MOD - b) % MOD;}
ll mult(const ll& a, const ll& b) {return (a * b) % MOD;}
ll power(ll a, ll b)
{
    ll n = b;
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
ll divide(const ll& a, const ll& b) {return (a * power(b, MOD - 2)) % MOD;}

int rand32()
{
    int a = rand();
    int b = rand();
    return (a << 16) | b;
}

ll rand64()
{
    ll a = rand32();
    ll b = rand32();
    return (a << 32) | b;
}

const int MAXN = 200010;
int N;
int a[MAXN];
int b[MAXN];
map<int, int> occ;

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
        cin >> N;
        for (int i = N; i >= 1; i--) cin >> a[i];
        for (int i = N; i >= 1; i--) cin >> b[i];

        int ans = 1;
        int i = 1, j = 1;
        while (i <= N && j <= N)
        {
            while (i <= N && a[i] != b[j])
            {
                occ[a[i]]++;
                if (occ[a[i]] > 0) 
                {
                    ans = 0;
                    break;
                }
                i++;
            }

            if (!ans) break;

            int k = j;
            while (k <= N && b[j] == b[k])
            {
                occ[b[k]]--;
                k++;
            }
            j = k;
            
            if (j == N + 1)
            {
                while (i <= N)
                {
                    occ[a[i]]++;
                    if (occ[a[i]] > 0) ans = 0;
                    i++;
                }
            }
        }

        if (ans) cout << "YES" << endl;
        else cout << "NO" << endl;

        for (int i = 1; i <= N; i++) a[i] = b[i] = 0;
        occ.clear();
    }

    return 0;
} 