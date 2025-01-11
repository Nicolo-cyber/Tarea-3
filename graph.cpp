#include "graph.h"
#include <iostream>
#include <sstream>
#include <QDebug>
#include <QFileInfo>
#include <stdexcept>
namespace camino_corto {

GraphBase::GraphBase(int vertices) {
    try {
        qDebug() << "Iniciando constructor GraphBase";
        if (vertices <= 0) throw std::invalid_argument("Vértices inválidos");
        V = vertices;
        adjMatrix.resize(V, std::vector<int>(V, INT_MAX));
        qDebug() << "Matriz inicializada";
    } catch (const std::exception& e) {
        qDebug() << "Error en constructor:" << e.what();
        throw;
    }
}

GraphBase::~GraphBase() {}

Graph::Graph(int vertices) : GraphBase(vertices) {
    if (vertices <= 0) {
        throw std::invalid_argument("Número de vértices inválido");
    }
}

std::ostream& operator<<(std::ostream& os, const GraphBase& graph) {
    for (int i = 0; i < graph.V; ++i) {
        for (int j = 0; j < graph.V; ++j) {
            if (graph.adjMatrix[i][j] == INT_MAX) {
                os << "INF ";
            } else {

                os << graph.adjMatrix[i][j] << " ";
            }
        }
        os << std::endl;
    }
    return os;
}

std::vector<int>& GraphBase::operator[](int index) {
    return adjMatrix[index];
}

Graph::~Graph() {}

void Graph::addEdge(int src, int dest, int weight) {
    adjMatrix[src][dest] = weight;
}



void Graph::loadGraphFromFile(const std::string &filename) {
    try {
        qDebug() << "Iniciando carga";
        std::ifstream file(filename);
        std::string line;

        if (!file.is_open()) throw std::runtime_error("Error apertura archivo");

        while (getline(file, line)) {
            qDebug() << "Leído:" << QString::fromStdString(line);
            std::istringstream iss(line);
            int src, dest, weight;
            if (!(iss >> src >> dest >> weight)) throw std::runtime_error("Error formato");
            addEdge(src, dest, weight);
        }
    } catch (const std::exception& e) {
        qDebug() << "Error en carga:" << e.what();
        throw;
    }
}

void Graph::dijkstra(int start, int end, const std::string &outputFile) {
    if (start < 0 || start >= V || end < 0 || end >= V) {
        std::cerr << "Error: Nodo inicial o final fuera del rango permitido." << std::endl;
        return;
    }

    std::vector<int> dist(V, INT_MAX);  // Vector de distancias mínimas
    std::vector<int> parent(V, -1);     // Vector para rastrear el camino
    std::vector<bool> visited(V, false);  // Vector para marcar nodos visitados

    dist[start] = 0;

    for (int i = 0; i < V - 1; ++i) {
        int minDist = INT_MAX, u = -1;

        for (int j = 0; j < V; ++j) {
            if (!visited[j] && dist[j] < minDist) {
                minDist = dist[j];
                u = j;
            }
        }

        if (u == -1) break;  // No hay más nodos alcanzables

        visited[u] = true;

        for (int v = 0; v < V; ++v) {
            if (!visited[v] && adjMatrix[u][v] != INT_MAX && dist[u] + adjMatrix[u][v] < dist[v]) {
                dist[v] = dist[u] + adjMatrix[u][v];
                parent[v] = u;
            }
        }
    }

    std::ofstream output(outputFile);  // Abrir el archivo de salida
    if (!output.is_open()) {
        std::cerr << "Error: No se pudo abrir el archivo de salida " << outputFile << std::endl;
        return;
    }

    if (dist[end] == INT_MAX) {
        output << "No existe un camino desde " << start << " hasta " << end << ".\n";
    } else {
        output << "Camino mas corto desde " << start << " hasta " << end << ": ";
        printShortestPath(start, end, parent, output);
        output << "\nCosto total: " << dist[end] << "\n";
    }

    output.close();
}

void Graph::printShortestPath(int start, int end, const std::vector<int>& parent, std::ofstream &output) {
    if (end == -1) {
        output << "No path exists from " << start << " to " << end << "\n";
        return;
    }

    if (parent[end] == -1) {
        output << "No path exists from " << start << " to " << end << "\n";
        return;
    }

    printShortestPath(start, parent[end], parent, output);  // Recursivamente imprimir el camino
    output << end << " ";
}

void Graph::display() {
    std::cout << *this;  // Mostrar la matriz de adyacencia usando el operador << sobrecargado
}

}  // namespace camino_corto
