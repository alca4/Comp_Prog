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

const int MAXN = 1010;
int N;
map<int, int> edges;
map<int, vector<int>> edgelist;

int main()
{
    srand(time(NULL));
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    int ans = 1;
    cin >> N;
    for (int i = 1; i < N; i++)
    {
        int x, y;
        cin >> x >> y;
        if (x < y) swap(x, y);
        if (x != N || x == y) ans = 0;
        edges[y]++;
        if (!edgelist.count(y)) edgelist[y].pb(N);
    }

    for (int i = 1; i < N; i++)
    {
        while (!edges.empty() && edgelist[edges.begin()->FF].size() == edges.begin()->SS) 
        {
            edges.erase(edges.begin());
        }
        if (!edgelist.count(i)) 
        {
            if (edges.empty()) 
            {
                ans = 0;
                break;
            }
            else edgelist[edges.begin()->FF].pb(i);
        }
        else if (!edges.empty() && i == edges.begin()->FF && edgelist[i].size() < edges[i])
        {
            ans = 0;
            break;
        }
    }

    for (auto n : edgelist) edgelist[n.FF].pb(n.FF);

    if (!ans) cout << "NO" << endl;
    else
    {
        cout << "YES" << endl;
        for (auto n : edgelist)
            for (int i = 1; i < n.SS.size(); i++)
                cout << n.SS[i - 1] << " " << n.SS[i] << endl;
    }
    return 0;
}