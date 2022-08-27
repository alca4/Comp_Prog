/*
  ___
 (o,o)
<  .  >
--"-"---
Rowlet is orz
*/
#include <bits/stdc++.h>
using namespace std;

#define FF first
#define SS second
#define pb push_back
#define ll long long
#define ld long double
#define INF 1000000000ull
#define MOD 1000000007
#define reset(x) memset(x, 0, sizeof(x))
#define all(x) (x).begin(), (x).end()
#define range(x, y, z) (x) + (y), (x) + (y) + (z)

typedef pair<int, int> pii;
typedef pair<ll, ll> pll;

int read()
{
    int a;
    cin >> a;
    return a;
}

const int MAXN = 2010;
string bessie, elsie;
ll dp[MAXN][MAXN][2];
int N, I, J;

void read(string &s) {
	string _s;
	cin >> _s;
	for (char c : _s) {
		if (c == '1') continue;
		if (c == '0') s.clear();
		if (c != '+') c = '2';
		s += c;
	}
}

void solve()
{
    // cout << "===========" << endl;
    cin >> N;
    string S1;
    cin >> S1;
    for (int i = 0; i < N; i++)
    {
        if (S1[i] == '1') continue;
		if (S1[i] == '0') bessie.clear();
		if (S1[i] != '+') S1[i] = '2';
		bessie += S1[i];
    }

    string S2;
    cin >> S2;
    for (int i = 0; i < N; i++)
    {
        if (S2[i] == '1') continue;
		if (S2[i] == '0') elsie.clear();
		if (S2[i] != '+') S2[i] = '2';
		elsie += S2[i];
    }

    I = bessie.length(), J = elsie.length();

    dp[0][0][0] = 1;
    for (int i = 0; i <= I; i++)
    {
        for (int j = 0; j <= J; j++)
        {
            if (j < J) 
            {
                dp[i][j + 1][1] += dp[i][j][0] + dp[i][j][1];
                dp[i][j + 1][1] %= MOD;
            }
            if (i < I) 
            {
                dp[i + 1][j][0] += dp[i][j][0];
                dp[i][j + 1][0] %= MOD;
            }
            if (i < I && elsie[j - 1] != bessie[i]) 
            {
                dp[i + 1][j][0] += dp[i][j][1];
                dp[i][j + 1][1] %= MOD;
            }
        }
    }
    cout << (dp[I][J][0] + dp[I][J][1]) % MOD << endl;
    for (int i = 0; i <= I; i++) for (int j = 0; j <= J; j++)
        dp[i][j][0] = dp[i][j][1] = 0;
    bessie.clear();
    elsie.clear();
}

int main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    int T;
    cin >> T;
    while (T--) solve();
}