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
#define MOD 1000000007ull
#define reset(x) memset(x, 0, sizeof(x))
#define all(x) (x).begin(), (x).end()
#define range(x, y, z) (x) + (y), (x) + (y) + (z)

typedef pair<int, int> pii;
typedef pair<ll, ll> pll;

int read()
{
    int a;
    cin >> a;
    return a;
}

const int MAXN = 200010;
int N;
int arr[MAXN];

int main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    cin >> N;
    for (int i = 1; i <= N; i++) cin >> arr[i];

    vector<int> backs;
    backs.pb(arr[1]);
    // for (int i = 0; i < backs.size(); i++) cout << backs[i] << " ";
    // cout << endl;
    for (int i = 2; i <= N; i++)
    {
        if (arr[i] < backs[0]) backs[0] = arr[i];
        else if (arr[i] > backs[backs.size() - 1]) backs.pb(arr[i]);
        else 
        {
            int id = distance(backs.begin(), lower_bound(all(backs), arr[i]));
            // cout << id << endl;
            backs[id] = arr[i];
        }
        // for (int i = 0; i < backs.size(); i++) cout << backs[i] << " ";
        // cout << endl;
    }
    cout << backs.size() << endl;
    return 0;
}