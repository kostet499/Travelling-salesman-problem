/*
 * Класс графа с большой функциональнойстью
 */

#ifndef MAIN_GRAPH_H
#define MAIN_GRAPH_H
#include <vector>
#include "dotgenerator.h"
#include <unordered_map>
#include <iostream>
#include <set>
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

    // количество вершин
    size_t size() const;

    //количество ребер
    size_t edges_count() const;

    vector <unordered_map <int, double> >:: iterator begin();

    Graph build_flow_way(unsigned start, unsigned end);

    //постройка минимального остовного дерева с помощью алгоритма Прима
    Graph buildMST() const;

    pair <int, int> choose_edge(const vector <int>&, const vector <int>&, unsigned, unsigned);

    // подсчет расстояния между двумя точками
    double count_distance(coord a, coord b) const;

    // обход вершин с помощью dfs и возвращения порядка вершин для построения приблизительного решения
    vector <int> walk() const;

    // подсчет решения по порядку вершин в массиве order
    double count_way(const vector <int>&);

    // нахождение оптимального решения перебором за факториал
    void optimal_solution(int, double, double &, vector <bool> &, int);

    double build_angle_way();

    void add_edge(vector < unordered_map <int, double> >&, int, int);

    void add_edge(double, int, int);

    void add_one_edge(double, int, int);

    double fig_angle(int, int, int);

    double fig_edges(int, int, int);

    tuple <int, int, int> choose_triangle(Graph&, set <int> &) const;

    void del_edge(int, int);

    // дфс обход для приближения
    void dfs(int vertex, vector <int> &stock, vector <bool> &visited) const;

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
