#include "graph.h"
#include <set>
#include <queue>
#include "ostov.h"
#include "maxflowapproximation.h"

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
    if(order.size() != graph.size())
        throw;
    vector <int> checker(order.size(), 0);
    checker[0] = 1;
    for(int i = 1; i < order.size(); i++) {
        answer += graph[order[i - 1]][order[i]];
        checker[i]++;
        if(checker[i] > 1)
            throw;
    }
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

Graph Graph::build_flow_way(unsigned start, unsigned end) {
    Graph flow_way(graph.size(), graph.size() - 1);

    vector<int> pre_network(graph.size());
    for(int i = 0; i < pre_network.size(); i++)
        pre_network[i] = i;
    DinicMatrix first(*this, pre_network, pre_network, start, end, false);
    queue <DinicMatrix> myq;
    myq.push(first);

    while(!myq.empty()) {
        DinicMatrix &dinic = myq.front();
        MaxFlow flow(dinic);

        pair <int, int> edge = flow_way.choose_edge(dinic.get_special(), flow.get_network(), dinic.get_start(), dinic.get_end());

        flow_way.add_edge(graph, edge.first, edge.second);
        
        DinicMatrix itock(*this, flow.get_network(), dinic.get_special(), dinic.get_start(), edge.first, false),
                    stock(*this, flow.get_network(), dinic.get_special(), edge.second, dinic.get_end() , true);
        
        if(itock.size() > 2)
            myq.push(itock);
        else if(itock.size() == 2)
            flow_way.add_edge(graph, itock.get_start(), itock.get_end());

        if(stock.size() > 2)
            myq.push(stock);
        else if(stock.size() == 2)
            flow_way.add_edge(graph, stock.get_start(), stock.get_end());
        myq.pop();
    }

    return flow_way;
}

void Graph::add_edge(vector<unordered_map<int, double> >& another_graph, int starting, int ending) {
    if(another_graph[starting].find(ending) == another_graph[starting].end())
        throw;
    graph[starting][ending] = another_graph[starting][ending];
    graph[ending][starting] = another_graph[ending][starting];
}

pair <int, int> Graph::choose_edge(const vector <int>& special, const vector <int>& network, unsigned str, unsigned end) {
    int edge_start = -1, edge_end = -1;
    double min_cost = 1000000000;

    for(int i = 0; i < network.size(); i++) {
        for(int j = i + 1; j < network.size(); j++) {
            if(special[i] == str && special[j] == end)
                continue;
            if(special[j] == str && special[i] == end)
                continue;

            if((network[i] == -1 && network[j] != -1 && graph[j][i] < min_cost)) {
                min_cost = graph[j][i];
                edge_start = special[j];
                edge_end = special[i];
            }
            if((network[j] == -1 && network[i] != -1 && graph[i][j] < min_cost)) {
                min_cost = graph[i][j];
                edge_start = special[i];
                edge_end = special[j];
            }
        }
    }

    if(edge_start == -1)
        throw;
    return make_pair(edge_start, edge_end);
};