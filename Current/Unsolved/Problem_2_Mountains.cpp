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

const int MAXN = 2010;
int N, Q;
pii pts[MAXN];
pii s[MAXN];

int orientation(const pll& p1, const pll& p2, const pll& p3)
{
    ll v = (p2.SS - p1.SS) * (p3.FF - p2.FF) - (p2.FF - p1.FF) * (p3.SS - p2.SS);
    if (v < 0) return -1;
    if (v > 0) return 1;
    return 0;
}

int main()
{
    srand(time(NULL));
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    cin >> N;
    for (int i = 1; i <= N; i++)
    {
        cin >> pts[i].SS;
        pts[i].FF = i;
    }

    cin >> Q;
    while (Q--)
    {
        int n, d;
        cin >> n >> d;
        pts[n].SS += d;

        int ans = 0;
        int top = 0;
        for (int i = N; i >= 1; i--)
        {
            int v = 0;
            while (top >= 2 && orientation(s[top - 1], s[top], pts[i]) == -1)
            {
                ans += top - 1;
                if (s[top - 1].SS <= s[top].SS) s[top - 1] = s[top];
                top--;
            }
            s[++top] = pts[i];
        }

        cout << ans + top * (top - 1) / 2 << endl;
    }
    return 0;
} 