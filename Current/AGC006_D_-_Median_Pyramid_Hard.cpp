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
ll LINF = 1000000000000000000;
ll MOD = 1000000007;
// ll MOD = 998244353;

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

const int MAXN = 100010;
int N;
int arr[2 * MAXN];
int tmp[2 * MAXN];

int main()
{
    srand(time(NULL));
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    cin >> N;
    for (int i = 1; i < 2 * N; i++) cin >> arr[i];

    int lb = 1, ub = 2 * N - 1;
    int fans;
    while (lb <= ub)
    {
        int mid = (lb + ub) / 2;

        for (int i = 1; i < 2 * N; i++) tmp[i] = arr[i] > mid;

        set<pii> ranges;

        int s = 1;
        for (int i = 1; i < 2 * N; i++)
        {
            while (i < 2 * N && tmp[i] == tmp[s]) i++;
            if (i - s > 1) ranges.insert({s, i - 1});
            s = i;
        }

        int best_dist = 2 * N;
        int ans;
        for (auto n : ranges)
        {
            if (n.FF <= N && N <= n.SS) 
                best_dist = 0, ans = tmp[N];
            if (n.SS < N && N - n.SS < best_dist)
                best_dist = N - n.SS, ans = tmp[n.SS];
            if (n.FF > N && n.FF - N < best_dist)
                best_dist = n.FF - N, ans = tmp[n.FF];
        }
        
        if (ranges.empty()) 
            ans = tmp[1];

        if (ans) lb = mid + 1;
        else fans = mid, ub = mid - 1;
    }

    cout << fans << endl;
    return 0;
} 