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
int N;
int arr[MAXN];
ll choice[31][2];

void solve(vector<int>& vals, int b)
{
    int zs = 0;
    int os = 0;
    ll si = 0;
    ll fi = 0;
    vector<int> zeroes;
    vector<int> ones;

    for (int i = 0; i < vals.size(); i++)
    {
        if (arr[vals[i]] & (1 << b)) 
        {
            os++;
            fi += zs;
            ones.pb(vals[i]);
        }
        else
        {
            zs++;
            si += os;
            zeroes.pb(vals[i]);
        }
    }
    vals.clear();

    choice[b][0] += si;
    choice[b][1] += fi;

    if (b > 0)
    {
        if (zeroes.size() > 1) solve(zeroes, b - 1);
        if (ones.size() > 1) solve(ones, b - 1);
    }
}

int main()
{
    srand(time(NULL));
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    cin >> N;
    vector<int> vals;
    for (int i = 1; i <= N; i++) 
    {
        cin >> arr[i];
        vals.pb(i);
    }

    solve(vals, 30);

    ll invs = 0;
    int ans = 0;
    for (int i = 0; i <= 30; i++) 
    {
        if (choice[i][0] <= choice[i][1]) invs += choice[i][0];
        else 
        {
            invs += choice[i][1];
            ans |= (1 << i);
        }
    }

    cout << invs << " " << ans << endl;
    return 0;
} 