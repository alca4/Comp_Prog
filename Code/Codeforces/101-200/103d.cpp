#include<iostream>
#include<cmath>
#include<algorithm>
#include<vector>
using namespace std;

#define v vector

typedef long long ll;

const int MAXN = 300010;

struct Q
{
    int a;
    int b;
    int id;
};

bool Comp(const Q& q1, const Q& q2)
{
    return q1.b == q2.b ? q1.a < q2.a : q1.b < q2.b;
}

int N, P;
ll moos[MAXN], ans[MAXN], psum[MAXN];
Q q[MAXN];

int main()
{
    scanf("%d", &N);
    for (int i = 1; i <= N; i++) scanf("%I64d", &moos[i]);
    int S = sqrt(N);
    
    scanf("%d", &P);
    for (int i = 1; i <= P; i++)
    {
        scanf("%d%d", &q[i].a, &q[i].b);
        q[i].id = i;
    }
    
    sort(q + 1, q + 1 + P, Comp);
    
    int b = 0;
    for (int i = 1; i <= P; i++)
    {
        if (q[i].b < S)
        {
            if (q[i].b > b)
            {
                b = q[i].b;
                for (int j = N; j >= q[i].a; j--)
                    psum[j] = (j + b <= N ? psum[j + b] + moos[j] : moos[j]);
            }
            
            ans[q[i].id] = psum[q[i].a];
        }
        else
        {
            for (int j = q[i].a; j <= N; j += q[i].b)
                ans[q[i].id] += moos[j];
        }
    }
                
    for (int i = 1; i <= P; i++) cout << ans[i] << endl;
    return 0;
}