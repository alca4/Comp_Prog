#include <iostream>
#include <chrono>
#include <set>
using namespace std;

typedef pair<int, int> pii;

int rand32() {
    return abs(rand() << 15 | rand());
}

int N = 300000;
int M = 100000;
set<pii> edges;

int main() {
    srand(time(NULL));
    cout << N << endl;
    for (int i = 1; i <= N; i++) cout << (rand32() % N) + 1 << endl;
    cout << rand32() % N + 1 << " " << rand32() % N + 1 << endl;
    return 0;
}