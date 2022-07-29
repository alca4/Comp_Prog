#include <iostream>
#include <algorithm>
#include <vector>
using namespace std;

#define MOD 998244353 
#define ll long long

int N, M;
ll choose[200010];
ll pow2[200010];

int Euclid(int a, int b, int& c, int& d)
{
    if (a == 0)
    {
        c = 0, d = 1;
        return b;
    }

    int x1, y1;
    int gcd = Euclid(b % a, a, x1, y1);
    c = y1 - (b / a) * x1;
    d = x1;
    return gcd;
}

int Inverse(int a)
{
    int x, y;
    Euclid(a, MOD, x, y);
    return (x + MOD) % MOD;
}

int main()
{
    cin >> N >> M;
    if (N < 3)
    {
        cout << 0 << endl;
        return 0;
    }
    pow2[0] = 1;
    for (int i = 1; i <= N; i++)
        pow2[i] = (pow2[i - 1] * 2) % MOD;
    choose[0] = 1;
    int down = 1;
    int up = M;
    for (int i = 1; i <= M; i++)
    {
        choose[i] = (choose[i - 1] * up) % MOD;
        if (down != 1) choose[i] = (choose[i] * Inverse(down)) % MOD;
        up--;
        down++;
    }

    ll ans = 1;
    ans = (ans * choose[N - 1]) % MOD;
    ans = (ans * (N - 2)) % MOD;
    ans = (ans * pow2[N - 3]) % MOD;
    cout << ans << endl;

    return 0;
}