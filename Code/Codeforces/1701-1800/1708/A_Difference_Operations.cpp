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

const int MAXN = 110;

void solve()
{
    int N;
    cin >> N;
    
    int arr[MAXN];
    for (int i = 1; i <= N; i++) cin >> arr[i];

    bool works = 1;
    for (int i = 2; i <= N; i++)
    {
        works = works && (arr[i] % arr[1] == 0);
        if (arr[i] < arr[1]) works = 0;
    }

    if (works) cout << "YES" << endl;
    else cout << "NO" << endl;
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