/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.2.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QTreeWidget>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralWidget;
    QLabel *label;
    QTreeWidget *treeWidget;
    QPushButton *extractButton;
    QPushButton *extractAllButton;
    QPushButton *addButon;
    QPushButton *removeButton;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QStringLiteral("MainWindow"));
        MainWindow->resize(400, 300);
        centralWidget = new QWidget(MainWindow);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        label = new QLabel(centralWidget);
        label->setObjectName(QStringLiteral("label"));
        label->setGeometry(QRect(130, 80, 57, 15));
        treeWidget = new QTreeWidget(centralWidget);
        treeWidget->setObjectName(QStringLiteral("treeWidget"));
        treeWidget->setGeometry(QRect(10, 0, 371, 192));
        extractButton = new QPushButton(centralWidget);
        extractButton->setObjectName(QStringLiteral("extractButton"));
        extractButton->setGeometry(QRect(20, 200, 80, 23));
        extractAllButton = new QPushButton(centralWidget);
        extractAllButton->setObjectName(QStringLiteral("extractAllButton"));
        extractAllButton->setGeometry(QRect(110, 200, 80, 23));
        addButon = new QPushButton(centralWidget);
        addButon->setObjectName(QStringLiteral("addButon"));
        addButon->setGeometry(QRect(200, 200, 80, 23));
        removeButton = new QPushButton(centralWidget);
        removeButton->setObjectName(QStringLiteral("removeButton"));
        removeButton->setGeometry(QRect(290, 200, 80, 23));
        MainWindow->setCentralWidget(centralWidget);
        mainToolBar = new QToolBar(MainWindow);
        mainToolBar->setObjectName(QStringLiteral("mainToolBar"));
        MainWindow->addToolBar(Qt::TopToolBarArea, mainToolBar);
        statusBar = new QStatusBar(MainWindow);
        statusBar->setObjectName(QStringLiteral("statusBar"));
        MainWindow->setStatusBar(statusBar);

        mainToolBar->addSeparator();

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "MainWindow", 0));
        label->setText(QApplication::translate("MainWindow", "TextLabel", 0));
        QTreeWidgetItem *___qtreewidgetitem = treeWidget->headerItem();
        ___qtreewidgetitem->setText(3, QApplication::translate("MainWindow", "Date Modified", 0));
        ___qtreewidgetitem->setText(2, QApplication::translate("MainWindow", "Date Created", 0));
        ___qtreewidgetitem->setText(1, QApplication::translate("MainWindow", "Size", 0));
        ___qtreewidgetitem->setText(0, QApplication::translate("MainWindow", "Filename", 0));
        extractButton->setText(QApplication::translate("MainWindow", "Extract", 0));
        extractAllButton->setText(QApplication::translate("MainWindow", "Extract All", 0));
        addButon->setText(QApplication::translate("MainWindow", "Add", 0));
        removeButton->setText(QApplication::translate("MainWindow", "Remove", 0));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
