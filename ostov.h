/*
 * Вспомогательный класс для постройки дереве
 * Не более
 */

#ifndef MAIN_OSTOV_H
#define MAIN_OSTOV_H
#include <vector>
class Ostov{
private:
    int end_size = 0, current_size = 0;
    std::vector <bool> inTree;
public:
    explicit Ostov(int size);
    bool add(int vertex);
    bool in_tree(int vertex) const;
};
#endif //MAIN_OSTOV_H
