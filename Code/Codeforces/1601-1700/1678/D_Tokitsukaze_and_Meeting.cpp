/*
Learnings:

Calculate things independently if possible
*/
#include <iostream>
#include <algorithm>
#include <vector>
#include <cstring>
using namespace std;

int T, N, M;
int row[1000010];
int col[1000010];

int main()
{
    scanf("%d", &T);
    while (T--)
    {
        for (int i = 0; i <= max(M, N); i++) row[i] = col[i] = 0;
        scanf("%d%d", &N, &M);
        int last = -N * M;
        int cols = 0;
        for (int i = 0; i < N * M; i++)
        {
            char tmp;
            scanf(" %c", &tmp);
            int val = tmp - '0';
            
            if (val == 1)
            {
                last = i;
                if (col[i % M] == 0)
                {
                    cols++;
                    col[i % M] = 1;
                }
            }

            if (i - last < M) row[i % M]++;

            if (i != 0) printf(" ");
            printf("%d", row[i % M] + cols);
        }
        printf("\n");
    }
    return 0;
}