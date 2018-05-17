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
            exp[i] = approx[2] / approx[0];
        }
        count_average(vers - start, exp);
    }
}


vector <double> Tester::run_experiment(int vertices_count) const {
    DotGenerator doter(0, 0, 1000, 1000, vertices_count);
    const vector<coord> &field = doter.getField();
    Graph graph(field);
    double mst_app = mst_solution(graph);
    double optimal = bruteforce_solution(graph, mst_app);
    double angle_app = angle_solution(graph);
    //double flow = flow_solution(graph);
    vector <double> approximations;
    approximations.emplace_back(optimal);
    approximations.emplace_back(mst_app);
    approximations.emplace_back(angle_app);
    //approximations.emplace_back(flow);
    return approximations;
}

double Tester::flow_solution(Graph& graph) const {
    double answer = 1000000000, current = 0;
    for (unsigned i = 1; i < graph.size(); i++) {
        Graph flow_way = graph.build_flow_way(0, i);
        current = flow_way.count_way(flow_way.walk());
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
    way[0] = false;
    graph.optimal_solution(0, processing, border, way, size);
    return border;
}

double Tester::angle_solution(Graph &graph) const {
    Graph angle = graph.build_angle_way();
    return graph.count_way(angle.walk());
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
