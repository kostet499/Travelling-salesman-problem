//
// Created by Toreno on 16.04.2018.
//

#include "tester.h"

Tester::Tester(int start, int end, int experiments) {
    srand(time(NULL));
    end++;
    vertices = end - start;
    average.resize(vertices);
    average_evasion.resize(vertices);

    for(int vers = start; vers < end; vers++) {
        vector <double> exp(experiments);
        for(int i = 0; i < experiments; i++) {
            DotGenerator doter(0, 0, 1000, 1000, vers);
            vector<coord> field = doter.getField();
            Graph graph(field);
            Graph mst = graph.buildMST();
            double heur = graph.count_way(mst.walk());

            vector<bool> way(graph.size(), true);
            int size = 1;
            double optimal = heur, processing = 0;
            graph.optimal_solution(0, processing, optimal, way, size);
            exp[i] = heur / optimal;
            //cout << heur << " " << optimal << " " << heur / optimal << endl;
        }
        count_average(vers - start, exp);
    }
}

void Tester::count_average(int number, vector <double> &exp) {
    double avrg = 0, evasion = 0;
    for(int i = 0; i < exp.size(); i++)
        avrg += exp[i];
    avrg /= static_cast<double>(exp.size());

    for(int i = 0; i < exp.size(); i++) {
        double difference = exp[i] - avrg;
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
