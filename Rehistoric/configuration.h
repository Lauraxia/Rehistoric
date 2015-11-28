#ifndef CONFIGURATION_H
#define CONFIGURATION_H

const QString rehistoricArchiveExtension = "zip";

const QString diffCommand = "diff";
static QString const diffArgs = "-u";

static QString const patchCommand = "patch";
static QString const patchArgs = "";

static QString const compressCommand = "zip";
static QString const compressArgs = "-j";

static QString const decompressCommand = "unzip";
static QString const decompressArgs = "";

static QString const rmCommand = "rm";

static QString const tmpDir = "/tmp";
#endif
