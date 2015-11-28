#include <QDebug>
#include <QProcess>
#include <QString>
#include <configuration.h>
#include <systemcalls.h>

QString createPatch(QString filename1, QString filename2)
{
    QProcess process;
    QString outputName = patchName(filename1, filename2);
    QStringList args = QStringList();
    if (diffArgs.length() > 0)
    {
        args << diffArgs;
    }
    args << filename1 << filename2;
    process.setStandardOutputFile(outputName);

    qDebug() << diffCommand << args << outputName;

    process.start(diffCommand, args);
    process.waitForFinished();
    return outputName;
}

QString patchName(QString filename1, QString filename2)
{
    return filename1.split("/").last() + filename2.split("/").last() + ".patch";
}

void applyPatch(QString patchName, QString outputName)
{
    QProcess process;
    QStringList args = QStringList() << "-i" << patchName << "-o" << outputName;
    qDebug() << patchCommand << args;
    process.start(patchCommand, args);
    process.waitForFinished();
}

QString createArchive(QString archiveName, QStringList fileNames)
{
    QProcess process;
    QStringList args = QStringList();
    if (compressArgs.length() > 0)
    {
        args << compressArgs;
    }
    args << archiveName << fileNames;
    qDebug() << compressCommand << args;
    process.start(compressCommand, args);
    process.waitForFinished();
    return archiveName;
}

void extractArchive(QString archiveName, QString location)
{
    QProcess process;
    QStringList args = QStringList();
    qDebug() << decompressArgs.length();
    if (decompressArgs.length() > 0)
    {
        args << decompressArgs;
    }
    args << archiveName << "-d" << location;
    qDebug() << decompressCommand << args;
    //process.setStandardErrorFile("whatever");
    process.start(decompressCommand, args);
    process.waitForFinished();
}
