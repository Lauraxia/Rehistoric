#ifndef SYSTEMCALLS_H
#define SYSTEMCALLS_H

QString createPatch(QString filename1, QString filename2);

QString patchName(QString filename1, QString filename2);

void applyPatch(QString patchName, QString outputName);

void createArchive(QString archiveName, QString fileNames);

void extractArchive(QString archiveName, QString location);

#endif // SYSTEMCALLS_H
