#include<iostream>
#include<fstream>
#include<vector>
#include<algorithm>
using namespace std;

int N;
int nums[248];
int memo[248][248];
int loc[248][248];

int main()
{
    ifstream fin ("248.in");
    fin >> N;
    for (int i = 0; i < N; i++) fin >> nums[i];

    for (int i = 1; i <= N; i++)
    {
        for (int j = 0; j < N - i + 1; j++)
        {
            if (i == 1)
            {
                memo[i][j] = nums[j];
                loc[i][j] = 3;
                continue;
            }

            int max_val = 0;
            int max_loc = 0;
            for (int k = j; i < i + j - 2; k++)
            {
                int start_val = memo[k - j + 1][j];
                int end_val = memo[i - j + k - 2][k + 1];
                int start_loc = loc[k - j + 1][j];
                int end_loc = loc[i - j + k - 2][k + 1];

                int val = max(start_val, end_val);
                if (start_loc | 1 == start_loc &&
                    end_loc | 2 == end_loc)
                    val++;
                if (val > max_val)
                {
                    max_val = val;
                    max_loc = (start_loc | 1 == start_loc) ? start_loc | 2 - 1 : 
                                                             start_loc | 2;
                }
            }
        }
    }

}