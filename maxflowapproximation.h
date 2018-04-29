/*
 * Класс для приближения лучше, чем 1,5
 */
#ifndef MAIN_MAXFLOWAPPROXIMATION_H
#define MAIN_MAXFLOWAPPROXIMATION_H
#include "DinicMatrix.h"
#include <queue>
class MaxFlowApproximation {
private:
    double answer = 0;
    unsigned start = 0, end = 0;
    // слоистая сеть, массив указателей на непосещенные вершины для дфс
    vector <int> network, pointer;
    // постройка слоистой сети
    bool build_network(DinicMatrix &graph);

    // создание блокирующего потока
    double break_flow(DinicMatrix &graph, int vertex, double current);

public:
    explicit MaxFlowApproximation(DinicMatrix &graph);

};

#endif //MAIN_MAXFLOWAPPROXIMATION_H
