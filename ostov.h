/*
 * Вспомогательный класс для постройки дереве
 * Не более
 */

#ifndef MAIN_OSTOV_H
#define MAIN_OSTOV_H
#include <vector>
class Ostov{
private:
    //конечный размер, текущий размер
    int end_size = 0, current_size = 0;
    //массив для опредления какие вершины уже в остовном дереве
    std::vector <bool> inTree;
public:
    //инициализация
    explicit Ostov(int size);
    //добавление одной вершины
    bool add(int vertex);
    //лежит ли вершина в дереве
    bool in_tree(int vertex) const;
};
#endif //MAIN_OSTOV_H
