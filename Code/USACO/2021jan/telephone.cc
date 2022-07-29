#include<iostream>
#include<vector>
#include<map>
#include<algorithm>
using namespace std;

#define ll long long

int N, K;
int coms[51][51];
int moos[50010];
int ans[50010];
int vis[50010];
map<int, vector<int>> occs;
map<int, vector<int>> nbs;

ll DP(int a)
{
    //cout << a << endl;
    if (ans[a] != -1) return ans[a];
    ll minval = 1e18;
    for (int i = 0; i < nbs[moos[a]].size(); i++)
    {
        int tar = nbs[moos[a]][i];
        //cout << tar << " is visited? " << vis[tar] << endl;
        if (!vis[tar])
        {
            vis[tar] = 1;
            minval = min(minval, DP(tar) + abs(a - tar));
            vis[tar] = 0;
        }
    }
    ans[a] = minval;
    return minval;
}

int main()
{
    cin >> N >> K;
    for (int i = 1; i <= N; i++) 
    {
        cin >> moos[i];
        occs[moos[i]].push_back(i);
        ans[i] = -1;
    }
    ans[N] = 0;
    for (int i = 1; i <= K; i++)
    {
        string str;
        cin >> str;
        for (int j = 1; j <= K; j++) 
        {
            coms[i][j] = str[j - 1] - '0';
            if (coms[i][j])
                for (int k = 0; k < occs[j].size(); k++)
                    nbs[i].push_back(occs[j][k]);
        }
    }
    /*
    for (auto n : occs)
    {
        cout << n.first << " appears at ";
        for (int i = 0; i < n.second.size(); i++)
            cout << n.second[i] << " ";
        cout  << endl;
    }
    for (auto n : nbs)
    {
        cout << n.first << " can talk to cows at at ";
        for (int i = 0; i < n.second.size(); i++)
            cout << n.second[i] << " ";
        cout  << endl;
    }
    */
    vis[1] = 1;
    cout << DP(1) << endl;
    return 0;
}