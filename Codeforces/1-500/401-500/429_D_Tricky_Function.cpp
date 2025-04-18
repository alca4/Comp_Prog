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
ll INF = 1000000000000000000;
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

const int MAXN = 100010;
int N;
pll pts[MAXN];

ll solve(int a, int b)
{
    if (b == a) return INF;
    int mid = (a + b) / 2;
    ll d = min(solve(a, mid), solve(mid + 1, b));

    // cout << a << " " << b << " " << d << endl;

    vector<pll> cand;
    for (int i = a; i <= b; i++) 
        if (abs(pts[i].FF - pts[mid].FF) <= d) cand.pb(pll(pts[i].FF, pts[i].SS));
    
    sort(cand.begin(), cand.end(), [](const pll& p1, pll& p2)
    {
        return p1.SS == p2.SS ? p1.FF < p2.FF : p1.SS < p2.SS;
    });

    for (int i = 0; i < cand.size(); i++)
        for (int j = i + 1; j <= min(i + 7, (int) cand.size() - 1); j++)
            d = min(d, (cand[i].FF - cand[j].FF) * (cand[i].FF - cand[j].FF) +
                       (cand[i].SS - cand[j].SS) * (cand[i].SS - cand[j].SS));
    
    return d;
}

int main()
{
    srand(time(NULL));
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    cin >> N;
    for (int i = 1; i <= N; i++) pts[i].FF = i;
    for (int i = 1; i <= N; i++) cin >> pts[i].SS;
    for (int i = 1; i <= N; i++) pts[i].SS = pts[i].SS + pts[i - 1].SS;

    sort(pts + 1, pts + 1 + N);

    cout << solve(1, N) << endl;
    return 0;
} 