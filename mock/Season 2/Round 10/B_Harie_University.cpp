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
#define MOD 10000000000000000ll

typedef pair<int, int> pii;
typedef pair<ll, ll> pll;

const int MAXN = 20010;
int N;
int subs[MAXN][2][5];
ll scores[MAXN];
ll pow23[MAXN];
ll target;
map<ll, int> s[2];

void s2(int id)
{
    for (int i = 0; i < 1024; i++)
    {
        vector<int> five(5);
        int tmp = i;
        for (int j = 0; j < 5; j++) 
        {
            five[j] = tmp % 4;
            tmp /= 4;
        }

        ll hv = 0;
        for (int j = 0; j < N; j++)
        {
            int score = 0;
            for (int k = 0; k < 5; k++) if (five[k] == subs[j][id][k]) score++;
            hv += (score * pow23[j]) % MOD;
            hv %= MOD;
        }
        s[id][hv]++;
    }
}

void solve()
{
    // cout << "===========" << endl;
    cin >> N;
    for (int i = 0; i < N; i++) 
    {
        for (int k = 0; k < 2; k++) for (int j = 0; j < 5; j++) 
        {
            char c;
            cin >> c;
            subs[i][k][j] = c - 'A';
        }
        cin >> scores[i];
    }
    ll target = 0;
    for (int j = 0; j < N; j++)
    {
        target += (scores[j] / 10 * pow23[j]) % MOD;
        target %= MOD;
    }
    // cout << target << endl;

    // cout << "T1" << endl;
    s2(0);
    // cout << "T2" << endl;
    s2(1);

    ll ans = 0;
    for (auto n1 : s[0]) for (auto n2 : s[1])
        if ((n1.FF + n2.FF) % MOD == target) ans += n1.SS * n2.SS;
    
    cout << ans << endl;

    target = 0;
    for (int i = 0; i < N; i++) 
    {
        for (int k = 0; k < 2; k++) for (int j = 0; j < 5; j++) subs[i][j][k] = 0;
        scores[i] = 0;
    }
    s[0].clear();
    s[1].clear();
}

int main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    pow23[0] = 1;
    for (int i = 1; i <= 20000; i++) 
    {
        pow23[i] = pow23[i - 1] * 23;
        pow23[i] %= MOD;
    }

    int T;
    cin >> T;
    while (T--) solve();
}