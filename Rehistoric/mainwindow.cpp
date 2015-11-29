#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDirModel>
#include <QTreeView>
#include <QDebug>
#include <QTreeWidgetItem>
#include <QDateTime>
#include<QObject>



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

void MainWindow::addFile(QString name, QString size, QDateTime dateCreated, QDateTime dateModified)
{
        //QTreeView tree = ui->treeView;
    QStringList list;
    list.append(name);
    list.append(size);
    list.append(dateCreated.toString());
    list.append(dateModified.toString());


//    list.append("test");
//    list.append("test2");
//    list.append("test3");
//    list.append("test4");
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

void MainWindow::on_extractButton_clicked()
{
    emit extractButton(getSelected());//ui->treeWidget->selectedItems());
    //connect(extractButton, SIGNAL(clicked()),main, SLOT(extract(getSelected())));
}
void MainWindow::on_addButton_clicked()
{
    emit addButton(getSelected());
    //connect(addButton, SIGNAL(clicked()),main, SLOT(add()))
}
void MainWindow::on_extractAllButton_clicked()
{
    emit extractAllButton(getSelectedQString());
   // connect(extractAllButton, SIGNAL(clicked()), main, SLOT(extractAll(getSelected())));
}
void MainWindow::on_removedButton_clicked()
{
    emit removeButton(getSelected());
}

QString MainWindow::getSelectedQString()
{
    QList<QTreeWidgetItem *> itemList;
    QString selected;
    itemList = this->ui->treeWidget->selectedItems();
    foreach(QTreeWidgetItem *item, itemList)
    {
       //get filename for each selected item
       selected += item->text(0);
       //selectedList.append(str);
    }
    return selected;
}

QStringList MainWindow::getSelected()
{
    QList<QTreeWidgetItem *> itemList;
    QStringList selectedList;
    itemList = this->ui->treeWidget->selectedItems();
    foreach(QTreeWidgetItem *item, itemList)
    {
       //get filename for each selected item
       QString str = item->text(0);
       selectedList.append(str);
    }
    return selectedList;//ui->treeWidget->currentItem()->text(ui->treeWidget->currentColumn());//test;




}





