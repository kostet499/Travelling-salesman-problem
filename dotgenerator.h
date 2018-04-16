//
// Created by Toreno on 15.04.2018.
//

#ifndef MAIN_DOTGENERATOR_H
#define MAIN_DOTGENERATOR_H

#include <vector>
#include <cmath>
#include <random>
#include <ctime>
struct coord {
    int x, y;
    coord(int new_x,int new_y) {
        x = new_x;
        y = new_y;
    }
};

class DotGenerator{
    double min_x, dif_x, min_y, dif_y;
    std::vector <coord> field;
private:
    coord generate();
public:
    DotGenerator(double x_min, double y_min, double x_max, double y_max, int count);
    std::vector <coord> getField();
};
#endif //MAIN_DOTGENERATOR_H