#include<iostream>
#include<vector>
#include<algorithm>
using namespace std;

int N, K;
string marbles;

int main()
{
    cin >> N >> K;
    cin >> marbles;
    vector<int> seg(N);
    int used = 0;
    int id = 0;
    bool white = (marbles[0] == 'W');
    for (int i = 0; i < marbles.length(); i++)
    {
        if (white && !marbles[i] == 'W') white = !white, id++;
        if (!white && marbles[i] == 'W') white = !white, id++;
        if (white) seg[i]++;
        else seg[i]--;
    }
    
    for (int i = 0; i < seg.size(); i++) cout << seg[i] << endl;
}