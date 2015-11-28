#ifndef SYSTEMCALLS_H
#define SYSTEMCALLS_H

QString createPatch(QString filename1, QString filename2);

QString patchName(QString filename1, QString filename2);

void applyPatch(QString patchName, QString outputName);

QString createArchive(QString archiveName, QStringList fileNames);

void extractArchive(QString archiveName, QString location);

int deletePatches(QStringList patches);

#endif // SYSTEMCALLS_H
