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

typedef pair<int, int> pii;
#define ff first
#define ss second
#define ll long long
#define ld long double
#define INF 1000000000000000000
#define MOD 1000000007

const int MAXN = 1010;
int N;
ll e[MAXN][MAXN], ans[MAXN][MAXN];
ll row[MAXN], col[MAXN];

int main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    cin >> N;
    for (int i = 1; i <= N; i++)
        for (int j = 1; j <= N; j++)
            cin >> e[i][j];

    ll rmid = 0, cmid = 0;
    for (int i = 2; i <= N - 1; i++)
    {
        row[i] = (e[i + 1][1] - 2 * e[i][1] + e[i - 1][1]) / 2;
        col[i] = (e[1][i + 1] - 2 * e[1][i] + e[1][i - 1]) / 2;
        rmid += row[i];
        cmid += col[i];
    }

    ll s1 = e[N][N];
    ll s2 = e[1][N];
    ll s3 = e[N][1];
    ll s4 = e[1][1];
    for (int i = 2; i <= N - 1; i++)
    {
        s1 -= (N - i) * row[i];
        s1 -= (N - i) * col[i];

        s2 -= (N - i) * col[i];
        s2 -= (i - 1) * row[i];

        s3 -= (i - 1) * col[i];
        s3 -= (N - i) * row[i];

        s4 -= (i - 1) * row[i];
        s4 -= (i - 1) * col[i];
    }
    s1 /= (N - 1);
    s2 /= (N - 1);
    s3 /= (N - 1);
    s4 /= (N - 1);

    row[1] = (cmid - rmid - s2 + s3 + 2 * s1) / 4;
    row[N] = (cmid - rmid - s1 + s4 + 2 * s2) / 4;
    col[1] = (rmid - cmid + s1 - s4 + 2 * s2) / 4;
    col[N] = (rmid - cmid + s3 - s2 + 2 * s4) / 4;

    
    for (int i = 1; i <= N; i++)
    {
        for (int j = 1; j <= N; j++)
        {
            ans[i][j] = min(row[i], col[j]);
            row[i] -= ans[i][j];
            col[j] -= ans[i][j];
            cout << ans[i][j] << " ";
        }
        cout << endl;
    }
    
    return 0;
}