#include "tester.h"
// вывод
// качетво приближения, среднеквадратичное отклонение от приближения
using namespace std;

int main() {
    Tester test(4, 10, 200);
    cout << test;
    return 0;
}