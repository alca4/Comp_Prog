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

const int MAXN = 300010;
int N, Q;
int arr[MAXN];
set<pii> itvs;
set<pii> freq[MAXN];

int main()
{
    srand(time(NULL));
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    cin >> N;
    for (int i = 1; i <= N; i++) cin >> arr[i];

    int s = 1, e = 1;
    for (int i = 1; i <= N; i++)
    {
        if (arr[e] != arr[s]) 
        {
            itvs.insert({s, e - 1});
            freq[arr[s]].insert({s, e - 1});
            s = e;
        }
        e++;
    }
    itvs.insert({s, e - 1});
    freq[arr[s]].insert({s, e - 1});

    cin >> Q;
    while (Q--)
    {
        int c;
        cin >> c;
        if (freq[c].size() <= 1) continue;
        pii s = *freq[c].begin();
        pii e = *(--freq[c].end());

        vector<pii> remove;
        for (auto it = itvs.find(s); it != itvs.find(e); ++it)
        {
            pii val = *it;
            remove.pb(val);
            freq[arr[val.FF]].erase(val);
        }
        remove.pb(e);
        freq[c].erase(freq[c].find(e));

        for (int i = 0; i < remove.size(); i++) 
            itvs.erase(remove[i]);

        itvs.insert({s.FF, e.SS});
        freq[c].insert({s.FF, e.SS});
    }

    for (auto n : itvs)
        for (int i = n.FF; i <= n.SS; i++) cout << arr[n.FF] << " ";
    cout << endl;
    return 0;
} 