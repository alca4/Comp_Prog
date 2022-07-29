#include<iostream>
#include<fstream>
#include<algorithm>
#include<map>
using namespace std;

int T, A, B;
bool memo[5000001][2];

int main()
{
    ifstream fin("feast.in");
    fin >> T >> A >> B;
    memo[0][0] = true;
    // assume no water
    for (int i = 0; i <= T; i++)
    {
        if (!memo[i][0]) continue;
        if (i + A <= T) memo[i + A][0] = memo[i][0];
        if (i + B <= T) memo[i + B][0] = memo[i][0];
        memo[i / 2][1] = memo[i][0];
    }
    // assume water
    for (int i = 0; i <= T; i++)
    {
        if (!memo[i][1]) continue;
        if (i + A <= T) memo[i + A][1] = memo[i][1];
        if (i + B <= T) memo[i + B][1] = memo[i][1];
    }
    int maxv = 0;
    for (int i = 0; i <= T; i++) if (memo[i][0]) maxv = max(maxv, i);
    for (int i = 0; i <= T; i++) if (memo[i][1]) maxv = max(maxv, i);

    ofstream fout("feast.out");
    fout << maxv << endl;
    return 0;
}