#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDirModel>
#include <QTreeView>
#include <QDebug>
#include <QTreeWidgetItem>


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

void MainWindow::addFile()
{
        //QTreeView tree = ui->treeView;
    QStringList list;
    list.append("test");
    list.append("test2");
    list.append("test3");
    list.append("test4");
    QTreeWidgetItem *test = new QTreeWidgetItem(list);
ui->treeWidget->addTopLevelItem(test);
   /* ui->treeView->setModel(new QDirModel());//&model);

    //ui->treeView->setRootIndex(model.index(QDir::homePath()));
    qDebug() << QDir::homePath();
    //ui->treeView->setColumnHidden( 1, true );
    ui->treeView->setColumnHidden( 2, true );
    ui->treeView->setColumnHidden( 3, true );

    ui->treeView->setWindowTitle("hello");//QObject::tr("Dir View:")+QDir::homePath());
    ui->treeView->resize(640, 480);
    ui->treeView->show();*/
}
