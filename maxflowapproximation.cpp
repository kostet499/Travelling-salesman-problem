#include "maxflowapproximation.h"
bool MaxFlowApproximation::build_network(DinicMatrix &graph) {
    fill(network.begin(), network.end(), -1);
    queue <unsigned> bfs;
    bfs.push(start);
    network[start] = 0;
    while(!bfs.empty()) {
        int vertex = bfs.front();
        bfs.pop();
        auto pass = graph.begin(vertex);
        for(unsigned i = 0; i < graph.size(); i++) {
            if(network[i] == -1 && *(pass + i) > 0.000) {
                network[i] = network[vertex] + 1;
                bfs.push(i);
            }
        }
    }
    return network[end] == -1;
}

double MaxFlowApproximation::break_flow(DinicMatrix &graph, int vertex, double current) {
    if(current == 0.000)
        return 0;
    if(vertex == end)
        return current;
    auto pass = graph.begin(vertex);
    for(int &next = pointer[vertex]; next < graph.size(); next++) {
        if (network[next] == network[vertex] + 1) {
            double passed_current = break_flow(graph, next, min(current, *(pass + next)));
            if (passed_current) {
                (pass + next) -= passed_current;
                (graph.begin(next) + vertex) += passed_current;
                return passed_current;
            }
        }
    }
    return 0;
}

MaxFlowApproximation::MaxFlowApproximation(DinicMatrix &graph) {
    if(!graph.size() || !graph.edges())
        return;
    start = graph.get_start();
    end = graph.get_end();
    pointer.resize(graph.size());
    network.resize(graph.size());
    for(;;) {
        if(build_network(graph))
            break;

        fill(pointer.begin(), pointer.end(), 0);
        for(;;) {
            double additive_current = break_flow(graph, 0, 100000000);
            if(additive_current < 0.001)
                break;
            answer += additive_current;
        }
    }
}

const vector <int>& MaxFlowApproximation::get_network() {
    return network;
}
