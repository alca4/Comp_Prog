/*
Learnings:

If there is a greedy solution, see if you can generalize to a DP
*/
#include <iostream>
#include <algorithm>
#include <vector>
using namespace std;

typedef pair<int, int> pii;

int T;
int N;
string str;
pii dp[200010][2];

pii Add(const pii& p1, const pii& p2)
{
    return pii(p1.first + p2.first, p1.second + p2.second);
}

int main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    cin >> T;
    while (T--)
    {
        cin >> N;
        cin >> str;
        int cost = 0;
        dp[0][1] = pii(0, 0);
        dp[0][0] = pii(0, 0);
        for (int i = 0; i < str.length(); i += 2)
        {
            dp[i + 2][0] = min(Add(dp[i][0], pii((str[i] - '0') + (str[i + 1] - '0'), 0)),
                               Add(dp[i][1], pii(('1' - str[i]) + ('1' - str[i + 1]), 1)));
            dp[i + 2][1] = min(Add(dp[i][0], pii((str[i] - '0') + (str[i + 1] - '0'), 1)),
                               Add(dp[i][1], pii(('1' - str[i]) + ('1' - str[i + 1]), 0)));
        }
        cout << min(dp[N][0], dp[N][1]).first << " " << min(dp[N][0], dp[N][1]).second + 1 << endl;
    }
    return 0;
}