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

const int MAXN = 200010;
int N;
ll arr[MAXN];

int main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    cin >> N;
    for (int i = 1; i <= N; i++) cin >> arr[i];

    ll temp = 0;
    ll mv = arr[1];
    for (int i = 2; i <= N; i++)
    {
        temp += (abs(arr[i] - arr[i - 1]));
        mv = max(mv, arr[i]);
    }
    temp += abs(arr[1] - arr[N]);

    cout << max(temp / 2, mv) << endl;
    return 0;
}