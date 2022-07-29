#include <iostream>
#include <algorithm>
#include <vector>
using namespace std;

int T, N;

int main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    cin >> T;
    while (T--)
    {
        string str;
        cin >> str;
        N = str.length();
        int val = 0;
        for (int i = 0; i < N; i++) val += (str[i] - 'a') + 1;
        int b = (N % 2 == 0 ? 0 : min((str[N - 1] - 'a') + 1, (str[0] - 'a') + 1));
        int a = val - b;
        if (a > b) cout << "Alice " << a - b << endl;
        else cout << "Bob " << b - a << endl;
    }
}