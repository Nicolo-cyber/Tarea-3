#ifndef GRAPH_H
#define GRAPH_H

#include <iostream>
#include <vector>
#include <climits>
#include <fstream>
#include <QFile>
#include <QFileInfo>
#include <QDebug>
#include <sstream>
#include <stdexcept>

namespace camino_corto {

class GraphBase {
protected:
    int V;  // Número de vértices
    std::vector<std::vector<int>> adjMatrix;  // Matriz de adyacencia para el grafo

public:
    GraphBase(int vertices);  // Constructor
    virtual ~GraphBase();  // Destructor

    virtual void addEdge(int src, int dest, int weight) = 0;  // Método puro
    virtual void display() = 0;  // Método virtual puro para mostrar el grafo

    // Declaración de la función como puramente virtual (sin implementación aquí)
    virtual void printShortestPath(int start, int end, const std::vector<int>& parent, std::ofstream &output) = 0;

    // Sobrecarga de operadores
    friend std::ostream& operator<<(std::ostream& os, const GraphBase& graph);
    std::vector<int>& operator[](int index);
};

class Graph : public GraphBase {
public:
    Graph(int vertices);
    ~Graph();

    void addEdge(int src, int dest, int weight) override;
    void loadGraphFromFile(const std::string &filename);
    void dijkstra(int start, int end, const std::string &outputFile);  // Algoritmo de Dijkstra
    void printShortestPath(int start, int end, const std::vector<int>& parent, std::ofstream &output) override;
    void display() override;
};

}  // namespace camino_corto

#endif
