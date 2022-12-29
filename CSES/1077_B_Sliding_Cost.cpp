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
int N, K;
int arr[MAXN];

int main()
{
    srand(time(NULL));
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    cin >> N >> K;
    for (int i = 1; i <= N; i++) cin >> arr[i];
    
    ll cost = 0;
    multiset<ll> vals;
    multiset<ll> v1;
    multiset<ll> v2;
    for (int i = 1; i <= K; i++) vals.insert(arr[i]);

    for (int i = 1; i <= (K + 1) / 2; i++) 
    {
        v1.insert(*vals.begin());
        vals.erase(vals.begin());
    }

    for (int i = (K + 1) / 2 + 1; i <= K; i++) 
    {
        v2.insert(*vals.begin());
        vals.erase(vals.begin());
    }

    for (auto n : v1) cost += abs(*v1.rbegin() - n);
    for (auto n : v2) cost += abs(*v1.rbegin() - n);
    cout << cost << " ";

    int d = (int) v2.size() - (int) v1.size();

    for (int i = 2; i <= N - K + 1; i++) 
    {
        ll median = *v1.rbegin();
        cost -= abs(median - arr[i - 1]);
        cost += abs(median - arr[i + K - 1]);

        if (v1.find(arr[i - 1]) == v1.end()) v2.erase(v2.find(arr[i - 1]));
        else v1.erase(v1.find(arr[i - 1]));

        if ((v1.size() == 0 && v2.size() == 0) || 
            (v1.size() != 0 && arr[i + K - 1] <= *v1.rbegin())) v1.insert(arr[i + K - 1]);
        else v2.insert(arr[i + K - 1]);

        if ((int) v2.size() - (int) v1.size() == d + 2)
        {
            v1.insert(*v2.begin());
            v2.erase(v2.begin());
        }
        else if ((int) v2.size() - (int) v1.size() == d - 2)
        {
            v2.insert(*v1.rbegin());
            v1.erase(--v1.end());
        }
        
        // for (auto n : v1) cout << n << " ";
        // for (auto n : v2) cout << n << " ";

        // cout << median << " " << *v1.rbegin() << " ";

        if (median <= *v1.rbegin())
        {
            // cout << "c1 ";
            cost += 1ll * (v1.size() - 1) * (*v1.rbegin() - median);
            cost -= 1ll * (v2.size() + 1) * (*v1.rbegin() - median);
        }

        else if (median <= *v2.begin())
        {
            // cout << "c2 ";
            cost += 1ll * (v1.size()) * (*v1.rbegin() - median);
            cost -= 1ll * (v2.size()) * (*v1.rbegin() - median);
        }

        else
        {
            cost += 1ll * v1.size() * (*v1.rbegin() - median);
            cost -= 1ll * v2.size() * (*v1.rbegin() - median);
        }

        cout << cost << " ";
    }
    cout << endl;
    return 0;
} 