#include<iostream>
#include<algorithm>
using namespace std;

int I, J, P;
int city[51][51];
long long memo[51][51];

long long DP(int a, int b)
{
    if (a == I && b == J) return 1;
    if (memo[a][b] >= 0) return memo[a][b];
    long long ans = 0;
    if (a < I && city[a + 1][b] != -1) ans += DP(a + 1, b);
    if (b < J && city[a][b + 1] != -1) ans += DP(a, b + 1);
    /*
    if (a >= 0 && city[a - 1][b] != -1) ans += DP(a - 1, b);
    if (b >= 0 && city[a][b - 1] != -1) ans += DP(a, b - 1);
    */
    memo[a][b] = ans;
    return ans;
}

int main()
{
    scanf("%d%d%d", &I, &J, &P);
    for (int i = 0; i <= I; i++) for (int j = 0; j <= J; j++) memo[i][j] = -1;
    for (int i = 0; i < P; i++)
    {
        int a, b;
        scanf("%d%d", &a, &b);
        city[a][b] = -1;
    }

    printf("%ld\n", DP(0, 0));
    return 0;
}