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

const int MAXN = 200010;
int N;
struct Event
{
    int q, x, y, n;
} events[MAXN];

bool operator<(const Event& e1, const Event& e2)
{
    return pii(e1.x, e1.y) < pii(e2.x, e2.y);
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
        int q, x, y, n;
        cin >> q >> x >> y >> n;
        events[i] = {q, x - y, x + y, n};
    }

    sort(events + 1, events + 1 + N);

    int ans = 0;
    multiset<pii> cows;
    for (int i = 1; i <= N; i++)
    {
        if (events[i].q == 1) cows.insert({events[i].y, events[i].n});
        else
        {
            while (events[i].n > 0)
            {
                auto tmp = cows.upper_bound({events[i].y, 2000000000});
                if (tmp == cows.begin()) break;
                else --tmp;
                pii target = *tmp;
                int v = min(target.SS, events[i].n);
                cows.erase(cows.find(target));
                if (target.SS != v) cows.insert({target.FF, target.SS - v});
                events[i].n -= v;
                ans += v;
            }
        }
    }

    cout << ans << endl;
    return 0;
} 