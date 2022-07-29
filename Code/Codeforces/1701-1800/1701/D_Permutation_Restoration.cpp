#include <iostream>
#include <algorithm>
#include <vector>
#include <set>
using namespace std;

typedef pair<int, int> pii;
#define ll long long

struct Range
{
    int s, e, id;
};
bool Comp(const Range& p1, const Range& p2)
{
    return pii(p1.e, p1.s) < pii(p2.e, p2.s);
}

int arr[500010];
Range range[500010];
int ans[500010];
set<int> vals;

void solve()
{

    int N;
    cin >> N;

    for (int i = 1; i <= N; i++) 
    {
        cin >> arr[i];
        vals.insert(i);
        range[i] = {i / (arr[i] + 1) + 1, (arr[i] == 0 ? N : i / arr[i]), i};
    }

    
    sort(range + 1, range + 1 + N, Comp);

    for (int i = 1; i <= N; i++) 
    {
        ans[range[i].id] = *(vals.lower_bound(range[i].s));
        vals.erase(ans[range[i].id]);
    }
    for (int i = 1; i <= N; i++)
        cout << ans[i] << " ";
    cout << endl;

    for (int i = 1; i <= N; i++) arr[i] = ans[i] = 0;
    for (int i = 1; i <= N; i++) range[i] = {0, 0, 0};
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