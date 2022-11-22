#include <iostream>
#include <algorithm>
#include <vector>
#include <set>
#include <map>
using namespace std;

void solve()
{
    int N;
    int a[100010];
    map<int, int> lengths;
    vector<int> remaining;
    int dupes = 0;
    cin >> N;
    for (int i = 1; i <= N; i++)
    {
        cin >> a[i];
        lengths[a[i]]++;
    }

    for (auto n : lengths)
    {
        if (n.second > 1) dupes++;
        if (n.second > 2)
        {
            cout << 0 << endl;
            return;
        }
    }
        
    
    if (dupes > 1)
    {
        cout << 0 << endl;
        return;
    }
    
    for (int i = 1; i <= 1000; i++)
        if (lengths[i] == 0)
            remaining.push_back(i);
    
    int ans = 0;
    set<int> pos;
    for (int i = 0; i < remaining.size(); i++)
        for (int j = i + 1; j < remaining.size(); j++)
        {
            if (dupes == 1)
            {
                if (lengths[remaining[i] + remaining[j]] >= 2)
                {
                    cout << lengths[remaining[i] + remaining[j]] << endl;
                    return;
                }
            }
            else
            {
                //cout << remaining[i] + remaining[j] << endl;
                if (lengths[remaining[i] + remaining[j]] != 0)
                {
                    pos.insert(remaining[i] + remaining[j]);
                    //cout << remaining[i] + remaining[j] << endl;
                }
            }
        }
    for (auto n : pos) ans += lengths[n];

    cout << ans << endl;
}
 
int main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
 
    int T;
    cin >> T;
    while (T--) solve();
    return 0;
}