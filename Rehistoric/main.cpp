#include "mainwindow.h"
#include <QApplication>
#include <QDebug>
#include <configuration.h>

int create(QString *files, int numFiles);
int extract(QString *files);
int add(QString *files, int numFiles);
int view(QString file);

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    if (argc == 1) // no arg, only prog name
    {
        qDebug() << "What are you doing?";
    }
    else if (argc == 2)
    {
        //only 1 arg, so it must be the .hist file, which should be viewed:
        QString file = argv[1];
        view(file);
    }
    else
    {
        //1st arg = action, 2nd+ = file paths
        QString mode = argv[1];
        qDebug() << mode << " " << argc;
        int numFiles = argc-2;
        QString files[numFiles];

        //read all input filenames
        for (int i=2; i<argc; i++)
        {
            files[i-2] = argv[i];
            qDebug() << files[i-2];
        }

        //carry out action, based on 1st argument
        if (mode == "create")
        {
            create(files, numFiles);
        }
        else if (mode == "add")
        {
            add(files, numFiles);
        }
        else if (mode == "extract")
        {
            extract(files);
        }

        MainWindow w;
        w.show();
    }


    return a.exec();
}
int create(QString *files, int numFiles)
{
    qDebug() << "creating";

    return 0;
}

int extract(QString *files)
{

    return 0;
}

int add(QString *files, int numFiles)
{

    return 0;
}
int view(QString file)
{

    return 0;
}

