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
#include <iomanip>
using namespace std;

typedef pair<int, int> pii;
#define ff first
#define ss second
#define ll long long
#define ld long double
#define INF 1000000000000000000
#define MOD 1000000007

const int MAXN = 100010;
int N, M, P;
ll d[MAXN], s[MAXN], t[MAXN];
ll dp[MAXN][110];

struct Line
{
    ll m, b;

    ll valueAt(int x)
    {
        return m * x + b;
    }

    ld intersect(const Line& other)
    {
        return 1.0 * (other.b - b) / (m - other.m);
    }
};

Line saved[MAXN];
deque<Line> cand;

bool delB(Line cur)
{
    Line right = cand.back();
    cand.pop_back();
    Line right_2 = cand.back();

    if (right.m == cur.m && right.b > cur.b) return 1;
    if (right.intersect(cur) <= right.intersect(right_2)) return 1;
    cand.push_back(right);
    return 0;
}

bool delF(int x)
{
    Line left = cand.front();
    cand.pop_front();
    Line second = cand.front();
    if ((left.m == second.m && left.b > second.b) ||
         left.intersect(second) <= x) return 1;
    cand.push_front(left);
    return 0;
}

int main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    cin >> N >> M >> P;
    for (int i = 2; i <= N; i++) 
    {
        cin >> d[i];
        d[i] += d[i - 1];
    }
    for (int i = 1; i <= M; i++)
    {
        int n, v;
        cin >> n >> v;
        t[i] = v - d[n];
    }

    sort(t + 1, t + 1 + M);

    for (int i = 1; i <= M; i++) s[i] = t[i] + s[i - 1];

    for (int i = 1; i <= M; i++) saved[i] = {0, 0};
    for (int i = 1; i <= P; i++)
    {
        for (int j = 1; j <= M; j++)
        {
            while (cand.size() >= 2)
                if (!delF(t[j])) break;
            
            dp[i][j] = j * t[j] - s[j];
            if (cand.size() > 0) dp[i][j] += cand.front().valueAt(t[j]);

            while (cand.size() >= 2)
                if (!delB(saved[j])) break;  
            cand.push_back(saved[j]);

            saved[j] = {-1 * j, dp[i][j] + s[j]};
        }
        cand.clear();
    }
    cout << dp[P][M] << endl;
    return 0;
}