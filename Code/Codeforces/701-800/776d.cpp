#include <iostream>
#include <algorithm>
#include <vector>
#include <set>
using namespace std;

int N, Q;
int state[100010];
vector<int> switches[100010];

#define BUF 100000
set<int> twosat[200010];
int V = 0;
int vis[200010];

bool DFS(int a)
{
    int not_a = (a > 100000 ? a - 100000 : a + 100000);
    if (vis[not_a]) return 0;
    //cout << "at " << a << endl;
    vis[a] = 1;
    V++;
    bool ans = 1;
    for (auto n : twosat[a])
    {
        if (vis[n]) continue;
        ans &= DFS(n);
    }
    return ans;
}

int main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    cin >> N >> Q;
    
    for (int i = 1; i <= N; i++) cin >> state[i];
    for (int i = 1; i <= Q; i++)
    {
        int n;
        cin >> n;
        for (int j = 0; j < n; j++)
        {
            int a;
            cin >> a;
            switches[a].push_back(i);
        }
    }

    for (int i = 1; i <= N; i++)
    {
        if (!state[i])
        {
            twosat[switches[i][0]].insert(switches[i][1] + BUF);
            twosat[switches[i][1] + BUF].insert(switches[i][0]);
            twosat[switches[i][1]].insert(switches[i][0] + BUF);
            twosat[switches[i][0] + BUF].insert(switches[i][1]);
            // cout << switches[i][0] << " to " << switches[i][1] + BUF << endl;
            // cout << switches[i][0] + BUF << " to " << switches[i][1] << endl;
        }
        else
        {
            twosat[switches[i][0]].insert(switches[i][1]);
            twosat[switches[i][1]].insert(switches[i][0]);
            twosat[switches[i][0] + BUF].insert(switches[i][1] + BUF);
            twosat[switches[i][1] + BUF].insert(switches[i][0] + BUF);
            // cout << switches[i][0] + BUF << " to " << switches[i][1] + BUF << endl;
            // cout << switches[i][0] << " to " << switches[i][1] << endl;
        }
    }

    
    bool b = 1;
    for (int i = 1; i <= Q; i++)
        if (!vis[i] && !vis[i + BUF]) b &= DFS(i);
    
    for (int i = 1; i <= 200000; i++) vis[i] = 0;

    bool b2 = 1;
    for (int i = 1; i <= Q; i++)
        if (!vis[i] && !vis[i + BUF]) b2 &= DFS(i + BUF);
    if (b || b2) cout << "YES" << endl;
    else cout << "NO" << endl;
    return 0;
}