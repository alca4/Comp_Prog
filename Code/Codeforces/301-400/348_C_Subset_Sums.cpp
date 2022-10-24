/*
Idea: sqrt
Split subsets into two types: "heavy" with |S| > sqrt(N), "light" with |S| < sqrt(N)
Note: at max sqrt(N) heavy sets, since size of sets < 1e5
Calculate the intersection between heavy and light sets
Keep lazy tags for all sets
For small queries, manually update array values and intersections
For large queries, update the lazy tags of the small sets using intersections
*/
#include <iostream>
#include <algorithm>
#include <vector>
#include <bitset>
using namespace std;

#define ll long long

const int S = 315;
int N, M, Q;
int H = 0;
ll arr[100010];
vector<int> sets[100010];
int heavy[100010];
int heavy_id[S + 5];
ll ud[S + 5];
ll sum[S + 5];
bitset<100010> vis[S + 5];
int intersect[100010][S + 5];

int main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    cin >> N >> M >> Q;
    for (int i = 1; i <= N; i++) cin >> arr[i];
    for (int i = 1; i <= M; i++)
    {
        int sz;
        cin >> sz;
        for (int j = 0; j < sz; j++) 
        {
            int n;
            cin >> n;
            sets[i].push_back(n);
        }
        if (sz > S) 
        {
            H++;
            heavy[i] = H;
            heavy_id[H] = i;
            for (int j = 0; j < sets[i].size(); j++)
                vis[heavy[i]][sets[i][j]] = 1;
        }
    }

    for (int i = 1; i <= N; i++)
        for (int j = 0; j < sets[i].size(); j++)
            for (int h = 1; h <= H; h++)
                if (vis[h][sets[i][j]] == 1)
                    intersect[i][h]++;
    
    for (int i = 1; i <= H; i++)
        for (int j = 0; j < sets[heavy_id[i]].size(); j++)
            sum[i] += arr[sets[heavy_id[i]][j]];
    
    while (Q--)
    {
        char type;
        int id;
        cin >> type;
        if (type == '+')
        {
            ll v;
            cin >> id >> v;
            if (sets[id].size() <= S)
            {
                for (int i = 0; i < sets[id].size(); i++)
                    arr[sets[id][i]] += v;
                for (int j = 1; j <= H; j++)
                    sum[j] += intersect[id][j] * v;
            }
            else
            {
                ud[heavy[id]] += v;
            }
        }
        else
        {
            cin >> id;
            if (sets[id].size() <= S)
            {
                ll ans = 0;
                for (int i = 0; i < sets[id].size(); i++) ans += arr[sets[id][i]];
                for (int i = 1; i <= H; i++)
                    ans += intersect[id][i] * ud[i];
                cout << ans << endl;
            }
            else
            {
                ll ans = sum[heavy[id]] + ud[heavy[id]] * sets[id].size();
                for (int i = 1; i <= H; i++)
                {
                    if (i == heavy[id]) continue;
                    ll a = intersect[id][i] * ud[i]; 
                    ans += a;
                }
                cout << ans << endl;
            }
        }
    }
}