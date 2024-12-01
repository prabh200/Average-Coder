#include "graph.h"

Graph::Graph() {
};

Graph::~Graph() {
    return;
};

void Graph::print() {
    std::string LINEBREAK = "----- ----- -----\n";

    std::cout << LINEBREAK;
    std::cout << "--- GRAPH REPRESENTED DATA ---\n";
    for (auto it = adj_list.begin(); it != adj_list.end(); it++) {
        std::cout << std::setw(24) << std::left << it -> first << ": ";
        for (auto mini_it = it -> second.begin(); mini_it != it -> second.end(); mini_it++) {
            std::cout << *mini_it << ", ";
        }
        std::cout << "\n";
    }
    std::cout << LINEBREAK;
}

void Graph::add_vertex(std::string node) {
    std::set<std::string> empty_set;
    adj_list.insert(std::make_pair(node, empty_set));
};


void Graph::remove_vertex(std::string node) {
    auto it = adj_list.find(node);
    if (it != adj_list.end()) {
        adj_list.erase(it);
        for (auto& list: adj_list) {
            list.second.erase(node);
        }
        return;
    }
    std::cout << "Vertex Removal failed. Vertex not found.\n";
};

void Graph::add_edge(std::string n1, std::string n2) {
    auto it1 = adj_list.find(n1);
    auto it2 = adj_list.find(n2);
    if (it1 != adj_list.end() && it2 != adj_list.end()) {
        adj_list[n1].insert(n2);
        adj_list[n2].insert(n1);
        return;
    }
    std::cout << "Edge Insertion failed. Node(s) not found.\n";
}

void Graph::remove_edge(std::string n1, std::string n2) {
    auto it1 = adj_list.find(n1);
    auto it2 = adj_list.find(n2);
    if (it1 != adj_list.end() && it2 != adj_list.end()) {
        adj_list[n1].erase(n2);
        adj_list[n2].erase(n1);
        return;
    }
    std::cout << "Edge Removal failed. Node(s) not found.\n";
};

bool Graph::has_edge(std::string n1, std::string n2) {
    auto it1 = adj_list.find(n1);
    if (it1 != adj_list.end()) {
        if (it1 -> second.find(n2) != it1 -> second.end()) {
            return true;
        }
    }
    return false;
};

Graph importgraph(std::string filename) {
    Graph g; // Create a graph
    std::ifstream infile(filename); // Open the file for reading

    std::string s, x = "", y = "", v1 = "", v2 = "";
    float n;

    bool in_steps = false;

    while (infile >> s) {
        if (!in_steps) {
            if (s == "\"steps\"") {
                in_steps = true;
            }
        } else {
            if (s == "\"lat\"") {
                infile >> s; // For colon
                infile >> s; // The latitude is the second item after "lat".
                y = std::to_string(std::stof(s));
                infile >> s; // For "lng"
                infile >> s; // For colon
                infile >> s; // The latitude is the second item after "lng".
                x = std::to_string(std::stof(s));
                v1 = y + "_" + x;
                g.add_vertex(v1);
                if (v2 != "") {
                    g.add_edge(v2, v1);
                }
                v2 = v1;
                v1 = "";
            }
        }
    }

    g.print();
    
    return g; // Return the populated Graph
};