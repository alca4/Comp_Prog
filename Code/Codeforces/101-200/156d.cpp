#include<iostream>
#include<map>
#include<algorithm>
using namespace std;

int N, M, K;
int p[100010];
int r[100010];
map<int, int> buckets;

int Root(int a)
{
    return (p[a] == a) ? a : Root(p[a]);
}

void Combine(int a, int b)
{
    a = Root(a), b = Root(b);
    if (a == b) return;
    if (r[a] > r[b])
        p[b] = a;
    else
    {
        if (r[a] == r[b])
        r[b]++;
        p[a] = b;
    }   
    //cout << "combined" << endl;
}

int main()
{
    cin >> N >> M >> K;
    for (int i = 1; i <= N; i++) p[i] = i, r[i] = 0;
    for (int i = 0; i < M; i++)
    {
        int a, b;
        cin >> a >> b;
        Combine(a, b);
    }
    //cout << "never got here" << endl;

    long long ans = 1;
    for (int i = 1; i <= N; i++)
        buckets[Root(i)]++;

    if (buckets.size() == 1)
    {
        cout << 1 % K << endl;
        return 0;
    }

    for (auto n : buckets)
        ans = (ans * n.second) % K;

    for (int i = 0; i < buckets.size() - 2; i++)
        ans = (ans * N) % K;
    cout << ans % K << endl;
    return 0;
}