// coded on a phone lmao
#include <iostream>
using namespace std;

int main()
{
    int t;
    cin >> t;
    
    while (t--)
    {
        int n;
        cin >> n;
        
        for (int i = 1; i <= n; i++) 
        {
            if (n % 2 == 0 && i == n / 2) cout << i * 2 << " ";
            else cout << i << " ";
        }
        cout << endl;
    }
    return 0;
}