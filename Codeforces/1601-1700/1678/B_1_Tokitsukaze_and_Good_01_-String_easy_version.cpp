#include <iostream>
#include <algorithm>
#include <vector>
using namespace std;

int T;
int N;
string str;
int consec[200010];

int main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    cin >> T;
    while (T--)
    {
        cin >> N;
        cin >> str;
        int last = -1;
        int len = 0;
        int id = 0;
        for (int i = 0; i < str.length(); i++)
        {
            if (str[i] != last) 
            {
                consec[id++] = len;
                len = 0;
                last = str[i];
            }
            len++;
        }
        consec[id++] = len;
        int switches = 0;
        for (int i = 1; i < id - 1; i++)
        {
            if (consec[i] % 2 == 1)
            {
                switches++;
                consec[i]++;
                consec[i + 1]++;
            }
        }
        cout << switches << endl;
    }
    return 0;
}