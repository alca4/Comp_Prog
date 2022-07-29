#include <iostream>
#include <algorithm>
#include <vector>
#include <set>
using namespace std;

int T, N;
set<int> a;

int main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cin >> T;
    while (T--)
    {
        cin >> N;
        int num_zero = 0;
        for (int i = 1; i <= N; i++) 
        {
            int n;
            cin >> n;
            if (n == 0) num_zero++;
            a.insert(n);
        }
        if (num_zero != 0) cout << N - num_zero << endl;
        else if (a.size() != N) cout << N << endl;
        else cout << N + 1 << endl;
        a.clear();
    }
}