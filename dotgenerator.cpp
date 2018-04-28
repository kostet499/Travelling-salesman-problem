#include "dotgenerator.h"
#include <ctime>
#include <chrono>
using std::linear_congruential_engine;
// x_min, y_min - координаты левой нижней токи поля, x_max, y_max - правой верхней, count - количество точек
DotGenerator::DotGenerator(double x_min, double y_min, double x_max, double y_max, int count) {
    min_x = x_min;
    dif_x = x_max - x_min;
    min_y = y_min;
    dif_y = y_max - y_min;
    unsigned int seed = std::chrono::system_clock::now().time_since_epoch().count();
    generator.seed(seed);
    for(int i = 0; i < count; i++)
        field.push_back(generate());
}

// возвращает массив точек - поле
const std::vector<coord> & DotGenerator::getField() const{
    return field;
}

// генерирует точку
coord DotGenerator::generate() {
    double u = 0, v = 0, s = 0;
    do {
        u = generator(); v = generator();
        u /= generator.max(); v /= generator.max();
        s = u * u + v * v;
    } while(s > 1.000000 || s == 0);

    double disp = sqrt(-2 * log(s) / s),
            x = min_x + dif_x * u * disp, y = min_y + dif_y * v * disp;
    return coord(static_cast<int>(x), static_cast<int>(y));
}