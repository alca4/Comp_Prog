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
#define ull unsigned ll
#define FILENAME 
ll INF = 1000000000;
ll MOD = 1000000007;

ifstream fin(FILENAME + ".in");
ofstream fout(FILENAME + ".out");

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

const int MAXN = (1 << 18);
int arr[MAXN];
int N;

int main()
{
    srand(time(NULL));
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    cin >> N;
    for (int i = 0; i < (1 << N); i++) cin >> arr[i];
    for (int i = 1; i < (1 << N); i++) arr[i] = arr[i] ^ arr[i - 1];

    for (int i = 0; i < (1 << N); i++) for (int j = N - 1; j >= 0; j--)
        if (arr[i] & (1 << j)) arr[i] = (1 << j);
    
    int v = 0;
    for (int i = 0; i < (1 << N); i++) v = v | arr[i];

    int ans = 0;
    for (int i = 0; i < N; i++) if (!(v & (1 << i))) ans++;

    cout << (1 << ans) << endl;
    return 0;
} 