#ifndef FILEIO_H
#define FILEIO_H

#include <stddef.h>
#include "firmware_versions.h"

#define VERSION_PATH "flash0:/vsh/etc/version.txt"
#define BACKUP_PATH "flash1:/vsh/version.txt.backup"
#define BUFFER_SIZE  (16 * 1024)

int initFlash(const char *flash, int mode);
int readFile(const char *file, char *buffer);
int writeFile(const char *file, const char *data, int size);
int copyFile(const char *src, const char *dst);
int deleteFile(const char *file);
void makeVersionTxt(char *buffer, size_t bufsize, const FirmwareVersion *fw);

#endif