#include <iostream>
#include <algorithm>
#include <vector>
#include <map>
#include <set>
using namespace std;

int T;

void solve()
{
    int N, M;
    cin >> N >> M;
    typedef pair<int, int> pii;

    int bots[10][10];
    for (int i = 1; i <= N; i++)
        for (int j = 1; j <= M; j++)
        {
            char c;
            cin >> c;
            if (c == 'R') bots[i][j] = 1;
            else bots[i][j] = 0;
        }
    
    pii minx;
    pii miny;

    bool foundx = 0;
    bool foundy = 0;

    for (int i = 1; i <= N; i++)
        for (int j = 1; j <= M; j++)
            if (!foundx && bots[i][j]) 
            {
                minx = pii(i, j);
                foundx = 1;
            }
    
    for (int j = 1; j <= M; j++)
        for (int i = 1; i <= N; i++)
            if (!foundy && bots[i][j]) 
            {
                miny = pii(i, j);
                foundy = 1;
            }

    if (minx == miny) cout << "YES" << endl;
    else cout << "NO" << endl;
}

int main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    cin >> T;
    while (T--) solve();
    return 0;
}