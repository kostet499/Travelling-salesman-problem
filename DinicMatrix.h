/*
 * Специальный класс для преобразования Graph в матрицу для работы максимального потока
 */
#ifndef MAIN_DINICMATRIX_H
#define MAIN_DINICMATRIX_H
#include "graph.h"
class DinicMatrix {
private:
    // матрица пропускных способнойстей
    vector < vector <double> > matrix;
    vector <unsigned> special;
    // количество вершин, количество ребер
    size_t n, m;
    unsigned start = 0, end = 0;
public:
    DinicMatrix(Graph&, vector<int>&, vector<unsigned >&, unsigned, unsigned, bool);

    size_t size() const;

    size_t edges() const;

    unsigned get_start() const;

    unsigned get_end() const;

    vector <unsigned>& get_special();

    vector <double>:: iterator begin(unsigned);

    friend istream&operator>> (istream& is, DinicMatrix& gr) {
        is >> gr.n >> gr.m;
        gr.matrix.resize(gr.n);
        for(int i = 0; i < gr.n; i++)
            gr.matrix[i].resize(gr.n, 0);

        for(int i = 0; i < gr.m; i++) {
            int x = 0, y = 0, pass = 0;
            is >> x >> y >> pass;
            x--; y--;
            gr.matrix[x][y] = pass;
        }
        return is;
    }
};

#endif //MAIN_DINICMATRIX_H
