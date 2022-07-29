#include <iostream>
#include <algorithm>
#include <vector>
#include <map>
#include <set>
using namespace std;

int T, N;

void solve()
{
    string str;
    cin >> str;
    set<char> distinct;
    for (int i = 0; i < str.length(); i++) 
    {
        if (distinct.find(str[i]) == distinct.end())
            distinct.insert(str[i]);
        else break;
    }
    for (int i = distinct.size(); i < str.length(); i++)
    {
        if (str[i] != str[i - distinct.size()]) 
        {
            cout << "NO" << endl;
            return;
        }
    }
    cout << "YES" << endl;
}

int main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    cin >> T;
    while (T--) solve();
    return 0;
}