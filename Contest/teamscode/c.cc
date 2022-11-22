#include<iostream>
#include<algorithm>
using namespace std;

int adjmat[100][100];

int main()
{
    /*
    int T;
    cin >> T;
    for (int i = 0; i < T; i++)
    {*/
        int N, A, B;
        cin >> N >> A >> B;
        for (int i = 0; i <= N; i++)
            for (int j = 0; j <= N; j++)
                adjmat[i][j] = (i ^ j ^ N);
        for (int k = 0; k <= N; k++)
        {
            for (int j = 0; j <= N; j++)
            {
                if (k == j) continue;
                for (int i = 0; i <= N; i++)
                {
                    if (k == i || j == i) continue;
                    adjmat[i][j] = min(adjmat[i][j], max(adjmat[i][k], adjmat[k][j]));
                }
            }
        }
        for (int i = 0; i <= N; i++)
        {
            for (int j = 0; j <= N; j++)
            {
                if (i == j) cout << "0 ";
                else cout << adjmat[i][j] << " ";    
            }
            cout << endl;
        }
                
    return 0;
}