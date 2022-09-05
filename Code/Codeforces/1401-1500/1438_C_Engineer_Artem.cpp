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

void maxeq(ll& a, ll b) {a = max(a, b);}
void mineq(ll& a, ll b) {a = min(a, b);}
void add(ll& a, ll b) {a = (a + b) % MOD;}
void mult(ll& a, ll b) {a = (a * b) % MOD;}

const int MAXN = 110;
int N, M;
int arr[MAXN][MAXN];

void solve()
{
    // cout << "===========" << endl;
    cin >> N >> M;
    for (int i = 1; i <= N; i++) for (int j = 1; j <= M; j++) cin >> arr[i][j];
    for (int i = 1; i <= N; i++) 
    {
        for (int j = 1; j <= M; j++) 
        {
            if ((i + j) % 2 != arr[i][j] % 2) cout << arr[i][j] + 1 << " ";
            else cout << arr[i][j] << " ";
        }
        cout << endl;
    }
    for (int i = 1; i <= N; i++) for (int j = 1; j <= M; j++) arr[i][j] = 0;
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