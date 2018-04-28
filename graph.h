/*
 * Класс графа для нахождения решения
 */

#ifndef MAIN_GRAPH_H
#define MAIN_GRAPH_H
#include <vector>
#include "dotgenerator.h"
#include <unordered_map>
#include <iostream>
using namespace std;

class Graph {
private:
    vector < unordered_map <int, double> > graph;
    size_t n, m;
public:
    // постройка графа по полю
    explicit Graph(const vector <coord> &field);

    // дефолтный конструктор
    Graph(size_t n, size_t m);

    size_t size() const;

    size_t edges_count() const;

    unordered_map <int, double>::iterator begin(int vertex);

    unordered_map <int, double>::iterator end(int vertex);

    vector <unordered_map <int, double> >:: iterator begin();

    vector <unordered_map <int, double> >:: iterator end();

    //постройка минимального остовного дерева с помощью алгоритма Прима
    Graph buildMST();

    // подсчет расстояния между двумя точками
    double count_distance(coord a, coord b) const;

    // обход вершин с помощью dfs и возвращения порядка вершин для построения приблизительного решения
    vector <int> walk();

    // подсчет решения по порядку вершин в массиве order
    double count_way(const vector <int> &order);

    // нахождение оптимального решения перебором за факториал
    void optimal_solution(int vertex, double &answer, double &minim, vector <bool> &way, int &vertices);

    void dfs(int vertex, vector <int> &stock, vector <bool> &visited);

    friend istream&operator>> (istream& is, Graph& gr) {
        is >> gr.n >> gr.m;
        gr.graph.resize(gr.n);
        for(int i = 0; i < gr.m; i++) {
            int x = 0, y = 0;
            double weight = 0;
            is >> x >> y >> weight;
            x--; y--;
            gr.graph[x][y] = weight;
            gr.graph[y][x] = weight;
        }
    }
};
#endif //MAIN_GRAPH_H
