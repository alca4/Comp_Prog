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

const int MAXN = 110;
int N, M;
vector<ll> arr[MAXN];
vector<int> divN;
vector<int> div0;
ll mv[MAXN];

int main()
{
    srand(time(NULL));
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    cin >> N >> M;
    for (int i = 0; i <= N; i++) 
    {
        string str;
        cin >> str;

        reverse(str.begin(), str.end());

        bool minus = 0;
        if (str[str.length() - 1] == '-')
        {
            minus = 1;
            str = str.substr(0, str.length() - 1);
        }

        for (int j = 0; j < str.length(); j++) 
        {
            int e = min((int) str.length() - j, 9);
            string tmp = str.substr(j, e);
            reverse(tmp.begin(), tmp.end());
            ll x = stoi(tmp);
            if (minus) x *= -1;
            arr[i].pb(x);
            j += e - 1;
        }
    }
    
    MOD = 1000000007;
    for (int k = 0; k <= N; k++) 
    {
        ll fac = 1;
        mv[k] = 0;
        for (int j = 0; j < arr[k].size(); j++) 
        {
            mv[k] = add(mv[k], mult(arr[k][j], fac));
            fac = (fac * 1000000000) % MOD;
        }
    }

    set<int> solns;
    for (int i = 1; i <= M; i++) 
    {
        ll fac = 1;
        ll tmp = 0;
        for (int j = 0; j <= N; j++) 
        {
            tmp = add(tmp, mult(mv[j], fac));
            fac = (fac * i) % MOD;
        }
        if (tmp == 0) solns.insert(i);
    }

    cout << solns.size() << endl;
    for (auto n : solns) cout << n << endl;
    return 0;
} 