#include "DinicMatrix.h"

DinicMatrix::DinicMatrix(Graph& graph,
                         const vector<int> &network,
                         const vector<int> &spec,
                         unsigned start,
                         unsigned end,
                         bool mode) {
    n = 0;
    m = 1;
    for(int i = 0; i < network.size(); i++) {
        if ((network[i] > -1 && !mode) || (network[i] == -1 && mode)) {
            if(spec[i] == start)
                this->start = special.size();
            if(spec[i] == end)
                this->end = special.size();
            special.emplace_back(spec[i]);
            n++;
        }
    }

    matrix.resize(n);
    for(int i = 0; i < n; i++) {
        matrix[i].resize(n, 0.000);
        if(special[i] == end)
            continue;
        for(int j = 0; j < n; j++)
            if(special[j] != start)
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

const vector <int>& DinicMatrix::get_special() {
    return special;
}

vector <double>::iterator DinicMatrix::begin(unsigned vertex) {
    return matrix[vertex].begin();
}

