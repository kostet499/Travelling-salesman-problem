//
// Created by Toreno on 16.04.2018.
//

#ifndef MAIN_TESTER_H
#define MAIN_TESTER_H

#include "graph.h"

class Tester {
private:
    int vertices;
    vector <double> average, average_evasion;
public:
    // конструктор, в котором всё прогоняется
    // [start, end] - диапазон количества вершин для эксперимента, experiments - число
    // экспериментов для каждого количества вершин из диапазона
    Tester(int start, int end, int experiments);

    // получение массива average
    vector<double> average_statistics();

    // получение массива average_evasion
    vector<double> average_evasion_statistics();

    // подсчет average и evasion для одного конкретного количества вершин
    void count_average(int number, vector <double> &exp);

    friend ostream&operator<<(ostream& os, Tester& test) {
        for(int i = 0; i < test.vertices; i++)
            cout << test.average[i] << " " << test.average_evasion[i] << endl;
    }
};

#endif //MAIN_TESTER_H
