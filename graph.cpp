#include "graph.h"
#include <set>
#include "ostov.h"

double Graph::count_distance(coord a, coord b) const{
    int x_dif = a.x - b.x, y_dif = a.y - b.y;
    return sqrt(static_cast<double>(x_dif * x_dif + y_dif * y_dif));
}

Graph::Graph(const vector<coord> &field) {
    n = field.size();
    m = (n * (n - 1)) / 2;
    graph.resize(field.size());
    for(int i = 0; i < field.size(); i++) {
        for(int j = i + 1; j < field.size(); j++) {
            double distance = count_distance(field[i], field[j]);
            graph[i][j] = distance;
            graph[j][i] = distance;
        }
    }
}

Graph::Graph(size_t size, size_t edges) {
    n = size;
    m = edges;
    graph.resize(n);
};

size_t Graph::size() const {
    return n;
}

size_t Graph::edges_count() const {
    return m;
}

vector <unordered_map <int, double> >::iterator Graph::begin() {
    return graph.begin();
};

Graph Graph::buildMST() const {
    Graph mst(graph.size(), graph.size() - 1);
    Ostov tree(graph.size());
    int vertex = 0;
    set <pair <double, int> > edges;
    if (!size() || !edges_count())
        return mst;
    while (!tree.add(vertex)) {
        for (auto i : graph[vertex])
            if (!tree.in_tree(i.first)) {
                double bir = i.second;
                int num = i.first;
                edges.insert(make_pair(bir, num));
            }

        pair<double, int> edge;
        do {
            if (edges.empty())
                return mst;
            edge = *edges.begin();
            edges.erase(edges.begin());
        } while (tree.in_tree(edge.second));

        (*(mst.begin() + vertex))[edge.second] = edge.first;
        vertex = edge.second;
    }
    return mst;
}

void Graph::dfs(int vertex, vector <int> &stock, vector <bool> &visited) const {
    stock.emplace_back(vertex);
    visited[vertex] = true;
    for(auto i : graph[vertex])
        if(!visited[i.first])
            dfs(i.first, stock, visited);
}

vector <int> Graph::walk() const {
    vector <int> stock;
    vector <bool> visited(graph.size(), false);
    dfs(0, stock, visited);
    return stock;
}

double Graph::count_way(const vector <int> &order) {
    double answer = 0;
    for(int i = 1; i < order.size(); i++)
        answer += graph[order[i - 1]][order[i]];
    answer += graph[order[order.size() - 1]][0];
    return answer;
}

void Graph::optimal_solution(int vertex, double &answer, double &minim, vector<bool> &way, int &vertices) {
    way[vertex] = false;
    if(way.size() == vertices) {
        answer += graph[vertex][0];
        if(answer < minim)
            minim = answer;
        answer -= graph[vertex][0];
        return;
    }

    for(auto i : graph[vertex]) {
        int next = i.first; double weight = i.second;
        if(way[next]) {
            answer += weight;
            if(answer < minim) {
                vertices++;
                optimal_solution(next, answer, minim, way, vertices);
                way[next] = true;
                vertices--;
            }
            answer -= weight;
        }
    }
}

double Graph::build_flow_way(unsigned start, unsigned end) {

}