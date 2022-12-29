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

const int MAXN = 310;
int N;
struct Info
{
    int c, o, v, l;
} arr[MAXN];
int dp[MAXN * MAXN * 10];

bool operator<(const Info& i1, const Info& i2)
{
    if (i1.v > 0 && i2.v <= 0) return 1;
    else if (i1.v <= 0 && i2.v > 0) return 0;
    else if (i1.v > 0 && i2.v >= 0) return i1.c < i2.c;
    else return i1.o > i2.o;
}

int main()
{
    srand(time(NULL));
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    cin >> N;
    int totlen = 0;
    for (int i = 1; i <= N; i++)
    {
        string str;
        cin >> str;
        arr[i].l = str.length();
        totlen += str.length();

        for (int j = str.length() - 1; j >= 0; j--) 
        {
            if (j < str.length() - 1 && str[j] == '(' && str[j + 1] == ')') 
                str.erase(j, 2);
        }

        for (int j = 0; j < str.length(); j++)
        {
            if (str[j] == '(') arr[i].o++;
            else arr[i].c++;
        }

        arr[i].v = arr[i].o - arr[i].c;
    }

    sort(arr + 1, arr + 1 + N);

    dp[0] = 1;
    for (int i = 1; i <= N; i++)
    {
        if (arr[i].o > arr[i].c)
        {
            for (int j = totlen; j >= 0; j--)
            {
                if (j - arr[i].v >= arr[i].c && dp[j - arr[i].v])
                {
                    // cout << "going to " << j << " from " << j - arr[i].v << endl;
                    dp[j] = max(dp[j], dp[j - arr[i].v] + arr[i].l);
                }
            }
        }
        else
        {
            for (int j = 0; j <= totlen; j++)
            {
                if (j - arr[i].v >= arr[i].c && dp[j - arr[i].v])
                {
                    // cout << "going to " << j << " from " << j - arr[i].v << endl;
                    dp[j] = max(dp[j], dp[j - arr[i].v] + arr[i].l);
                }
            }
        }
    }

    cout << dp[0] - 1 << endl;
    return 0;
} 