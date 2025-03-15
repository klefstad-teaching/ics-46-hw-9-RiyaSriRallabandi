#include <iostream>
#include "dijkstras.h"

int main() {
    Graph G;
    string input_file = "small.txt";
    file_to_graph(input_file, G);
    int source_vertex = 0;
    vector<int> previous_vertices;
    vector<int> distances = dijkstra_shortest_path(G, source, previous_vertices;)
    for (int destination = 0; destination < G.numVertices; destination++) {
        vector<int> path = extract_shortest_path(distances, previous, destination);
        print_path(path, distances[destination]); 
    } return 0;
}
