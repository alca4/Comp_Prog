#include <iostream>
#include <algorithm>
using namespace std;

int main()
{
    srand(time(NULL));
    int N = 1;
    cout << N << endl;
    for (int i = 0; i < N; i++)
    {
        for (int j = 1; j <= 10000; j++)
        {
            int a = rand() % 26;
            char c = a + 'a';
            cout << c;
        }
        cout << endl;
    }
    return 0;
}