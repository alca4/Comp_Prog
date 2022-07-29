/*
  ___
 (o,o)
<  .  >
--"-"---
Rowlet is orz
*/
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
#include <bitset>
using namespace std;

#define pb push_back
#define ll long long
#define ld long double
#define INF 1000000000ull
#define MOD 1000000007

typedef pair<int, int> pii;
typedef pair<ll, ll> pll;

int read()
{
    int a;
    cin >> a;
    return a;
}

const int MAXN = 200010;

void solve()
{
    string str;
    str.clear();
    cin >> str;

    int N = str.length();

    int pos[MAXN];
    int P = 0;
    int score = 0;
    bool ans = 1;
    for (int i = 0; i < str.length(); i++) 
    {
        if (str[i] == '(') score++;
        if (str[i] == ')') score--;
        if (str[i] == '?') pos[++P] = i;
    }

    int div = (P - score) / 2;
    if (div == 0 || div == P) 
    {
        cout << "YES" << endl;
        for (int i = 1; i <= P; i++) pos[i] = 0;
        return;
    }

    for (int i = 1; i < div; i++) str[pos[i]] = '(';
    str[pos[div]] = ')';
    str[pos[div + 1]] = '(';
    for (int i = div + 2; i <= P; i++) str[pos[i]] = ')';
    
    score = 0;
    for (int i = 0; i < str.length(); i++)
    {
        if (str[i] == '(') score++;
        if (str[i] == ')') score--;
        if (score < 0) ans = 0;
    }

    if (!ans || P == 0) cout << "YES" << endl;
    else cout << "NO" << endl;
    
    for (int i = 1; i <= P; i++) pos[i] = 0;
}

int main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    int T;
    cin >> T;
    while (T--) solve();
}