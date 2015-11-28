#include "mainwindow.h"
#include <QApplication>
#include <QDebug>
#include <configuration.h>
#include <systemcalls.h>
#include <QDir>

int create(QString *files, int numFiles);
int extract(QString *files);
int add(QString *files, int numFiles);
QString findNextFile(QString currentFileName, QStringList dirList);
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
    return 0;
}

int extract(QString *files)
{

    return 0;
}

int add(QString *files, int numFiles)
{
    //find the archive filename from the list
    QString archive;
    for (int i = 0; i < numFiles; i++)
    {
        if (files[i].endsWith(rehistoricArchiveExtension))
        {
            archive = files[i];
            break;
        }
    }
    qDebug() << archive;
    //make subdir in tmpDir and extract archive to it
    QString destination = tmpDir + dirSep + archive; // temp dir to extract archive to
    qDebug() << destination;
    QDir().mkdir(destination);
//    QString destination2 = destination + "new"; //temp dir for new archive
//    qDebug() << destination2;
//    QDir().mkdir(destination2);
    extractArchive(archive, destination);

    //check all extracted files for the file to be patched
    QStringList dirList = QDir(destination).entryList();
    //removing . and .. entries in dir listing
    int indexdotdot = dirList.indexOf("..");
    dirList.removeAt(indexdotdot);
    dirList.removeAt(dirList.indexOf("."));
    //list of patches
    QStringList patchList = dirList.filter("*.patch");
    QString fileName;
    for (int i = 0; i < dirList.length(); i++)
    {
        QString tmp = dirList[i];
        qDebug() << tmp;
        if (!tmp.endsWith(".patch"))
        {
            fileName = tmp;
        }
    }
    qDebug() << fileName;
    //apply all patches in correct order
    do
    {
        QString patch = findNextFile(fileName, dirList);
        qDebug() << "Found:" << patch << "containing" << fileName;
        QString tmp = patch;
        tmp.remove(fileName).remove(".patch");
        qDebug() << fileName;
        QDir().setCurrent(destination);
        applyPatch(patch, tmp);
        fileName = tmp;
        //QDir().rename(patch, destination2 + dirSep + patch.split(dirSep).last());
    } while (!findNextFile(fileName,dirList).isEmpty());


    //diff with new file(s), save only diffs and original file and compress
    return 0;
}
//find next patch file
QString findNextFile(QString currentFileName, QStringList dirList)
{
    qDebug() << currentFileName;
    for (int i = 0; i < dirList.length(); i++)
    {
        QString tmp = dirList[i];
        qDebug() << "Comparing:" << tmp << tmp.endsWith(".patch");
        if (tmp.startsWith(currentFileName) && tmp.endsWith(".patch"))
        {
            return tmp;
        }
    }
    return "";
}

int view(QString file)
{

    return 0;
}

