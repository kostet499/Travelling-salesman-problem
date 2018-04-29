#include "DinicMatrix.h"

DinicMatrix::DinicMatrix(Graph& graph, vector<int>& network, vector<unsigned> &spec, unsigned start, unsigned end, bool mode) {
    n = 0;
    m = 0;
    for(int i = 0; i < network.size(); i++) {
        if(network[i] > -1 || (network[i] == -1 && mode)) {
            special.emplace_back(spec[i]);
            n++;
        }
    }
    this->start = start;
    this->end = end;

    matrix.resize(n);
    for(int i = 0; i < n; i++) {
        matrix[i].resize(n, 0.000);
        for(int j = 0; j < n; j++)
            matrix[i][j] = (*(graph.begin() + special[i]))[special[j]];
    }

    matrix.resize(n);
}

size_t DinicMatrix::size() const {
    return n;
}

size_t DinicMatrix::edges() const{
    return m;
}

unsigned DinicMatrix::get_start() const {
    return start;
}

unsigned DinicMatrix::get_end() const {
    return end;
}

vector <unsigned>& DinicMatrix::get_special() {
    return special;
}

vector <double>::iterator DinicMatrix::begin(unsigned vertex) {
    return matrix[vertex].begin();
}

