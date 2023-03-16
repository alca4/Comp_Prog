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
#define MOD 998244353ll

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

ll N, D;

ll mat[2][2];
ll ans = 1;

void calc()
{
    ll n = N;
    ll res[2][2];
    res[0][0] = res[1][1] = 1;
    res[0][1] = res[1][0] = 0;

    ll binexp[64][2][2];
    for (int i = 0; i < 2; i++) for (int j = 0; j < 2; j++) binexp[0][i][j] = mat[i][j];
    for (int i = 1; i < 64; i++) 
    {
        ll tmp[2][2];
        for (int k = 0; k < 2; k++) for (int j = 0; j < 2; j++) tmp[k][j] = 0;
        tmp[0][0] = add(mult(binexp[i - 1][0][0], binexp[i - 1][0][0]), mult(binexp[i - 1][0][1], binexp[i - 1][1][0]));
        tmp[0][1] = add(mult(binexp[i - 1][0][0], binexp[i - 1][0][1]), mult(binexp[i - 1][0][1], binexp[i - 1][1][1]));
        tmp[1][0] = add(mult(binexp[i - 1][1][0], binexp[i - 1][0][0]), mult(binexp[i - 1][1][1], binexp[i - 1][1][0]));
        tmp[1][1] = add(mult(binexp[i - 1][1][0], binexp[i - 1][0][1]), mult(binexp[i - 1][1][1], binexp[i - 1][1][1]));

        for (int k = 0; k < 2; k++) for (int j = 0; j < 2; j++) binexp[i][k][j] = tmp[k][j];
    }

    while (n > 0)
    {
        int id = (int) log2(n & -n);

        ll tmp[2][2];
        for (int k = 0; k < 2; k++) for (int j = 0; j < 2; j++) tmp[k][j] = 0;
        tmp[0][0] = add(mult(res[0][0], binexp[id][0][0]), mult(res[0][1], binexp[id][1][0]));
        tmp[0][1] = add(mult(res[0][0], binexp[id][0][1]), mult(res[0][1], binexp[id][1][1]));
        tmp[1][0] = add(mult(res[1][0], binexp[id][0][0]), mult(res[1][1], binexp[id][1][0]));
        tmp[1][1] = add(mult(res[1][0], binexp[id][0][1]), mult(res[1][1], binexp[id][1][1]));

        for (int k = 0; k < 2; k++) for (int j = 0; j < 2; j++) res[k][j] = tmp[k][j];
        n -= (n & -n);
    }

    ans = add(ans, add(res[0][0], res[1][1]));
}

int main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    cin >> N >> D;

    ll choose = 1;
    ll choosem1 = 0;
    ll choosem2 = 0;
    for (ll i = 1; i <= D + 1; i++)
    {
        choosem2 = choosem1;
        choosem1 = choose;
        choose = mult(choose, D - i);
        choose = mult(choose, modInverse(i));
        
        mat[0][0] = choose;
        mat[0][1] = choosem1;
        mat[1][0] = choosem1;
        mat[1][1] = choosem2;

        calc();
    }

    cout << ans << endl;
    return 0;
} 