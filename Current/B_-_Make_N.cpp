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

void Bezout(ll A, ll B, ll* x, ll* y)
{
    if (B == 0)
    {
        *x = 1;
        *y = 0;
        return;
    }

    ll dx, dy;
    Bezout(B, A % B, &dx, &dy);
    *y = dx - (A / B) * dy;
    *x = dy;
}

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
        cout << "=========" << endl;
        ll N, A, B, X, Y, Z;
        cin >> N >> A >> B >> X >> Y >> Z;

        if (A < B)
        {
            swap(A, B);
            swap(Y, Z);
        }

        ll ans = min({N * X, 
                      N / A * Y + (N % A) * X, 
                      N / B * Z + (N % B) * X});
        
        ll x, y;
        Bezout(A, B, &x, &y);
        ll G = gcd(A, B);

        ll cx = x * (N / G);
        ll cy = y * (N / G);

        cout << cx << " " << cy << endl;

        ll r = N - cx * A - cy * B;
        // cout << r << endl;

        // cout << g << endl;

        ll dx = B / G;
        ll dy = A / G;

        ll d;
        if (cy < 0) d = ceil(-1.0 * cy / dy) * -1;
        else d = cy / dy;

        cy -= dy * d;
        cx += dx * d;

        cout << cx << " " << cy << endl;
        
        if (cx >= 0 && cy >= 0) ans = min(ans, cx * Y + cy * Z + (N - cx * A - cy * B) * X);

        if (cx < 0) d = ceil(-1.0 * cx / dx) * -1;
        else d = cx / dx;

        cy += dy * d;
        cx -= dx * d;

        cout << cx << " " << cy << endl;

        if (cx >= 0 && cy >= 0) ans = min(ans, cx * Y + cy * Z + (N - cx * A - cy * B) * X);

        cout << ans << endl;
    }

    return 0;
} 