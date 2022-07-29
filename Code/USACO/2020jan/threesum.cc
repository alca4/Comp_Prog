#include<iostream>
#include<fstream>
#include<vector>
#include<algorithm>
using namespace std;

int N, Q;
int A[5000];
int intervals[5000][5000];

int main()
{
    ifstream fin ("threesum.in");
    fin >> N >> Q;
    for (int i = 0; i < N; i++) fin >> A[i];
    for (int i = 3; i <= N; i++) // size of interval
    {
        for (int s = 0; s <= N - i; s++) // start
        {
            int e = s + i - 1;
            if (i == 3) 
                intervals[s][e] = (A[s] + A[s + 1] + A[s + 2] == 0 ? 1 : 0);
            else
            {
                intervals[s][e] = intervals[s][e - 1] + intervals[s + 1][e] -
                                  intervals[s + 1][e - 1];
                cout << intervals[s][e - 1] << endl;
                cout << intervals[s + 1][e] << endl;
                cout << intervals[s + 1][e - 1] << endl;
            }
            cout << "interval from " << s << " to " << e << " has "
                 << intervals[s][e] << " solutions" << endl;
        }
    }
    return 0;
}