#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include <QMessageBox>
#include <QTextStream>
#include <QFile>


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    , graph(nullptr)
{
    ui->setupUi(this);
    setupTable();
}

MainWindow::~MainWindow()
{
    delete ui;
    delete graph;
}

void MainWindow::setupTable()
{
    tableWidget = new QTableWidget(6, 6, this);
    tableWidget->setFixedHeight(300);
    ui->verticalLayout->insertWidget(1, tableWidget);

    for(int i = 0; i < 6; i++) {
        for(int j = 0; j < 6; j++) {
            tableWidget->setItem(i, j, new QTableWidgetItem(" "));
        }
    }
    tableWidget->resizeColumnsToContents();
}

void MainWindow::updateTable()
{
    if(!graph) return;
    for(int i = 0; i < 6; i++) {
        for(int j = 0; j < 6; j++) {
            int value = (*graph)[i][j];
            tableWidget->setItem(i, j,
                                 new QTableWidgetItem(value == INT_MAX ? " " : QString::number(value)));
        }
    }
    tableWidget->resizeColumnsToContents();
}

void MainWindow::on_loadButton_clicked()
{
    QString filename = QFileDialog::getOpenFileName(this, "Abrir archivo");
    if(filename.isEmpty()) return;

    try {
        delete graph;
        graph = new camino_corto::Graph(6);

        QFile file(filename);
        if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
            throw std::runtime_error("Error al abrir archivo");
        }

        QTextStream in(&file);
        while (!in.atEnd()) {
            QString line = in.readLine();
            QStringList parts = line.split(' ');
            if (parts.size() == 3) {
                graph->addEdge(parts[0].toInt(), parts[1].toInt(), parts[2].toInt());
            }
        }
        updateTable();
    } catch(std::exception& e) {
        QMessageBox::critical(this, "Error", e.what());
    }
}

void MainWindow::on_calculateButton_clicked()
{
    try {
        if (!graph) {
            QMessageBox::warning(this, "Error", "Carga un grafo primero");
            return;
        }

        int start = ui->startSpinBox->value();
        int end = ui->endSpinBox->value();

        std::ostringstream output;
        std::vector<int> dist(6, INT_MAX);
        std::vector<int> parent(6, -1);
        std::vector<bool> visited(6, false);

        // Implementar Dijkstra
        dist[start] = 0;
        for (int i = 0; i < 6-1; i++) {
            int u = -1;
            int minDist = INT_MAX;
            for (int j = 0; j < 6; j++) {
                if (!visited[j] && dist[j] < minDist) {
                    minDist = dist[j];
                    u = j;
                }
            }

            if (u == -1) break;
            visited[u] = true;

            for (int v = 0; v < 6; v++) {
                if (!visited[v] && (*graph)[u][v] != INT_MAX &&
                    dist[u] + (*graph)[u][v] < dist[v]) {
                    dist[v] = dist[u] + (*graph)[u][v];
                    parent[v] = u;
                }
            }
        }

        // Construir resultado
        QString result;
        if (dist[end] == INT_MAX) {
            result = QString("No existe camino de %1 a %2").arg(start).arg(end);
        } else {
            result = QString("Camino más corto de %1 a %2:\n").arg(start).arg(end);
            // Reconstruir camino
            std::vector<int> path;
            for (int v = end; v != -1; v = parent[v]) {
                path.push_back(v);
            }
            for (int i = path.size()-1; i >= 0; i--) {
                result += QString::number(path[i]) + " ";
            }
            result += QString("\nDistancia total: %1").arg(dist[end]);
        }

        ui->resultTextEdit->setText(result);

    } catch (const std::exception& e) {
        QMessageBox::critical(this, "Error", e.what());
    }
}
