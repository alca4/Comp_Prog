#include<iostream>
#include<algorithm>
using namespace std;

int Solve(int n, int a, int b)
{
    if (n <= 2) return 0;
    if (a == b) return 0;
    int ta = a;
    int tb = b;
    if (a <= n / 4) a += n / 4;
    if (a > 3 * n / 4) a -= n / 4;
    if (b <= n / 4) b += n / 4;
    if (b > 3 * n / 4) b -= n / 4;
    if ((ta == a || tb == b) && (ta != a || tb != b)) return n / 4;
    a -= n / 4;
    b -= n / 4;
    n /= 2;
    return Solve(n, a, b);
}

int main()
{
    int T;
    cin >> T;
    for (int i = 0; i < T; i++)
    {
        int N, A, B;
        cin >> N >> A >> B;
        cout << Solve(N + 1, A + 1, B + 1) << endl;
    }
    return 0;
}