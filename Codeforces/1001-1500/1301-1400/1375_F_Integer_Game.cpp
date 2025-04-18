/*
  ___
 (o,o)
<  .  >
--"-"---
Rowlet is orz
*/
#include <iostream>
#include <algorithm>
using namespace std;

#define FF first
#define SS second
#define pb push_back
#define ll long long
#define ld long double
#define INF 1000000000ull
#define MOD 1000000007ull
#define reset(x) memset(x, 0, sizeof(x))
#define all(x) (x).begin(), (x).end()
#define range(x, y, z) (x) + (y), (x) + (y) + (z)

typedef pair<int, int> pii;
typedef pair<ll, ll> pll;

void maxeq(ll& a, ll b) {a = max(a, b);}
void mineq(ll& a, ll b) {a = min(a, b);}
void add(ll& a, ll b) {a = (a + b) % MOD;}
void mult(ll& a, ll b) {a = (a * b) % MOD;}

const int MAXN = 500010;
ll piles[4];
ll sorted[4];

void operation()
{
    for (int i = 1; i <= 3; i++) sorted[i] = piles[i];
    sort(sorted + 1, sorted + 4);
    ll diff = sorted[3] * 2 - sorted[2] - sorted[1];
    cout << diff << endl;
    cout.flush();
    int n;
    cin >> n;
    if (n == 0) return;

    if (piles[n] == sorted[3]) 
    {
        piles[n] += diff;
        operation();
    }
    else if (piles[n] == sorted[2]) 
    {
        cout << sorted[3] - sorted[1] << endl;
        int yay;
        cin >> yay;
    }
    else if (piles[n] == sorted[1]) 
    {
        cout << sorted[3] - sorted[2] << endl;
        int yay;
        cin >> yay;
    }
}

int main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    cin >> piles[1] >> piles[2] >> piles[3];
    cout << "First" << endl;

    operation();
    return 0;
}