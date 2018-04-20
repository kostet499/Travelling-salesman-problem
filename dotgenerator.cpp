/* Класс, реализующий нормальное распределение точек на поле
 * через преобразования Бокса-Мюллера
 */
#include "dotgenerator.h"

// x_min, y_min - координаты левой нижней токи поля, x_max, y_max - правой верхней, count - количество точек
DotGenerator::DotGenerator(double x_min, double y_min, double x_max, double y_max, int count) {
    min_x = x_min;
    dif_x = x_max - x_min;
    min_y = y_min;
    dif_y = y_max - y_min;

    for(int i = 0; i < count; i++)
        field.push_back(generate());
}

// возвращает массив точек - поле
const std::vector<coord> & DotGenerator::getField() const{
    return field;
}

// генерирует точку
coord DotGenerator::generate() const {
    double u = 0, v = 0, s = 0;
    do {
        u = rand(); v = rand();
        u /= RAND_MAX; v /= RAND_MAX;
        s = u * u + v * v;
    } while(s > 1.000000 || s == 0);

    double disp = sqrt(-2 * log(s) / s),
            x = min_x + dif_x * u, y = min_y + dif_y * v;
    return coord(static_cast<int>(x), static_cast<int>(y));
}