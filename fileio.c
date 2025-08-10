#include <pspkernel.h>
#include <pspiofilemgr.h>
#include <string.h>
#include <stdio.h>
#include "fileio.h"

// --- Mount/Unmount flash0 or flash1 for read or write operations ---
int initFlash(const char *flash, int mode) {
    int ret = sceIoUnassign(flash);
    int tries = 0;
    while (ret < 0 && tries < 10) {
        sceKernelDelayThread(500000);
        ret = sceIoUnassign(flash);
        tries++;
    }
    if (ret < 0) return -1;
    char lflash[32], flashfat[32];
    if (strcmp(flash, "flash0:") == 0) {
        strcpy(lflash, "lflash0:0,0");
        strcpy(flashfat, "flashfat0:");
    } else {
        strcpy(lflash, "lflash0:0,1");
        strcpy(flashfat, "flashfat1:");
    }
    ret = sceIoAssign(flash, lflash, flashfat, mode, NULL, 0);
    if (ret < 0) return -2;
    return 0;
}

// --- Basic file operations ---
int readFile(const char *file, char *buffer) {
    SceUID fd = sceIoOpen(file, PSP_O_RDONLY, 0777);
    if (fd < 0) return -1;
    int bytes = sceIoRead(fd, buffer, BUFFER_SIZE - 1);
    if (bytes < 0) {
        sceIoClose(fd);
        return -2;
    }
    sceIoClose(fd);
    buffer[bytes] = '\0';
    return bytes;
}

int writeFile(const char *file, const char *data, int size) {
    SceUID fd = sceIoOpen(file, PSP_O_WRONLY | PSP_O_CREAT | PSP_O_TRUNC, 0777);
    if (fd < 0) return -1;
    int bytes = sceIoWrite(fd, data, size);
    sceIoClose(fd);
    return bytes;
}

int copyFile(const char *src, const char *dst) {
    char buffer[BUFFER_SIZE];
    int len = readFile(src, buffer);
    if (len <= 0) return -1;
    int res = writeFile(dst, buffer, len);
    if (res < 0) return -2;
    return 0;
}

int deleteFile(const char *file) {
    SceUID fd = sceIoOpen(file, PSP_O_RDONLY, 0777);
    if (fd < 0) return -1;
    sceIoClose(fd);
    return sceIoRemove(file);
}

// --- Craft valid version.txt using firmare info from firmware_versions.h ---
void makeVersionTxt(char *buffer, size_t bufsize, const FirmwareVersion *fw) {
    snprintf(buffer, bufsize,
        "release:%s:\n"
        "build:%s\n"
        "system:%s\n"
        "vsh:%s\n"
        "%s%s\n",
        fw->release, fw->build, fw->system, fw->vsh,
        strlen(fw->target) ? "target:" : "",
        fw->target
    );
}