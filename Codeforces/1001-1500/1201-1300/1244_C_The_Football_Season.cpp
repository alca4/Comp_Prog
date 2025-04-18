/*
Key insight: d * W = w * D
So d < W must have solution
*/
#include <iostream>
#include <algorithm>
#include <vector>
using namespace std;

#define ll long long

int W, D;
ll N, P;

int main()
{
    cin >> N >> P >> W >> D;
    ll w, d;
    for (d = 0; d < W; d++)
    {
        w = (P - d * D) / W;
        if (d * D + w * W == P && w + d <= N && w >= 0)
        {
            cout << w << " " << d << " " << N - w - d << endl;
            return 0;
        }
    }
    cout << -1 << endl;
    //cout << w << " * " << W << " + " << d << " * " << D << " = " << P << endl;
    return 0;
}