/*
Idea: Mo's algorithm
On prefix xor, find two indices where a ^ b = k, then process queries using Mo
*/
#include <iostream>
#include <algorithm>
#include <cmath>
#include <vector>
using namespace std;

struct Query
{
    int l;
    int r;
    int id;    
};

int N, M, K, S = 320, B;
int a[100010];
Query q[100010];
long long ans[100010];
int cnt[1 << 20];
long long res = 0;

bool CompL(const Query& q1, const Query& q2)
{
    return make_pair(q1.l, q1.r) < make_pair(q2.l, q2.r);
}
bool CompR(const Query& q1, const Query& q2)
{
    return make_pair(q1.r, q1.l) < make_pair(q2.r, q2.l);
}

void Add(int n)
{
    res += cnt[n ^ K];
    cnt[n]++;
    //cout << "result is now: " << res << endl;
}

void Delete(int n)
{
    cnt[n]--;
    res -= cnt[n ^ K];
    //cout << "result is now: " << res << endl;
}

int main()
{
    cin >> N >> M >> K;
    for (int i = 1; i <= N; i++) cin >> a[i];
    for (int i = 2; i <= N; i++) a[i] = a[i] ^ a[i - 1];
    for (int i = 1; i <= M; i++) 
        cin >> q[i].l >> q[i].r, q[i].id = i;

    sort(q + 1, q + M + 1, CompL);
    int l = 1;
    int val = q[1].l / S;
    for (int i = 2; i <= M; i++)
    {
        if (q[i].l / S != val) 
        {
            //cout << l << " " << i - 1 << endl;
            sort(q + l, q + i - 1, CompR);
            l = i;
            val = q[i].l / S;
        }   
    }
    sort(q + l, q + M + 1, CompR);
    //for (int i = 1; i <= N; i++) cout << a[i] << " ";
    //cout << endl;

    int ll = 1;
    int rr = 0;
    Add(0);
    for (int i = 1; i <= M; i++)
    {
        if (q[i].l < ll)
        {
            for (int j = ll - 2; j >= q[i].l - 1; j--) 
            {
                //cout << "adding " << j << endl;
                Add(a[j]);
            }
        }
        if (q[i].r > rr)
        {
            for (int j = rr + 1; j <= q[i].r; j++) 
            {
                //cout << "adding " << j << endl;
                Add(a[j]);
            }
        }
        if (q[i].l > ll)
        {
            for (int j = ll - 1; j <= q[i].l - 2; j++) 
            {
                //cout << "removing " << j << endl;
                Delete(a[j]);
            }
        }
        if (q[i].r < rr)
        {
            for (int j = rr; j > q[i].r; j--) 
            {
                //cout << "removing " << j << endl;
                Delete(a[j]);
            }
        }
        ll = q[i].l;
        rr = q[i].r;
        ans[q[i].id] = res;
    }

    for (int i = 1; i <= M; i++) cout << ans[i] << endl;
    return 0;
}