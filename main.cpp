#include "tester.h"
// вывод
// качетво приближения, среднеквадратичное отклонение от приближения
using namespace std;

int main() {
    int a, b, c;
    cin >> a >> b >> c;
    Tester test(a, b, c);
    cout << test;
    return 0;
}