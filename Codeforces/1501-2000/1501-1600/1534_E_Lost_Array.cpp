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

const int MAXN = 510;
int N, K;
queue<int> select;
queue<int> unselect;
int vis[MAXN];
int pre[MAXN];

int main()
{
    srand(time(NULL));
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    cin >> N >> K;

    for (int i = 1; i <= N; i++) unselect.push(i);
    
    vis[K] = 1;
    queue<int> q;
    q.push(K);
    while (!q.empty())
    {
        int n = q.front();
        q.pop();

        for (int i = min(K, n); i >= max(0, K - (N - n)); i--)
        {
            int m = n + K - 2 * i;
            if (m >= 1 && m <= N && !vis[m]) 
            {
                q.push(m);
                vis[m] = 1;
                pre[m] = n;
            }
        }
    }

    if (!vis[N])
    {
        cout << -1 << endl;
        return 0;
    }

    stack<int> vals;
    int x = N;
    while (x != 0)
    {
        vals.push(x);
        x = pre[x];
    }
    vals.push(0);

    int ans = 0;

    while (vals.size() > 1)
    {
        int a = vals.top();
        vals.pop();
        int b = vals.top();
        vals.pop();

        int x = (K - (b - a)) / 2;
        cout << "? ";
        for (int i = 1; i <= x; i++)
        {
            cout << select.front() << " ";
            unselect.push(select.front());
            select.pop();
        }

        for (int i = x + 1; i <= K; i++)
        {
            cout << unselect.front() << " ";
            select.push(unselect.front());
            unselect.pop();
        }
        cout << endl;

        int n;
        cin >> n;
        ans ^= n;

        vals.push(b);
    }

    cout << "! " << ans << endl;
    return 0;
} 