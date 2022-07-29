#include<iostream>
#include<algorithm>
using namespace std;

#define MOD 1000000007
#define ll long long
int A, B, N;
ll choose[1000010];

int euclid(int a, int b, int& c, int& d)
{
    if (a == 0)
    {
        c = 0, d = 1;
        return b;
    }

    int x1, y1;
    int gcd = euclid(b % a, a, x1, y1);
    c = y1 - (b / a) * x1;
    d = x1;
    return gcd;
}

ll inverse(int n)
{
    int x, y;
    euclid(n, MOD, x, y);
    return (x % MOD + MOD) % MOD;
}

bool isValid(int n)
{
    if (n == 0) return true;
    return isValid(n / 10) && ((n % 10) == A || (n % 10) == B);
}

int main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(NULL);
    cin >> A >> B >> N;

    int up = N;
    int down = 1;
    choose[0] = 1;
    for (int i = 1; i <= N; i++)
    {
        choose[i] = (choose[i - 1] * up) % MOD;
        if (down != 1)
            choose[i] = (choose[i] * inverse(down)) % MOD;
        up--;
        down++;
    }

    int ans = 0;
    int thing = A * N;
    for (int i = 0; i <= N; i++)
    {
        if (isValid(thing)) ans = (ans + choose[i]) % MOD;
        thing = thing - A + B;
    }
    cout << ans << endl;
    return 0;
}