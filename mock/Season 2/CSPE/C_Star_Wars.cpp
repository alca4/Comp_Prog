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

ll rand32()
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

const int MAXN = 500010;
int N, M, Q;
ll good = 0;
ll arr[MAXN];
ll in[MAXN];
ll cur_in[MAXN];
ll cur, ans;

int main()
{
    srand(time(NULL));
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    cin >> N >> M;
    for (int i = 1; i <= N; i++) 
    {
        arr[i] = rand64() % 1000000000000000;
        ans += arr[i];
    }
    for (int i = 1; i <= M; i++)
    {
        int a, b;
        cin >> a >> b;
        in[b] += arr[a];
        cur_in[b] += arr[a];
        cur += arr[a];
    }

    cin >> Q;
    while (Q--)
    {
        int t;
        cin >> t;
        if (t == 1) 
        {
            int a, b;
            cin >> a >> b;
            cur -= arr[a];
            cur_in[b] -= arr[a];
        }
        if (t == 2)
        {
            int a;
            cin >> a;
            cur -= cur_in[a];
            cur_in[a] = 0;
        }
        if (t == 3) 
        {
            int a, b;
            cin >> a >> b;
            cur += arr[a];
            cur_in[b] += arr[a];
        }
        if (t == 4)
        {
            int a;
            cin >> a;
            cur += in[a] - cur_in[a];
            cur_in[a] = in[a];
        }
        if (cur == ans) cout << "YES" << endl;
        else cout << "NO" << endl;
    }
    return 0;
} 