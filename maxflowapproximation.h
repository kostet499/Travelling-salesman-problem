/*
 * Класс для поиска максимального потока
 */
#ifndef MAIN_MAXFLOWAPPROXIMATION_H
#define MAIN_MAXFLOWAPPROXIMATION_H
#include "DinicMatrix.h"
#include <queue>
class MaxFlow {
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
    explicit MaxFlow(DinicMatrix &graph);
    // получить сеть
    const vector <int>& get_network() const;

    vector <int>& get_not_const_network();
};

#endif //MAIN_MAXFLOWAPPROXIMATION_H
