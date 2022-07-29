#include<iostream>
#include<algorithm>
#include<set>
#include<vector>
using namespace std;

int N;
int vals[100010];
int inc[100010];
int dec[100010];
multiset<int> increasing;
multiset<int> decreasing;

int main()
{
    cin >> N;
    for (int i = 0; i < N; i++) cin >> vals[i];

    for (int i = 0; i < N; i++)
    {
        increasing.insert(vals[i]);
        inc[i] = increasing.find(vals[i]) - increasing.begin();
    }

    for (int i = 0; i < N; i++)
    {
        decreasing.insert(vals[N - 1 - i]);
        dec[i] = decreasing.end() - decreasing.find(vals[i]);
    }
}