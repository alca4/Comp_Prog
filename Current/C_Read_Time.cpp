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
int N, M;
ll heads[MAXN];
ll theads[MAXN];
ll targets[MAXN];

int main()
{
    srand(time(NULL));
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    cin >> N >> M;
    for (int i = 1; i <= N; i++) cin >> heads[i];
    for (int i = 1; i <= M; i++) cin >> targets[i];
    heads[0] = LINF;
    heads[N + 1] = LINF;

    ll ans = 0;
    ll lb = 0, ub = INF * 1000000;
    while (lb <= ub)
    {
        ll mid = (lb + ub) >> 1;
        cout << "==========" << endl;
        cout << mid << endl;

        for (int i = 1; i <= N; i++) theads[i] = heads[i];

        int last_move = 0;
        bool ok = 1;
        ll dist = 0;
        for (int i = 1; i <= M; i++)
        {
            cout << i << endl;
            auto it = lower_bound(theads + 1, theads + 1 + N, targets[i]);
            ll before = *(it - 1);
            ll after = *it;
            
            // cout << before << " " << after << endl;
            // cout << "dist is: " << dist << endl;
            
            if (dist > mid) ok = 0;

            ll tdist = dist;
            dist = LINF;
            if (tdist != 0 && i > 1)
            {
                // if (tdist + targets[i] - targets[i - 1]) cout << "use back" << endl;
                dist = min(dist, tdist + targets[i] - targets[i - 1]);
            }
            if (before != LINF && before != targets[i - 1] && i > 1) 
            {
                // if (targets[i] - before) cout << "use before" << endl;
                dist = min(dist, targets[i] - before);
                last_move = distance(theads + 1, it - 1);
            }
            if (after != LINF && i < M) 
            {
                // if (after - targets[i]) cout << "use after" << endl;
                dist = min(dist, after - targets[i]);
                last_move = distance(theads + 1, it);
            }
            ll x = targets[i];
            if (theads[last_move + 1])
            i = max(i, (int) distance(targets + 1, upper_bound(targets + 1, targets + 1 + M, theads[last_move + 1])));
            theads[last_move + 1] = x;
        }
        if (dist > mid && dist != LINF) ok = 0;

        if (ok) 
        {
            ub = mid - 1;
            ans = mid;
        }
        else lb = mid + 1;
    }

    cout << ans << endl;
    return 0;
}