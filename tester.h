/*
 * Класс тестирует решение, выводит среднее значение приближения, отклонения
 */
#ifndef MAIN_TESTER_H
#define MAIN_TESTER_H

#include "graph.h"

class Tester {
private:
    //количество вершин, на которых произвести тест(передается пользователем)
    unsigned vertices;
    //массивы средних значений и уклонений от среднего для каждой вершины по количеству экспериментов
    vector <double> average, average_evasion;
public:
    // конструктор, в котором всё прогоняется
    // [start, end] - диапазон количества вершин для эксперимента, experiments - число
    // экспериментов для каждого количества вершин из диапазона
    Tester(int start, int end, int experiments);

    // получение массива average
    const vector<double>& average_statistics() const;

    // получение массива average_evasion
    const vector<double>& average_evasion_statistics() const;

    // приближение остовным деревом
    double mst_solution(Graph&) const;

    double flow_solution(Graph&) const;

    double angle_solution(Graph&) const;

    // решение перебором
    double bruteforce_solution(Graph&, double) const;

    //проведение одной генерации поля и запуска алгоритмов приближения
    vector<double> run_experiment(int) const;

    // подсчет average и evasion для одного конкретного количества вершин
    void count_average(int number, vector <double> &exp);

    friend ostream&operator<<(ostream& os, const Tester& test) {
        for(int i = 0; i < test.vertices; i++)
            cout << test.average[i] << " " << test.average_evasion[i] << endl;
    }
};

#endif //MAIN_TESTER_H
