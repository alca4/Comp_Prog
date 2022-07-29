/*
Learning:

Static Range Query: prefix sums
Know what is stored in each of your data structures
*/
#include <iostream>
#include <algorithm>
#include <vector>
using namespace std;

#define ll long long

int T, N;
int a[5010];
int b[5010];
int bc[5010][5010];

int main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    cin >> T;
    while (T--)
    {
        for (int i = 1; i <= N; i++)
        {
            a[i] = b[i] = 0;
            for (int j = 1; j <= N; j++) bc[i][j] = 0;
        }
        cin >> N;
        for (int i = 1; i <= N; i++) cin >> a[i];

        for (int i = 1; i <= N; i++)
        {
            int vals = 0;
            for (int j = i + 1; j <= N; j++)
            {
                if (a[i] > a[j]) vals++;
                bc[i][j] = vals;
            }
        }
        for (int j = 1; j <= N; j++)
        {
            for (int i = N - 1; i >= 1; i--) bc[i][j] += bc[i + 1][j];
        }
        
        for (int i = 1; i <= N; i++)
            for (int j = i + 1; j <= N; j++)
                if (a[i] > a[j])
                    b[i]++;
        for (int i = 2; i <= N; i++)
            b[i] += b[i - 1];
        
        
        long long ans = 0;
        for (int i = 1; i <= N; i++)
            for (int j = i + 1; j <= N; j++)
            {
                if (a[i] < a[j])
                {
                    ans += b[j - 1] - b[i];
                    ans -= bc[i + 1][j];
                }
            }
        cout << ans << endl;
    }
}