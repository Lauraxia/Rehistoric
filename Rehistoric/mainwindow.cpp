#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDirModel>
#include <QTreeView>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);




}

MainWindow::~MainWindow()
{
    delete ui;
}

//void MainWindow::addFile()
//{
//    QDirModel model;
//        //QTreeView tree = ui->treeView;

//    ui->treeView->setModel(&model);

//    ui->treeView->setRootIndex(model.index(QDir::homePath()));
//    ui->treeView->setColumnHidden( 1, true );
//    ui->treeView->setColumnHidden( 2, true );
//    ui->treeView->setColumnHidden( 3, true );

//    ui->treeView->setWindowTitle(QObject::tr("Dir View:")+QDir::homePath());
//    ui->treeView->resize(640, 480);
//    ui->treeView->show();
//}
