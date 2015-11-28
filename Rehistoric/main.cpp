#include "mainwindow.h"
#include <QApplication>
#include <QDebug>
#include <configuration.h>
#include <systemcalls.h>
#include <QDir>

int create(QString *files, int numFiles);
int extract(QString *files);
int add(QString *files, int numFiles);
int view(QString file);

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    for (int j=0; j<argc; j++)
    {
    qDebug() << argv[j];
    }

    if (argc == 1) // no arg, only prog name
    {
        qDebug() << "What are you doing?";
        MainWindow w;
        w.show();
        //return 0;
    }
    else if (argc == 2)
    {
        //only 1 arg, so it must be the .hist file, which should be viewed:
        QString file = argv[1];
        view(file);
        MainWindow w;
        w.show();
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
            MainWindow w;
            w.show();
            qDebug() << files[i-2];
        }

        //carry out action, based on 1st argument
        if (mode == "create")
        {
            create(files, numFiles);
            //return 0;
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
    // create patches
    QStringList patches = QStringList();
    for (int i = 1; i < numFiles; i++)
    {
        QString patchname = createPatch(files[i-1], files[i]);
        qDebug() << patchname;
        patches << patchname;
    }

    QString archive = createArchive("hist", patches << files[0]);
    qDebug() << archive;
    //return 0;
}

int extract(QString *files)
{

    return 0;
}

int add(QString *files, int numFiles)
{
    QString archive;
    for (int i = 0; i < numFiles; i++)
    {
        if (files[i].endsWith(rehistoricArchiveExtension))
        {
            archive = files[i];
            break;
        }
    }
    QString destination = tmpDir + "/" + archive;
    QDir().mkdir(destination);
    extractArchive(archive, destination);
    //use QDirIterator
    //match with startswith filename of included file
    //patch it, match on resulting and so on until last file
    //then diff with new file(s), save only diffs and original file and compress
    return 0;
}
int view(QString file)
{

    return 0;
}

