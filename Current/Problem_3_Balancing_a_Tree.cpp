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

const int MAXN = 100010;
int B;
vector<int> nbs[MAXN];
int val[MAXN];
pii bounds[MAXN];

pii DFS(int a)
{
    pii ans = bounds[a];

    for (int i = 0; i < nbs[a].size(); i++)
    {
        pii tmp = DFS(nbs[a][i]);

        ans.FF = max(ans.FF, tmp.FF);
        ans.SS = min(ans.SS, tmp.SS);
    }

    return ans;
}

void solve()
{
    int N;
    cin >> N;

    for (int i = 2; i <= N; i++)
    {
        int a;
        cin >> a;
        nbs[a].pb(i);
    }

    for (int i = 1; i <= N; i++) cin >> bounds[i].FF >> bounds[i].SS;

    pii ans = DFS(1);

    cout << max(0, (ans.FF - ans.SS + 1) / 2) << endl;
    if (B == 1) 
    {
        for (int i = 1; i <= N; i++) cout << bounds[i].FF << " ";
        cout << endl;
    }
}

int main()
{
    srand(time(NULL));
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    int T;
    cin >> T >> B;
    while (T--) solve();
} 