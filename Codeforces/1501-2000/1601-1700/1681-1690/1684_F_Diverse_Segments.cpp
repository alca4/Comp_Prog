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
int N, M;
int arr[MAXN];
int start[MAXN];
vector<int> fin[MAXN];
int extend[MAXN];
map<int, vector<int>> cnt;
int LMAX, R;

int main()
{
    srand(time(NULL));
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    int T;
    cin >> T;
    while (T--)
    {
        cin >> N >> M;
        for (int i = 1; i <= N; i++) 
        {
            cin >> arr[i];
            cnt[arr[i]].pb(i);
        }
        for (int i = 1; i <= M; i++) 
        {
            int x, y;
            cin >> x >> y;
            start[x]++;
            fin[y].pb(x);
        }

        LMAX = N + 1;
        multiset<int> segments;
        for (int i = 1; i <= N; i++)
        {
            // cout << i << endl;
            for (int j = 0; j < start[i]; j++) segments.insert(i);
            int prev_occ = 0;
            if (cnt[arr[i]][0] < i) 
                prev_occ = *(--lower_bound(cnt[arr[i]].begin(), cnt[arr[i]].end(), i));
            if (segments.size() && *segments.begin() <= prev_occ)
            {
                int first_occ = *(lower_bound(cnt[arr[i]].begin(), cnt[arr[i]].end(), *segments.begin()));
                LMAX = min(LMAX, i);
                R = max(R, prev_occ);
                extend[first_occ] = i;
            }
            for (int j = 0; j < fin[i].size(); j++) 
                segments.erase(segments.find(fin[i][j]));
        }

        // cout << LMAX << " " << R << endl;

        int ans = INF;
        for (int i = 1; i <= LMAX; i++)
        {
            // cout << i << " " << R << endl;
            ans = min(ans, R - i + 1);
            R = max(R, extend[i]);
        }

        cout << max(ans, 0) << endl;

        for (int i = 1; i <= N; i++) arr[i] = start[i] = extend[i] = 0;
        for (int i = 1; i <= N; i++) fin[i].clear();
        cnt.clear();
        LMAX = 0;
        R = 0;
    }

    return 0;
} 