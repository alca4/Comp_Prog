#include <iostream>
#include <algorithm>
#include <vector>
#include <stack>
using namespace std;

#define ll long long

int T, N, M;

int main()
{
    scanf("%d", &T);
    while (T--)
    {
        scanf("%d%d", &N, &M);
        stack<ll> d;
        for (int i = 1; i <= N; i++) 
        {
            ll a;
            scanf("%lld", &a);
            d.push(a);
        }
        long long ans = 0;
        while (d.size() > 1)
        {
            ll a = d.top();
            d.pop();
            ll b = d.top();
            d.pop();
            if (a + b - (a | b) >= M) d.push(a | b);
            else 
            {
                ans += a - M;
                d.push(b);
            }
        }
        ans += d.top() - M;
        printf("%lld\n", ans);
    }
    return 0;
}