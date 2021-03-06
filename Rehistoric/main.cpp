#include "mainwindow.h"
#include <QApplication>
#include <QDebug>
#include <configuration.h>
#include <systemcalls.h>
#include <QDir>
#include <QDateTime>
#include<QInputDialog>


int create(QString *files, int numFiles);
int extract(QString *files, int numFiles);
int extractSpecific(QString archive, QString file);
void extract2(QStringList selected);
void extractAll(QString file);
void remove(QString archive, QString *files, int numFiles);
void listArchive(QString archiveName, MainWindow *w);

void add(QString archive, QString file);
QString findNextFile(QString currentFileName, QStringList dirList);
int view(QString file, MainWindow *w);
QString archiveName;

QString getArchiveDestination(QString file);
//MainWindow *mainW;

int main(int argc, char *argv[])
{


    QApplication a(argc, argv);
    MainWindow w;

    for (int j=0; j<argc; j++)
    {
    qDebug() << argv[j];
    }

    if (argc == 1) // no arg, only prog name
    {
        qDebug() << "What are you doing?";

        //w.show();
        return 0;
    }
    else if (argc == 2)
    {
        //only 1 arg, so it must be the .hist file, which should be viewed:
        QString file = argv[1];

        archiveName = file;

        w.show();
        //QObject::connect(w, SIGNAL(extractButton()), this, SLOT(extract()));
        QObject::connect(&w, &MainWindow::extractButton, extract2);
        //QObject::connect(w, &QPushButton::clicked, someFunction);
        //QObject::connect(&w,&MainWindow::addButton, add); //grab the needed stuff for adding
        QObject::connect(&w, &MainWindow::extractAllButton,extractAll);//same as extract but for all the files
        view(file, &w);
        qDebug() << "2 params!";
        return a.exec();
    }
    else
    {
        w.show();
        //1st arg = action, 2nd+ = file paths
        QString mode = argv[1];
        qDebug() << mode << " " << argc;
        int numFiles = argc-2;
        QString files[numFiles];
        QString file = argv[3];
        QString archive = argv[2];
        //read all input filenames
        for (int i=2; i<argc; i++)
        {
            files[i-2] = argv[i];
            //MainWindow w;
            //w.show();
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
            add(archive, file);
        }
        else if (mode == "extract")
        {
            //extract(files, numFiles);
            extractSpecific(files[0], files[1]); //archive, file to extract
        }
        else if (mode == "extractAll")
        {
            extractAll(files[0]);
        }
        else if (mode == "remove")
        {
            remove(files[0], files, numFiles);
        }

    }

    w.show();
    //mainW = &w;
    //w.addFile();

    qDebug() << "shown window";
    return a.exec();
}
int create(QString *files, int numFiles)
{
    qDebug() << "creating";
    //putting files into a map with date as key
//    QMap<QDateTime,QString> datemap;
//    for (int i = 0; i < numFiles; i++)
//    {
//        QFile oldFile(files[i]);
//        QFileInfo fileInfo;
//        fileInfo.setFile(oldFile);
//        QDateTime modified = fileInfo.lastModified();
//        datemap.insert(modified, files[i]);
//        qDebug() << "inserted " << files[i] << "into datemap";
//    }
    // create patches
    QStringList patches = QStringList();
//    QMap<QDateTime, QString>::iterator i;
//    QString prevFile;
//    for (i = datemap.begin(); i != datemap.end(); i++)
//    {
//        qDebug() << i.key().toString("yyyy.M.d.h:m") << i.value();
//        if (!prevFile.isEmpty())
//        {
//            QString patchname = createPatch(prevFile, i.value());
//            qDebug() << patchname;
//            patches << patchname;
//        }
//        prevFile = i.value();
//    }
    for (int i = 1; i < numFiles; i++)
    {
        QString patchname = createPatch(files[i-1], files[i]);
        qDebug() << patchname;
        patches << patchname;
    }
    QStringList filesToArchive = patches;
    filesToArchive << files[0];
    qDebug() << filesToArchive;
    //and add to archive:


    //QString archive = createArchive("hist", filesToArchive);
    QString archive = createArchive(files[0]+".hist", filesToArchive);
    qDebug() << archive;


    //then remove patches (temp files) now that we're done
    deletePatches(patches);
    //QDir().rename(files[0] + ".zip" , files[0] + ".hist");
    for (int i = 0; i < numFiles-1; i++)
    {
        qDebug() << files[i];
        QDir().remove(files[i]);
    }
    return 0;
}
int extract(QString *files, int numFiles)
{
    QString archive = "hist.zip";
    QString destination = tmpDir + dirSep + archive;
    if (!QDir(destination).exists())
    {
        QDir().mkdir(destination);
    }
    extractArchive(files[0], destination);

    //check all extracted files for the file to be patched
    QStringList dirList = QDir(destination).entryList();
    //removing . and .. entries in dir listing
    dirList.removeAt(dirList.indexOf(".."));
    dirList.removeAt(dirList.indexOf("."));

    QString origFile; // finding file that patches are applied to
    for (int i = 0; i < dirList.length(); i++)
    {
        QString tmp = dirList[i];
        qDebug() << tmp;
        if (!tmp.endsWith(".patch")) //all other files assumed to be patches
        {
            origFile = tmp;
        }
    }
    qDebug() << origFile;
    //apply all patches in correct order
    QString fileName = origFile;
    QString oldWorkDir = QDir().currentPath();
    QStringList filesToDelete = QStringList();
    QDir().setCurrent(destination);
    bool allCreated;
    do
    {
        QString patch = findNextFile(fileName, dirList);
        qDebug() << "Found:" << patch << "containing" << fileName;
        QString tmp = patch;
        tmp.remove(fileName).remove(".patch");
        qDebug() << "filename " << fileName;
        applyPatch(patch, tmp);
        filesToDelete << tmp;
        fileName = tmp;
        qDebug() << "findNext " << findNextFile(fileName,dirList);
        allCreated = true;
        for (int i = 1; i < numFiles; i++)
        {
            qDebug() << "allCreated: " << files[i] << " " << !QFile::exists(files[i]);
            if (!QFile::exists(files[i]))
            {
                allCreated = false;
                break;
            }
        }

    } while (!findNextFile(fileName,dirList).isEmpty() && !allCreated);

    for (int i = 1; i < numFiles; i++)
    {
        qDebug() << "copying back " << files[i];
        if (QFile::exists(files[i]))
        {
            QDir().rename(files[i], oldWorkDir + dirSep + files[i]);
        }
    }

    QDir().setCurrent(oldWorkDir);
    QDir(destination).removeRecursively();

    return 0;
}
int extractSpecific(QString archive, QString file)
{
    QString destination = tmpDir + dirSep + archive;
    if (!QDir(destination).exists())
    {
        QDir().mkdir(destination);
    }
    else
    {
        QDir(destination).removeRecursively(); //TODO this is awful, but program will hang if we don't
    }
    extractArchive(archive.split(dirSep).last(), destination);

    //check all extracted files for the file to be patched
    QStringList dirList = QDir(destination).entryList();
    //removing . and .. entries in dir listing
    dirList.removeAt(dirList.indexOf(".."));
    dirList.removeAt(dirList.indexOf("."));

    QString origFile; // finding file that patches are applied to
    for (int i = 0; i < dirList.length(); i++)
    {
        QString tmp = dirList[i];
        qDebug() << tmp;
        if (!tmp.endsWith(".patch")) //all other files assumed to be patches
        {
            origFile = tmp;
        }
    }
    qDebug() << origFile;
    //apply all patches in correct order
    QString fileName = origFile;
    QString oldWorkDir = QDir().currentPath();
    QStringList filesToDelete = QStringList();
    QDir().setCurrent(destination);
    //bool allCreated;
    QString patch = findNextFile(fileName, dirList);
    while (!patch.isEmpty())
    {
        qDebug() << "Found:" << patch << "containing" << fileName;
        QString tmp = patch;
        tmp.remove(fileName).remove(".patch");
        qDebug() << "filename " << fileName;
        applyPatch(patch, tmp);
        filesToDelete << tmp;
        fileName = tmp;
        qDebug() << "findNext " << findNextFile(fileName,dirList);

patch = findNextFile(fileName, dirList);
    } // && !allCreated);

        qDebug() << "copying back " << file << oldWorkDir << dirSep << file;
        qDebug() << "looking in" << tmpDir + dirSep + archive + dirSep + file;
        if (QFile::exists(tmpDir + dirSep + archive + dirSep + file))
        {
            qDebug() << "exists";
            if (QFile::exists(oldWorkDir + dirSep + file))
            {
                qDebug() << "file to be extracted exists already, removing previous copy";
                QDir().remove(oldWorkDir + dirSep + file);
            }
            QDir().rename(tmpDir + dirSep + archive + dirSep + file, oldWorkDir + dirSep + file);
        }

    QDir().setCurrent(oldWorkDir);
    QDir(destination).removeRecursively();

    return 0;
}


void extract2(QStringList selected)
{
    qDebug() << selected;// QString::number(i);//+ mainW->getSelected();

    //w.getSelected();
    //w->ui->treeWidget->selectedItems().
    //return 0;
    //TODO: not a good way to do this, but we'll assume only 1 can be selected (true, for now...)
    extractSpecific(archiveName, selected[0]); //selected.length());
}

QString getArchiveDestination(QString file)
{
    return tmpDir + dirSep + file;
}

void extractAll(QString file)
{

    QString justName = file.split(dirSep).last();

    QString destination = getArchiveDestination(justName);
    qDebug() << "extractAll to: " << destination;

    if (!QDir(destination).exists())
    {
        QDir().mkdir(destination);
    }
    else
    {
        qDebug() << " better clean up!";
        //TODO FIX: kind of an awful hack, but preemptively delete any existing contents to avoid conflict:
        QDir(destination).removeRecursively();
    }
    extractArchive(file, destination);

    //check all extracted files for the file to be patched
    QStringList dirList = QDir(destination).entryList();
    //removing . and .. entries in dir listing
    dirList.removeAt(dirList.indexOf(".."));
    dirList.removeAt(dirList.indexOf("."));

    QString origFile; // finding file that patches are applied to
    for (int i = 0; i < dirList.length(); i++)
    {
        QString tmp = dirList[i];
        qDebug() << tmp;
        if (!tmp.endsWith(".patch"))
        {
            origFile = tmp; // there must be one
        }
    }
    qDebug() << origFile;
    //apply all patches in correct orderhttps://en.wikipedia.org/wiki/Id
    QString fileName = origFile;
    QString oldWorkDir = QDir().currentPath();
    QStringList actualFilesToCopy = QStringList(); //the files the user wants
    QDir().setCurrent(destination);

        QString patch = findNextFile(fileName, dirList);
        qDebug() << "Found:" << patch << "containing" << fileName;
        QString tmp = patch;
        tmp.remove(fileName).remove(".patch");
        qDebug() << "filename " << fileName;
        applyPatch(patch, tmp);
        actualFilesToCopy << tmp;
        fileName = tmp;
        qDebug() << "findNext " << findNextFile(fileName,dirList);

    actualFilesToCopy << origFile;
    for (int i = 0; i < actualFilesToCopy.length(); i++)
    {
        if (QFile::exists(oldWorkDir + dirSep + actualFilesToCopy[i]))
        {
            qDebug() << "file " << actualFilesToCopy[i] << " to be extracted exists already, removing previous copy";
            QDir().remove(oldWorkDir + dirSep + actualFilesToCopy[i]);
        }
        QFile::copy(actualFilesToCopy[i], oldWorkDir + dirSep + actualFilesToCopy[i]);
    }
    QDir().setCurrent(oldWorkDir);

    //TODO FIX: we can't do this here, because sometimes we need to extractAll and then read the contents!
    //QDir(destination).removeRecursively();

    //return 0;// maybe void instead?
}

//clean it up a little
void add(QString archive, QString file)//mar
{
    //find the archive filename from the list
    //mario:don't need the followinng because we're getting the archive name from the args

    qDebug() << archive;
    //make subdir in tmpDir and extract archive to it
    QString destination = tmpDir + dirSep + archive; // temp dir to extract archive to
    qDebug() << destination;
    QDir().mkdir(destination);
    extractArchive(archive, destination);

    //check all extracted files for the file to be patched
    QStringList dirList = QDir(destination).entryList();
    //removing . and .. entries in dir listing
    dirList.removeAt(dirList.indexOf(".."));
    dirList.removeAt(dirList.indexOf("."));
    //list of patches
    QStringList patchList = dirList;//.filter(".patch");
    QString origFile = file;

    qDebug() << origFile;
    //apply all patches in correct order
    QString fileName = origFile;
    QString oldWorkDir = QDir().currentPath();
    QStringList filesToDelete = QStringList();
    QDir().setCurrent(destination);
    //do
    //{
        QString patch = findNextFile(fileName, dirList);
        qDebug() << "Found:" << patch << "containing" << fileName;
        QString tmp = patch;
        tmp.remove(fileName).remove(".patch");
        qDebug() << "filename " << fileName;
        applyPatch(patch, tmp);
        filesToDelete << tmp;
        fileName = tmp;
        //QDir().rename(patch, destination2 + dirSep + patch.split(dirSep).last());
        qDebug() << "findNext " << findNextFile(fileName,dirList);
    //} while (!findNextFile(fileName,dirList).isEmpty());

    qDebug() << "done patching, final file" << fileName;
    qDebug() << "current patchList: " << patchList;

    QString prevFile = fileName;

        if (!QFile::exists(destination + dirSep + file))
        {
                QString newFile = oldWorkDir + dirSep + file;
                QString patchname = createPatch(prevFile, newFile);
                prevFile = file;
                patchList << patchname;

        }

    qDebug() << patchList;

    QStringList filesToArchive = patchList;
    filesToArchive << origFile;
    qDebug() << filesToArchive;
    createArchive("hist", filesToArchive);
    QString destArchive = oldWorkDir + dirSep + "hist." + rehistoricArchiveExtension;
    qDebug() << destArchive;
    if (QFile::exists(destArchive))
    {
       QFile::remove(destArchive);
    }
    QDir().rename("hist."+rehistoricArchiveExtension, destArchive);
    QDir(destination).removeRecursively();
    QDir().setCurrent(oldWorkDir);
    deletePatches(filesToDelete << origFile);
    qDebug() << filesToDelete;
    //return 0;
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

int view(QString file, MainWindow *w)
{
    //extract info from hist...

    //then add each file's info:
    //w->addFile(QString("test"), QString("test2"), QDateTime::currentDateTime(), QDateTime::currentDateTime());
    listArchive(file,w);
    return 0;
}
void listArchive(QString archiveName, MainWindow *w)
{
//    QProcess process;
//    QStringList args = QStringList();
//    args << "-l" << archiveName;
//    qDebug() << "unzip" << args;
//    process.start("unzip", args, QIODevice::ReadWrite);
//    process.waitForFinished();
//    QString result(process.readAllStandardOutput());

//    QStringList lines = result.split("\n");
//    for (int i = 3; i < lines.length()-3; i++)
//    {
//        qDebug() << lines[i].split(QRegExp("\\s+"));

//    }
    extractAll(archiveName);

    //this should be where the output is, so list from here...
    QString destination = getArchiveDestination(archiveName.split(dirSep).last());

    qDebug() << "done extracting";
//    QString destination = tmpDir + dirSep + archiveName;
    QStringList dirList = QDir(destination).entryList();

    qDebug() << "dirlist is: " << dirList;
    //removing . and .. entries in dir listing
    dirList.removeAt(dirList.indexOf(".."));
    dirList.removeAt(dirList.indexOf("."));


    for (int i = 0; i < dirList.length(); i++)
    {
        QString tmp = dirList[i];
        qDebug() << tmp;

        QFileInfo tmpinfo = QFileInfo(tmp);
        qDebug() << tmpinfo.lastModified() << tmpinfo.size();

        //we don't want to add this if it's a patch and not an actual file:
        if (tmp.contains(".patch"))
        {
            //dirList.removeAt(i);
            qDebug() << "found patch at " << i << tmp;
        }
        else
        {
            //add to our file list:
            w->addFile(tmp,(QString::number(tmpinfo.size()) + " B"),tmpinfo.lastModified());
            //TODO: do we need to track which things we've added? Will this mess up actions based on selection index later?
        }
    }
    QDir(destination).removeRecursively();
}

void remove(QString archive, QString *files, int numFiles) {
    qDebug() << archive;
    //make subdir in tmpDir and extract archive to it
    QString destination = getArchiveDestination(archive); // temp dir to extract archive to
    qDebug() << destination;
    QDir().mkdir(destination);
    extractArchive(archive, destination);

    //check all extracted files for the file to be patched
    QStringList dirList = QDir(destination).entryList();
    //removing . and .. entries in dir listing
    int indexdotdot = dirList.indexOf("..");
    dirList.removeAt(indexdotdot);
    dirList.removeAt(dirList.indexOf("."));
    //list of patches
    QStringList patchList = dirList;//.filter(".patch");
    QString origFile;
    for (int i = 0; i < dirList.length(); i++)
    {
        QString tmp = dirList[i];
        qDebug() << tmp;
        if (!tmp.endsWith(".patch"))
        {
            origFile = tmp;
        }
    }
    qDebug() << origFile;
    //apply all patches in correct order
    QString fileName = origFile;
    QString oldWorkDir = QDir().currentPath();
    QStringList filesToDelete = QStringList();
    QDir().setCurrent(destination);
    do
    {
        QString patch = findNextFile(fileName, dirList);
        qDebug() << "Found:" << patch << "containing" << fileName;
        QString tmp = patch;
        tmp.remove(fileName).remove(".patch");
        qDebug() << "filename " << fileName;
        applyPatch(patch, tmp);
        filesToDelete << tmp;
        fileName = tmp;
        //QDir().rename(patch, destination2 + dirSep + patch.split(dirSep).last());

        //was fileremoveName(?!)
        qDebug() << "findNext " << findNextFile(fileName,dirList);
    } while (!findNextFile(fileName,dirList).isEmpty());

    for (int i = 0; i < numFiles; i++)
    {
        QDir(destination).remove(files[i]);
        qDebug() << "removed " << files[i];
    }
    QStringList dirList2 = QDir(destination).entryList();
    //removing . and .. entries in dir listing
    dirList.removeAt(dirList2.indexOf(".."));
    dirList.removeAt(dirList2.indexOf("."));
    qDebug() << dirList2;
    QString files2[dirList2.length()];
    for(int i = 0; i < dirList2.length(); i++)
    {
        files2[i] = dirList2[i];
    }

    create(files2, dirList2.size());

    QString destArchive = oldWorkDir + dirSep + "hist." + rehistoricArchiveExtension;
    qDebug() << destArchive;
    if (QFile::exists(destArchive))
    {
       QFile::remove(destArchive);
    }
    QDir().rename("hist."+rehistoricArchiveExtension, destArchive);
    QDir().setCurrent(oldWorkDir);
    QDir(destination).removeRecursively();

}
