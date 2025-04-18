// Coded on a phone, why do i do this help
#include <iostream>
#include <algorithm>
using namespace std;

int arr[100010];
int main()
{
    int t;
    cin >> t;
    
    while (t--)
    {
        int n;
        cin >> n;
        
        for (int i = 1; i <= n; i++) cin >> arr[i];

        int ans = abs(arr[1] - 1);
        for (int i = 2; i <= n; i++) ans = __gcd(ans, abs(arr[i] - i));
        cout << ans << endl;

        for (int i = 1; i <= n; i++) arr[i] = 0;
    }
    
    return 0;
}