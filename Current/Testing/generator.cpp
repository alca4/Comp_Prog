#include <iostream>
#include <chrono>
#include <set>
using namespace std;

typedef pair<int, int> pii;

int rand32() {
    return abs(rand() << 15 | rand());
}

int N = 100;
int M = 100000;
set<pii> edges;

int main() {
    srand(time(NULL));
    cout << N << " " << M << endl;
    cout << 0 << endl;
    for (int i = 2; i <= N; i++) cout << (rand32() % 1000000000) << endl;
    return 0;
}