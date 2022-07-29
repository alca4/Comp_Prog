#include<iostream>
using namespace std;

int main()
{
    int n = 4;
    for (int i = 1; i <= 4; i++)
    {
        for (int j = 1; j <= 4; j++)
        {
            int a = i;
            int b = j;
            if (a <= n / 4) a += n / 4;
            if (a > 3 * n / 4) a -= n / 4;
            if (b <= n / 4) b += n / 4;
            if (b > 3 * n / 4) b -= n / 4;
            a -= n / 4;
            b -= n / 4;
            cout << a << " " << b << "  ";
        }
        cout << endl;
    }
    return 0;
}