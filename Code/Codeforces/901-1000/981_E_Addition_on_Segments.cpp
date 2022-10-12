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
// #define MOD 1000000007ll

typedef pair<int, int> pii;
typedef pair<ll, ll> pll;

const int MAXN = 10010;
int N, Q;
ll MOD;
ll dp[MAXN];
vector<int> event[MAXN];

ll add(ll a, ll b) {return (a + b) % MOD;}
ll sub(ll a, ll b) {return (a - b + MOD) % MOD;}

void add(int a)
{
    for (int i = N; i >= a; i--) dp[i] = add(dp[i], dp[i - a]);
}

void del(int a)
{
    for (int i = a; i <= N; i++) dp[i] = sub(dp[i], dp[i - a]);
}

int pos[MAXN];

int main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    cin >> N >> Q;
    
    srand(time(NULL));
    MOD = (ll) (rand() + 9000000000);

    for (int i = 1; i <= Q; i++)
    {
        int a, b, v;
        cin >> a >> b >> v;
        event[a].pb(v);
        event[b].pb(-v);
    }

    dp[0] = 1;
    for (int i = 1; i <= N; i++)
    {
        sort(event[i].rbegin(), event[i].rend());
        for (int j = 0; j < event[i].size(); j++)
        {
            if (event[i][j] > 0) add(event[i][j]);
            else del(event[i][j] * -1);
            for (int k = 1; k <= N; k++) if (dp[k]) pos[k] = 1;
        }
    }

    vector<int> ans;
    for (int i = 1; i <= N; i++) if (pos[i]) ans.pb(i);
    cout << ans.size() << endl;
    for (int i = 0; i < ans.size(); i++) cout << ans[i] << " ";
    cout << endl;
    return 0;
}