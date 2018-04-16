/* Класс графа для нахождения решения
 */

#ifndef MAIN_GRAPH_H
#define MAIN_GRAPH_H
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
    Graph(vector <coord> field);

    // дефолтный конструктор
    Graph(size_t n, size_t m);

    size_t size();

    size_t edges_count();

    unordered_map <int, double>::iterator begin(int vertex);

    unordered_map <int, double>::iterator end(int vertex);

    vector <unordered_map <int, double> >:: iterator begin();

    vector <unordered_map <int, double> >:: iterator end();

    Graph&operator=(Graph& graph);

    //постройка минимального остовного дерева с помощью алгоритма Прима
    Graph buildMST();

    // подсчет расстояния между двумя точками
    double count_distance(coord a, coord b);

    // обход вершин с помощью dfs и возвращения порядка вершин для построения приблизительного решения
    vector <int> walk();

    // подсчет решения по порядку вершин в массиве order
    double count_way(vector <int> order);

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

class Ostov{
private:
    int end_size = 0, current_size = 0;
    vector <bool> inTree;
public:
    explicit Ostov(int size);
    bool add(int vertex);
    bool in_tree(int vertex);
};

#endif //MAIN_GRAPH_H
