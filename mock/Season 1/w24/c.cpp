#include <iostream>
#include <algorithm>
#include <vector>
#include <cmath>
#include <set>
#include <map>
#include <deque>
#include <queue>
#include <stack>
#include <unordered_set>
#include <unordered_map>
#include <iomanip>
using namespace std;

typedef pair<int, int> pii;
#define ff first
#define ss second
#define ll long long
#define ld long double
#define INF 1000000000000000000
#define MOD 1000000007
#define terminate {cout << 0 << endl; return 0;}

int A, B, C, D;
const int MAXN = 2010;
int K = 0;

// sum a and b


struct Op
{
    int t, a, b, c, d;
} ans[15010];

int rev = 0;

void op1()
{
    ans[++K] = {1, A, B};
    A++, B++;
}

void op2()
{
    ans[++K] = {2, A, B};
    A /= 2, B /= 2;
}

void op3(int A0)
{
    ans[++K] = {3, A0, A, A, B};
    A = A0;
}

int main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    cin >> A >> B >> C >> D;

    if (A == B && C != D) terminate
    if (A != B && C == D) terminate
    if (B - A < 0 && D - C > 0) terminate
    if (B - A > 0 && D - C < 0) terminate
    if (B - A < 0) 
    {
        swap(A, B);
        swap(C, D);
        rev = 1;
    }
    int p = B - A;
    if (p == 0 && D - C != 0) terminate
    if (p != 0 && D - C == 0) terminate
    if (p == 0 && D - C == 0)
    {
        while (A != 1)
        {
            if (A % 2 == 1) op1();
            op2();
        }
        while (A < C) op1();
    }
    else
    {
        while (!(p % 2)) p /= 2;
        if ((D - C) % p) terminate

        while (B - A != p || A != 1)
        {
            if (B % 2 != A % 2)
            {
                int t = B;
                while (A != t) op1();
                op3(t - p);
                if (A % 2 == 1) op1();
                op2();   
            }
            else
            {
                if (A % 2 == 1) op1();
                op2();
            }
        }

        for (int i = 1; i < (D - C) / p; i++)
        {
            int t = A + p;
            while (A != t) op1();
            op3(t - p);
        }

        while (A < C) op1();
    }

    cout << K << endl;
    for (int i = 1; i <= K; i++)
    {
        if (rev)
        {
            cout << ans[i].t << " ";
            if (ans[i].t == 3) 
                cout << ans[i].d << " " << ans[i].c << " " 
                     << ans[i].b << " " << ans[i].a << endl;
            else
                cout << ans[i].b << " " << ans[i].a << endl;
        }
        else
        {
            cout << ans[i].t << " " << ans[i].a << " " << ans[i].b << " ";
            if (ans[i].t == 3) cout << ans[i].c << " " << ans[i].d;
            cout << endl;
        }
    }
    return 0;
}