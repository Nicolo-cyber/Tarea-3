/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.15.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpinBox>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTextEdit>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralwidget;
    QVBoxLayout *verticalLayout;
    QPushButton *loadButton;
    QHBoxLayout *horizontalLayout;
    QLabel *label;
    QSpinBox *startSpinBox;
    QLabel *label_2;
    QSpinBox *endSpinBox;
    QPushButton *calculateButton;
    QTextEdit *resultTextEdit;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QString::fromUtf8("MainWindow"));
        MainWindow->resize(800, 600);
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
        verticalLayout = new QVBoxLayout(centralwidget);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        loadButton = new QPushButton(centralwidget);
        loadButton->setObjectName(QString::fromUtf8("loadButton"));

        verticalLayout->addWidget(loadButton);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        label = new QLabel(centralwidget);
        label->setObjectName(QString::fromUtf8("label"));

        horizontalLayout->addWidget(label);

        startSpinBox = new QSpinBox(centralwidget);
        startSpinBox->setObjectName(QString::fromUtf8("startSpinBox"));
        startSpinBox->setMaximum(5);

        horizontalLayout->addWidget(startSpinBox);

        label_2 = new QLabel(centralwidget);
        label_2->setObjectName(QString::fromUtf8("label_2"));

        horizontalLayout->addWidget(label_2);

        endSpinBox = new QSpinBox(centralwidget);
        endSpinBox->setObjectName(QString::fromUtf8("endSpinBox"));
        endSpinBox->setMaximum(5);

        horizontalLayout->addWidget(endSpinBox);


        verticalLayout->addLayout(horizontalLayout);

        calculateButton = new QPushButton(centralwidget);
        calculateButton->setObjectName(QString::fromUtf8("calculateButton"));

        verticalLayout->addWidget(calculateButton);

        resultTextEdit = new QTextEdit(centralwidget);
        resultTextEdit->setObjectName(QString::fromUtf8("resultTextEdit"));
        resultTextEdit->setReadOnly(true);

        verticalLayout->addWidget(resultTextEdit);

        MainWindow->setCentralWidget(centralwidget);
        statusbar = new QStatusBar(MainWindow);
        statusbar->setObjectName(QString::fromUtf8("statusbar"));
        MainWindow->setStatusBar(statusbar);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "Camino M\303\241s Corto", nullptr));
        loadButton->setText(QCoreApplication::translate("MainWindow", "Cargar Grafo", nullptr));
        label->setText(QCoreApplication::translate("MainWindow", "Inicio:", nullptr));
        label_2->setText(QCoreApplication::translate("MainWindow", "Fin:", nullptr));
        calculateButton->setText(QCoreApplication::translate("MainWindow", "Calcular Camino M\303\241s Corto", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
