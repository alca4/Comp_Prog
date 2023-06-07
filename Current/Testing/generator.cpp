#include <iostream>
#include <chrono>
using namespace std;

int rand32() {
    return abs(rand() << 16 | rand());
}

int N = 200000;
int Q = 200000;

int main() {
    srand(time(NULL));
    cout << N << " " << Q << endl;
    for (int i = 1; i <= N; i++) cout << i << " ";
    cout << endl;
    for (int i = 1; i <= Q; i++) {
        int t = rand32() % 3;
        t++;
        cout << t << " ";
        if (t != 2) {
            int l = rand32() % N + 1;
            int r = rand32() % N + 1;
            if (l > r) swap(l, r);
            cout << l << " " << r << endl;
        }
        else {
            int l = rand32() % (N - 1) + 2;
            int r = rand32() % (N - 1) + 2;
            if (l > r) swap(l, r);
            int k = rand32() % (l - 1) + 1;
            cout << l << " " << r << " " << k << endl;
        }
    }
    return 0;
}