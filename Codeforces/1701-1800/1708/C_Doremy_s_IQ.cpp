#include <iostream>
#include <algorithm>
#include <vector>
#include <cmath>
#include <set>
#include <map>
#include <deque>
#include <queue>
#include <stack>
#include <unordered_set>
#include <unordered_map>
using namespace std;

#define F first
#define S second
#define pb push_back
#define ll long long
#define ld long double
#define INF 1000000000
#define MOD 1000000007

typedef pair<int, int> pii;
typedef pair<ll, ll> pll;

int readInt()
{
    int a;
    cin >> a;
    return a;
}

const int MAXN = 100010;

void solve()
{
    int N, Q;
    cin >> N >> Q;

    int arr[MAXN];
    for (int i = 1; i <= N; i++) cin >> arr[i];

    int ans[MAXN];
    int q = 0;
    for (int i = N; i >= 1; i--)
    {
        if (arr[i] <= q) ans[i] = 1;
        else
        {
            if (q < Q)
            {
                ans[i] = 1;
                q++;
            }
            else ans[i] = 0;
        }
    }

    for (int i = 1; i <= N; i++) cout << ans[i];
    cout << endl;
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