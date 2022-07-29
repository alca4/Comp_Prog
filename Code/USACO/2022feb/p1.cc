#include<iostream>
#include<algorithm>
#include<vector>
using namespace std;

const int MAXN = 20;
int N, Q;
int wishlist[MAXN][MAXN];
bool edges[MAXN][MAXN];
bool want_trade[MAXN][MAXN];
bool visited[MAXN];

int DP(int a, bool mark)
{
    int ans = 0;
    for (int i = 1; i <= N; i++)
    {
        if (edges[a][i] && !visited[i])
        {
            visited[i] = true;
            if (!mark) ans += (1 + DP(i, true));
            ans += DP(i, false);
            visited[i] = false;
        }
    }
    return ans;
}

int main()
{
    cin >> N; 
    for (int i = 1; i <= N; i++)
        for (int j = 1; j <= N; j++)
            cin >> wishlist[i][j];

    for (int i = 1; i <= N; i++)
    {
        for (int j = 1; j <= N; j++)
        {
            if (wishlist[i][j] > j) want_trade[j][wishlist[i][j]] = true;
            if (wishlist[i][j] < j) 
                for (int k = 1; k <= N; k++)
                    if (k != i) want_trade[k][wishlist[i][j]] = true;
        }
    }

/*
    for (int i = 1; i <= N; i++)
    {
        for (int j = 1; j <= N; j++)
            cout << want_trade[i][j] << " ";
        cout << endl;
    }
*/

    cin >> Q;
    for (int i = 0; i < Q; i++)
    {
        string str;
        cin >> str;
        for (int j = 1; j <= N; j++)
            for (int k = 1; k <= N; k++)
                edges[j][k] = (str[j - 1] == str[k - 1]) && 
                               want_trade[j][k] &&
                               want_trade[k][j];

        int start = 1;
        for (int i = 1; i <= N; i++)
        {
            for (int j = 1; j <= N; j++)
            {
                if (edges[i][j] == 1) start = i;
            }
        }
        visited[start] = true;
        cout << DP(start, false) + 1 << endl;
    }
    return 0;
}