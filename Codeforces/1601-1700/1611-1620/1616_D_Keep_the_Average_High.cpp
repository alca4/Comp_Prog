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

const int MAXN = 50010;
int N, X;
int arr[MAXN];
int choice[MAXN];

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
        for (int i = 1; i <= N; i++) cin >> arr[i];
        cin >> X;
        for (int i = 1; i <= N; i++) arr[i] -= X;

        choice[1] = 1;

        for (int i = 2; i <= N; i++)
        {
            if (choice[i - 1] && arr[i - 1] + arr[i] < 0) choice[i] = 0;
            else if (i >= 3 && choice[i - 1] && choice[i - 2] && 
                     arr[i - 2] + arr[i - 1] + arr[i] < 0) choice[i] = 0;
            else choice[i] = 1;
        }

        int ans = 0;
        for (int i = 1; i <= N; i++) ans += choice[i];
        cout << ans << endl;
        for (int i = 1; i <= N; i++) choice[i] = arr[i] = 0;
    }

    return 0;
} 