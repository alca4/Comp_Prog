#pragma GCC optimize("O3,unroll-loops")
#pragma GCC target("avx2,bmi,bmi2,lzcnt,popcnt")

#include <iostream>
#include <algorithm>
#include <vector>
#include <cmath>
using namespace std;

#define ll long long

int N, M;
int arr[110];
int G;
vector<int> groups[30];
int ans[110];
int vis[110];

int main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    cin >> N;
    int g1 = 0;
    int gl = 0;
    for (int i = 1; i <= N; i++) cin >> arr[i];
    for (int i = 1; i <= N; i++)
    {
        if (vis[i]) continue;
        groups[++G].push_back(i);
        vis[i] = 1;
        int temp = i;
        while (arr[temp] != i)
        {
            temp = arr[temp];
            groups[G].push_back(temp);
            vis[temp] = 1;
        }
        for (int i = 0; i < groups[G].size(); i++)
        {
            if (i % 2 == 0) ans[groups[G][i]] = 1;
            if (i % 2 == 1) ans[groups[G][i]] = -1;
        }
        if (groups[G].size() == 2)
        {
            groups[G].clear();
            G--;
        }
        if (i == 1 && G > 0) g1 = G;
        if (i == N && G > 0) gl = G;
    }

    for (int i = 0; i < 1 << G; i++)
    {
        if ((i | (1 << (g1 - 1))) == i || (i | (1 << (gl - 1))) == i) continue;
        for (int j = 0; j < G; j++)
        {
            if ((i | (1 << j)) == i && ((i - 1) | (1 << j)) != (i - 1)) 
            {
                for (int h = 0; h < groups[j + 1].size(); h++)
                {
                    if (h % 2 == 0) ans[groups[j + 1][h]] = -1;
                    if (h % 2 == 1) ans[groups[j + 1][h]] = 1;
                }
            }
            if ((i | (1 << j)) != i && ((i - 1) | (1 << j)) == (i - 1)) 
            {
                for (int h = 0; h < groups[j + 1].size(); h++)
                {
                    if (h % 2 == 0) ans[groups[j + 1][h]] = 1;
                    if (h % 2 == 1) ans[groups[j + 1][h]] = -1;
                }
            }
        }
        int sum = 0;
        int works = 1;
        for (int i = 1; i <= N; i++)
        {
            sum += ans[i];
            if (sum < 0) works = 0;
        }
        if (works)
        {
            for (int i = 1; i <= N; i++)
            {
                if (ans[i] == 1) cout << "(";
                if (ans[i] == -1) cout << ")";
            }
            cout << endl;
            return 0;
        }
    }
    
    return 0;
}