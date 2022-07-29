#include<iostream>
#include<algorithm>
#include<vector>
using namespace std;

int H;
vector<int> heights;
vector<int> incdec;

int main()
{
    int longest = 0;
    cin >> H;
    for (int i = 0; i < H; i++)
    {
        int a;
        cin >> a;
        heights.push_back(a);
    }

    incdec.resize(H - 1);

    for (int i = 0; i < H - 1; i++)
    {
        if (heights[i] < heights[i + 1]) incdec[i] = 1;
        else if (heights[i] > heights[i + 1]) incdec[i] = -1;
        else incdec[i] = 0;
        //cout << incdec[i] << " ";
    }
    //cout << endl;

    int cur = 1;
    int condition = 0;
    for (int i = 0; i < H - 1; i++)
    {
        //cout << "i is: " << i << endl;
        //cout << "cur is: " << cur << endl;
        if (incdec[i] == 1)
        {
            if (condition > -1) 
            {
                cur++;
                condition = 1;
            }
            else 
            {
                //cout << "ended cycle" << endl;
                longest = max(cur, longest);
                cur = 2;
                condition = 1;
            }
        }
        if (incdec[i] == 0)
        {
            if (condition == -1) longest = max(cur, longest);
            cur = 1;
            condition = 0;
        }
        if (incdec[i] == -1)
        {
            if (condition == 1)
            {
                cur++;
                condition = -1;
            }
            else if (condition == -1)
            {
                cur++;
            }
        }
    }
    if (condition == -1) longest = max(cur, longest);

    cout << longest << endl;
    return 0;
}