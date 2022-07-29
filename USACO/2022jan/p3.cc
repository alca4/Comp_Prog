#include<iostream>
#include<vector>
#include<algorithm>
using namespace std;

typedef vector<long> vi;

int N, K;
vi ans;
vi j;

int main()
{
    cin >> N;
    j.resize(N + 1);
    ans.resize(N + 1);
    long max_k = 0;
    for (int i = 1; i <= N; i++) 
    {
        cin >> j[i];
    }
    K = 1e6;
    ans[1] = 0;
    int id = 1;
    for (int i = 1; i < N; i++)
    {
        if (j[i + 1] == j[i]) ans[i + 1] = ans[i] + 1;
        else if (j[i] != i) ans[i + 1] = ans[i] + K;
        else ans[i + 1] = ans[i] + K + 1;
    }

    cout << K << endl;
    for (int i = 1; i <= N; i++)
    {
        cout << ans[i] << endl;
    }
    return 0;
}