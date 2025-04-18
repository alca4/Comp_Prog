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

const int MAXN = 5010;
int N;
int arr[MAXN];

void solve(int a, int b)
{
    if (b - a + 1 == 4)
    {
        int x[5];
        cout << "? " << a << " " << a + 1 << endl;
        cin >> x[1];
        cout << "? " << a << " " << a + 2 << endl;
        cin >> x[2];
        cout << "? " << a << " " << a + 3 << endl;
        cin >> x[3];
        cout << "? " << a + 2 << " " << a + 3 << endl;
        cin >> x[4];

        arr[a + 3] = (x[3] - x[2] + x[4]) / 2;
        arr[a] = x[3] - arr[a + 3];
        arr[a + 2] = x[4] - arr[a + 3];
        arr[a + 1] = x[1] - arr[a];
    }
    else if ((b - a + 1) % 2 == 0) 
    {
        int mid = (a + b) / 2;
        solve(a, mid);
        solve(mid + 1, b);
    }
    else
    {
        int x[MAXN];
        int s = 0;
        for (int i = a; i < b; i++)
        {
            cout << "? " << i << " " << i + 1 << endl;
            cin >> x[i];
            s += x[i];
        }
        cout << "? " << a << " " << b << endl;
        cin >> x[b];
        s += x[b];

        s /= 2;

        for (int i = a; i <= b; i++)
        {
            arr[i] = s;
            for (int j = i + 1; j <= b; j += 2) 
            {
                arr[i] -= x[j];
                // cout << "subtracting " << j << endl;
            }
            for (int j = a + (i - a) % 2; j < i; j += 2) 
            {
                arr[i] -= x[j];
                // cout << "subtracting " << j << endl;
            }
        }
    }
}

int main()
{
    srand(time(NULL));
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    cin >> N;
    solve(1, N);

    cout << "! ";
    for (int i = 1; i <= N; i++) cout << arr[i] << " ";
    cout << endl;
    return 0;
} 