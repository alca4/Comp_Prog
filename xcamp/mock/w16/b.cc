/*
Learnings:

If WA with simple code, write down proof then challenge each step
*/
#include <iostream>
#include <algorithm>
#include <vector>
#include <cstdint>
using namespace std;

#define ll long long

typedef pair<ll, ll> pii;

ll N, K;
pii ins[100010];

int main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    cin >> N >> K;
    string str;
    cin >> str;

    ins[0] = pii(0, 0);
    for (int i = 1; i <= N; i++)
    {
        ins[i] = ins[i - 1];
        if (str[i - 1] == 'R') ins[i].first++;
        if (str[i - 1] == 'L') ins[i].first--;
        if (str[i - 1] == 'U') ins[i].second++;
        if (str[i - 1] == 'D') ins[i].second--;
    }

    ll best = 0;
    for (int i = 1; i <= N; i++)
    {
        best = max(best, abs(ins[N].first * (K - 1) + ins[i].first) + 
                         abs(ins[N].second * (K - 1) + ins[i].second));
    }
    for (int i = 1; i <= N; i++)
    {
        best = max(best, abs(ins[i].first) + abs(ins[i].second));   
    }
    cout << best << endl;
    return 0;
}