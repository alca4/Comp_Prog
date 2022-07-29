/*
Learnings:

Don't use 1e9 + 7 as MOD, its fine just typing number out
If DP overcounts sets, consider adding a dimension which indicates the max value
of any item in set
*/
#include <iostream>
#include <algorithm>
#include <vector>
using namespace std;

#define ll long long
#define MOD 1000000007

int T, N;
vector<int> palin;
ll dp[40010][510];

int reverse(int i)
{
    int rev = 0;
    while (i > 0)
    {
        rev *= 10;
        rev += i % 10;
        i /= 10;
    }
    return rev;
}

int main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    for (int i = 1; i <= 40000; i++)
        if (reverse(i) == i) 
            palin.push_back(i);

    for (int i = 1; i <= 40000; i++)
    {
        for (int j = 0; j < palin.size(); j++)
        {
            if (j > 0) dp[i][j] = dp[i][j - 1];
            if (i - palin[j] == 0) dp[i][j] = (dp[i][j] + 1) % MOD;
            if (i - palin[j] > 0) dp[i][j] = (dp[i - palin[j]][j] + dp[i][j]) % MOD;
        }
    }
    
    cin >> T;
    while (T--)
    {
        int a;
        cin >> a;
        cout << dp[a][palin.size() - 1] << endl;
    }
}