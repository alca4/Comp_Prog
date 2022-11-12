/*
  ___
 (o,o)
<  .  >
--"-"---
Rowlet is orz
*/
#include <bits/stdc++.h>
using namespace std;

#define FF first
#define SS second
#define pb push_back
#define ll __int128_t
#define ld long double
#define INF 9000000000000000000ll
#define MOD 1000000007ull
#define reset(x) memset(x, 0, sizeof(x))
#define all(x) (x).begin(), (x).end()
#define range(x, y, z) (x) + (y), (x) + (y) + (z)

typedef pair<int, int> pii;
typedef pair<ll, ll> pll;

// void maxeq(auto& a, auto b) {a = max(a, b);}
// void mineq(auto& a, auto b) {a = min(a, b);}
// void add(auto& a, auto b) {a = (a + b) % MOD;}
// void mult(auto& a, auto b) {a = (a * b) % MOD;}

const int MAXN = 200010;
int N;
ll arr[MAXN];
ll tmp[MAXN];
ll ans = INF;

ll score(ll diff)
{
    for (int i = 1; i <= N; i++) tmp[i] = arr[i] - diff * i;
 
    sort(tmp + 1, tmp + 1 + N);
    ll cost = 0;
    for (int i = 1; i <= N; i++) 
    {
        ll a = tmp[(N + 1) / 2] - tmp[i];
        if (a <= 0) a *= -1;
        cost += a;
    }
    return cost;
}

int main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    cin >> N;
    for (int i = 1; i <= N; i++) 
    {
        long long n;
        cin >> n;
        arr[i] = n;
    }

    ll lb = -20000000000000;
    ll ub = 20000000000000;
    while (lb <= ub)
    {
        ll m1 = lb + (ub - lb) / 3;
        ll m2 = ub - (ub - lb) / 3;

        ll s1 = score(m1);
        ll s2 = score(m2);
        if (s1 < s2) 
        {
            ub = m2 - 1;
            ans = min(ans, s1);
        }
        else 
        {
            lb = m1 + 1;
            ans = min(ans, s2);
        }
    }
    cout << (long long) ans << endl;
    return 0;
}