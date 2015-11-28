#include <QDebug>
#include <QProcess>
#include <QString>
#include <configuration.h>
#include <systemcalls.h>

QString createPatch(QString filename1, QString filename2)
{
    QProcess process;
    QString outputName = patchName(filename1, filename2);
    QStringList args = QStringList() << diffArgs << filename1 << filename2;
    process.setStandardOutputFile(outputName);

    qDebug() << diffCommand << args << outputName;

    process.start(diffCommand, args);
    return outputName;
}

QString patchName(QString filename1, QString filename2)
{
    return filename1 + filename2 + ".patch";
}

void applyPatch(QString patchName, QString outputName)
{
    QProcess process;
    QStringList args = QStringList() << "-i" << patchName << "-o" << outputName;
    qDebug() << patchCommand << args;
    process.start(patchCommand, args);
}

void createArchive(QString archiveName, QString fileNames)
{
    QProcess process;
    QStringList args = QStringList() << compressArgs << archiveName << fileNames;
    qDebug() << compressCommand << args;
    process.start(compressCommand, args);
}

void extractArchive(QString archiveName, QString location)
{
    QProcess process;
    QStringList args = QStringList() << decompressArgs << archiveName << "-d" << location;
    qDebug() << decompressCommand << args;
    process.start(decompressCommand, args);
}
