#include <iostream>
#include <algorithm>
#include <vector>
#include <stack>
using namespace std;

int T, N, M;

int main()
{
    scanf("%d", &T);
    while (T--)
    {
        scanf("%d%d", &N, &M);
        long long ans = 0;
        for (int i = 1; i <= N; i++) 
        {
            int a;
            scanf("%d", &a);
            ans = (ans | a);
        }
        printf("%lld\n", ans);
    }
    return 0;
}