#include <iostream>
#include <algorithm>
#include <vector>
using namespace std;

#define ll long long
int N, P;
ll fac[410];
ll I[410];
ll B[410][410];
ll ans[410];

void solve()
{
    cin >> N;
    cout << ans[N] << endl;
}
 
int main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
 
    int T;
    cin >> T >> P;
    fac[0] = 1;
    for (int i = 1; i <= 400; i++) fac[i] = (fac[i - 1] * i) % P;

    
    I[1] = 1;
    for (int i = 2; i <= 400; i++) 
    {
        I[i] = fac[i];
        for (int k = 1; k <= i - 1; k++) 
            I[i] = (I[i] + P - I[k] * fac[i - k]) % P;
    }

    
    B[0][0] = 1;
    for (int i = 1; i <= 400; i++)
        for (int k = 1; k <= i; k++)
        {
            B[i][k] = 0;
            for (int j = 1; j <= i; j++)
                B[i][k] = (B[i][k] + B[i - j][k - 1] * fac[j]) % P;
        }

    
    ans[1] = 1;
    ans[2] = 2;
    for (int i = 3; i <= 400; i++)
    {
        ll v1 = 0;
        for (int j = 1; j <= i - 1; j++)
            v1 = (v1 + I[j] * fac[i - j]) % P;
        v1 = (v1 * 2) % P;

        ll v2 = 0;
        for (int j = 3; j <= i - 1; j++)
            v2 = (v2 + B[i][j] * ans[j]) % P;
        
        ans[i] = (fac[i] + P - v1) % P;
        ans[i] = (ans[i] + P - v2) % P;
    }
    while (T--) solve();
    return 0;
}