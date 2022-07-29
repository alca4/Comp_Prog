#include <iostream>
#include <algorithm>
#include <vector>
#include <deque>
using namespace std;

#define ll long long 
#define ld long double

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

int N, A, B, C;
ll arr[1000010];
ll psum[1000010];
ll dp[1000010];
deque<Line> cand;

bool del(Line cur)
{
    Line right = cand.back();
    cand.pop_back();
    Line right_2 = cand.back();

    if (right.intersect(cur) <= right.intersect(right_2))
    {
        // cout << "removing line " << right.id << endl;
        return 1;
    }
    cand.push_back(right);
    return 0;
}

bool delF(int x)
{
    Line left = cand.front();
    cand.pop_front();
    Line second = cand.front();
    if (left.intersect(second) <= x) 
    {
        // cout << "deleting " << left.id << endl;
        return 1;
    }
    cand.push_front(left);
    return 0;
}

void solve()
{
    cin >> N >> A >> B >> C;
    for (int i = 1; i <= N; i++) 
    {
        cin >> arr[i];
        psum[i] = arr[i] + psum[i - 1];
    }
    cand.push_front({0, 0});

    for (int i = 1; i <= N; i++)
    {
        while (cand.size() >= 2)
            if (!delF(psum[i])) break;
        ll c = (A * psum[i] * psum[i]) + (B * psum[i]) + C;
        dp[i] = cand.front().valueAt(psum[i]) + c;
        
        Line cur = {-2 * A * psum[i], A * psum[i] * psum[i] - B * psum[i] + dp[i]};
        while (cand.size() >= 2)
            if (!del(cur)) break;
        cand.push_back(cur);
        /*
        cout << "inserting line " << cand.back().m << " " << cand.back().b << " "
             << cand.back().id << endl;
        */
    }

    cout << dp[N] << endl;
    
    for (int i = 1; i <= N; i++) arr[i] = psum[i] = dp[i] = 0;
    cand.clear();
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