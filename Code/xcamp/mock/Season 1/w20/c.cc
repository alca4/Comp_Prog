#include <iostream>
#include <algorithm>
#include <vector>
#include <unordered_map>
using namespace std;

#define ll long long
#define MOD 1000000007

int N, M;
int seq[100010];
int mon[100010];
ll temp[100010];
ll n1, n2, n3;

bool valid(ll ans)
{
    ll tn1 = (ans / N) * n1;
    ll tn2 = (ans / N) * n2;
    ll tn3 = (ans / N) * n3;

    for (int i = 1; i < (ans % N) + 1; i++)
    {
        if (seq[i] == 1) tn1++;
        if (seq[i] == 2) tn2++;
        if (seq[i] == 3) tn3++;
    }

    for (int i = 1; i <= M; i++) temp[i] = mon[i];

    for (int i = 1; i <= M; i++)
    {
        if (temp[i] % 2 == 1 && temp[i] >= 3 && tn3 > 0)
        {
            temp[i] -= 3;
            tn3--;
        }
    }

    
    for (int i = 1; i <= M; i++)
    {
        if (temp[i] >= 6 && tn3 > 1)
        {
            ll remove = min(tn3 / 2, temp[i] / 6);
            tn3 -= 2 * remove;
            temp[i] -= remove * 6;
        }
    }

    if (tn3 == 1)
    {
        int maxid = 1;
        for (int i = 1; i <= M; i++)
            if (temp[i] > temp[maxid])
                maxid = i;
        if (temp[maxid] >= 6) 
        {
            temp[maxid] -= 3;
            tn3 = 0;
        }
    }
    
    if (tn3 > 0)
    {
        for (int i = 1; i <= M; i++)
            if (temp[i] == 4 && tn3 > 0)
            {
                temp[i] = 1;
                tn3--;
            }
    }

    if (tn3 > 0)
    {
        for (int i = 1; i <= M; i++)
            if (temp[i] == 2 && tn3 > 0)
            {
                temp[i] = 0;
                tn3--;
            }
    }

    if (tn3 > 0)
    {
        for (int i = 1; i <= M; i++)
            if (temp[i] == 1 && tn3 > 0)
            {
                temp[i] = 0;
                tn3--;
            }
    }

    if (tn3 > 0) tn2 += tn3;

    for (int i = 1; i <= M; i++)
    {
        if (temp[i] >= 2 && tn2 > 0)
        {
            ll remove = min(tn2, temp[i] / 2);
            tn2 -= remove;
            temp[i] -= remove * 2;
        }
    }

    if (tn2 > 0) tn1 += tn2;

    ll sum = 0;
    for (int i = 1; i <= M; i++) sum += temp[i];

    for (int i = 1; i <= M; i++) temp[i] = 0;
    return (tn1 >= sum);
}

void solve()
{
    cin >> N;
    for (int i = 1; i <= N; i++) cin >> seq[i];
    cin >> M;
    for (int i = 1; i <= M; i++) cin >> mon[i];

    for (int i = 1; i <= N; i++)
    {
        if (seq[i] == 1) n1++;
        if (seq[i] == 2) n2++;
        if (seq[i] == 3) n3++;
    }

    ll lb = 1;
    ll ub = 100000000000000;
    ll ans = 100000000000000;
    while (lb <= ub)
    {
        ll mid = (lb + ub) / 2;
        if (valid(mid)) 
        {
            ans = min(ans, mid);
            ub = mid - 1;
        }
        else lb = mid + 1;
    }
    cout << ans << endl;

    for (int i = 1; i <= N; i++) seq[i] = 0;
    for (int i = 1; i <= M; i++) mon[i] = 0;
    n1 = n2 = n3 = 0;
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