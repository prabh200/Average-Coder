#ifndef GRAPH_H
#define GRAPH_H

#include <string>
#include <fstream>
#include <set>
#include <map>
#include <iostream>
#include <iomanip>
#include <string>

class Graph {
    private:
        std::map<std::string, std::set<std::string>> adj_list;
    public:
        Graph();
        ~Graph();

        void print();

        void add_vertex(std::string);               // self-explanatory
        void remove_vertex(std::string);            // if remove non-existent node, print error message
        void add_edge(std::string, std::string);    // if parameter includes non-existent node(s), print error message
        void remove_edge(std::string, std::string); // if parameter includes non-existent node(s), print error message
        bool has_edge(std::string, std::string);    // self-explanatory
};

Graph importgraph(std::string);

#endif
