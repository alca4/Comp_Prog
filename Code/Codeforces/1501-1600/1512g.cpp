#include <iostream>
#include <algorithm>
#include <cmath>
#include <vector>
using namespace std;

int T;
int c[10000010];
int d[10000010];
int ans[10000010];

int main()
{
    cin >> T;
    d[1] = 1;
    for (int i = 2; i <= 10000000; i++)
    {
        if (c[i]) continue;
        for (int j = i; j <= 10000000; j += i)
            c[j] = 1;
    }
    for (int i = 1; i <= 10000000; i++)
    {
    	for (int j = i; j <= 10000000; j += i)
    	{
    		if (i <= sqrt(j)) d[j] += i;
    		if (i < sqrt(j)) d[j] += j / i;
    	}
    }
    d[1] = 1;
    for (int i = 1; i <= 10000000; i++)
        ans[i] = 1000000000;
    for (int i = 1; i <= 10000000; i++)
    {
    	if (d[i] > 10000000) continue;
    	ans[d[i]] = min(i, ans[d[i]]);
    }
    for (int i = 1; i <= T; i++)
    {
        int n;
        cin >> n;
        if (ans[n] == 1000000000) cout << -1 << endl;
        else cout << ans[n] << endl;
    }
    return 0;
}