/*
 * Класс, реализующий нормальное распределение точек на поле
 * через преобразования Бокса-Мюллера
 */
#ifndef MAIN_DOTGENERATOR_H
#define MAIN_DOTGENERATOR_H
#include <vector>
#include <random>

// структура координат
struct coord {
    int x, y;
    coord(int new_x,int new_y) {
        x = new_x;
        y = new_y;
    }
};

class DotGenerator{
    //минимальный, разница макс и мин по абсциссе, аналогично по второй коорд
    double min_x, dif_x, min_y, dif_y;
    //массив для точек на поле
    std::vector <coord> field;
    //генератор случайных чисел
    std::minstd_rand0 generator;
private:
    //генерирует одну точку
    coord generate();
public:
    //генерирует поле точек
    DotGenerator(double x_min, double y_min, double x_max, double y_max, int count);
    //возвращает поле
    const std::vector<coord> & getField() const;
};
#endif //MAIN_DOTGENERATOR_H
