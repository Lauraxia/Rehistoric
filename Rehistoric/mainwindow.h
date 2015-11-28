#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    void addFile(QString name, QString size, QDateTime dateModified, QDateTime dateCreated);

    QStringList getSelected();
    void remove();

private slots:
    void on_extractButton_clicked();
    void on_addButton_clicked();
    void on_extractAllButton_clicked();
    void on_removedButton_clicked();


signals:
    int extractButton(QStringList selected);
    int removeButton(QStringList selected);
    int extractAllButton(QStringList selected);
    int addButton(QStringList selected);


private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
