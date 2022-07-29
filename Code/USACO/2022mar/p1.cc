#include<iostream>
#include<algorithm>
#include<vector>
using namespace std;

struct Info
{
    int t;
    int x;
    int n;
};

bool CompT(const Info& i1, const Info& i2)
{
    return i1.t < i2.t;
}

int N, A, C;
Info apples[200010];
Info cows[200010];

int main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(NULL);
    cin >> N;
    A = 1, C = 1;
    for (int i = 1; i <= N; i++)
    {
        int q;
        Info thing;
        cin >> q >> thing.t >> thing.x >> thing.n;
        if (q == 2) apples[A] = thing, A++;
        if (q == 1) cows[C] = thing, C++;
    }
    A--, C--;

    sort(apples + 1, apples + A + 1, CompT);
    sort(cows + 1, cows + C + 1, CompT);

    int a = 1, c = 1;
    long long ans = 0;
    while (a <= A && c <= C)
    {
        Info& i1 = apples[a];
        Info& i2 = cows[c];
        if (i1.t < i2.t) a++;
        else if (abs(i1.t - i2.t) >= abs(i1.x - i2.x))
        {
            int smaller = min(i1.n, i2.n);
            i1.n -= smaller;
            i2.n -= smaller;
            ans += smaller;
            cout << a << " " << c << " produce " << smaller << endl;
            if (i1.n == 0) a++;
            if (i2.n == 0) c++;
        }
    }

    cout << ans << endl;
    return 0;
}