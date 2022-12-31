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

const int MAXN = 200010;
int N, Q;
vector<int> arr;
int last_occ[256];
set<int> w[256];

void fill(int a)
{
    priority_queue<pii> pq;
    pq.push({last_occ[a], a});
    while (!pq.empty())
    {
        int n = pq.top().SS;
        pq.pop();

        for (int i = 0; i < 8; i++) 
        {
            int nb = (a ^ (1 << i));
            if (last_occ[nb] != 0 && last_occ[nb] < last_occ[a])
            {
                pq.push({last_occ[nb], nb});
                if (w[n].size()) w[nb].erase(n);
                else w[nb].insert(n);
            }
        }
    }
}

int main()
{
    srand(time(NULL));
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    cin >> N >> Q;
    arr.pb(256);
    for (int i = 1; i <= N; i++)
    {
        int a;
        cin >> a;
        arr.pb(a);
        last_occ[a] = i;
    }

    for (int i = N; i >= 1; i--) fill(arr[i]);

    // for (int i = 1; i <= N; i++) cout << (w[arr[i]].size() || (i != last_occ[arr[i]])) << " ";
    // cout << endl;

    while (Q--)
    {
        int t;
        cin >> t;
        if (t == 1)
        {
            int a;
            cin >> a;
            arr.pb(a);
            last_occ[a] = ++N;
            fill(a);

            for (int i = 1; i <= N; i++) cout << w[arr[i]].size()  << " ";
            cout << endl;
        }
        if (t == 2)
        {
            int a;
            cin >> a;
            if (a != last_occ[arr[a]] || w[arr[a]].size()) cout << "Alice" << endl;
            else cout << "Bob" << endl;
        }
    }
    return 0;
} 