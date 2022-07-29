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
    int N;
    cin >> N;

    int arr[MAXN];

    for (int i = 1; i <= N; i++) cin >> arr[i];

    for (int i = N - 1; i >= 1; i--)
    {
        int pre = arr[i + 1];
        bool zero;
        for (int j = i; j >= 1; j--)
        {
            zero = arr[j] == 0;
            arr[j] = pre - arr[j];
            pre = pre - arr[j];
            if (zero) 
            {
                sort(arr + j, arr + i + 1);
                break;
            }
        }
        if (!zero) sort(arr + 1, arr + i + 1);
    }
    cout << arr[1] << endl;
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