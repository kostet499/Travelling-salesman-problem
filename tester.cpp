#include "tester.h"

Tester::Tester(int start, int end, int experiments) {
    end++;
    vertices = end - start;
    average.resize(vertices);
    average_evasion.resize(vertices);

    for(int vers = start; vers < end; vers++) {
        vector <double> exp(experiments);
        for(int i = 0; i < experiments; i++) {
            vector <double> approx = run_experiment(vers);
            exp[i] = approx[2] / approx[1];
        }
        count_average(vers - start, exp);
    }
}


vector <double> Tester::run_experiment(int vertices_count) const {
    DotGenerator doter(0, 0, 1000, 1000, vertices_count);
    const vector<coord> &field = doter.getField();
    Graph graph(field);
    double mst_app = mst_solution(graph), optimal = bruteforce_solution(graph, mst_app), flow = flow_solution(graph);
    vector <double> approximations;
    approximations.emplace_back(mst_app);
    approximations.emplace_back(optimal);
    approximations.emplace_back(flow);
    return approximations;
}

double Tester::flow_solution(Graph& graph) const {
    double answer = 0, current = 0;
    for (unsigned i = 1; i < graph.size(); i++) {
        Graph flow_way = graph.build_flow_way(0, i);
        current = graph.count_way(flow_way.walk());
        if(current < answer)
            answer = current;
    }
    return answer;
}

double Tester::mst_solution(Graph& graph) const{
    Graph mst = graph.buildMST();
    return graph.count_way(mst.walk());
}

double Tester::bruteforce_solution(Graph& graph, double border) const{
    vector<bool> way(graph.size(), true);
    int size = 1;
    double processing = 0;
    graph.optimal_solution(0, processing, border, way, size);
    return border;
}

void Tester::count_average(int number, vector <double> &exp) {
    double avrg = 0, evasion = 0;
    for(double i : exp)
        avrg += i;

    avrg /= static_cast<double>(exp.size());

    for(double i : exp) {
        double difference = i - avrg;
        evasion += difference * difference;
    }
    evasion = sqrt(evasion) / static_cast<double>(exp.size());
    average_evasion[number] = evasion;
    average[number] = avrg;
}

const vector<double>& Tester::average_statistics() const {
    return average;
}

const vector<double>& Tester::average_evasion_statistics() const {
    return average_evasion;
}
