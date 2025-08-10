#include <pspkernel.h>
#include <pspdebug.h>
#include <pspctrl.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <math.h>

#include "fileio.h"
#include "firmware_versions.h"

PSP_MODULE_INFO("Version.txt Switch & Repair", 0x800, 1, 0);
PSP_MAIN_THREAD_ATTR(THREAD_ATTR_USER | THREAD_ATTR_VFPU);

// --- Color macros ---
#define color(x) pspDebugScreenSetTextColor(x)
#define RED    0xff0000ff
#define BLUE   0xffff0000
#define GREEN  0xff00ff00
#define LGRAY  0xffd3d3d3
#define WHITE  0xffffffff
#define YELLOW 0xff00ffff
#define ORANGE 0xff007fff

#define printf pspDebugScreenPrintf

// --- Exit callback ---
int exit_callback(int arg1, int arg2, void *common) {
    sceKernelExitGame();
    return 0;
}
int callback_thread(SceSize args, void *argp) {
    int cbid = sceKernelCreateCallback("Exit Callback", exit_callback, NULL);
    sceKernelRegisterExitCallback(cbid);
    sceKernelSleepThreadCB();
    return 0;
}
int setup_callbacks(void) {
    int thid = sceKernelCreateThread("update_thread", callback_thread, 0x11, 0xFA0, 0, 0);
    if(thid >= 0)
        sceKernelStartThread(thid, 0, 0);
    return thid;
}

// --- Parse firmware hex string to dec ---
float parse_hex_to_version(unsigned int hex) {
    unsigned char major = (hex >> 24) & 0xFF;
    unsigned char minor = (hex >> 16) & 0xFF;
    unsigned char patch = (hex >> 8) & 0xFF;
    float version = major + ((minor * 10 + patch) / 100.0f);
    return version;
}

// --- Get Firmware Version as string ---
void printFirmwareVersion(char* buf, size_t buflen) {
    u32 fw = sceKernelDevkitVersion();
    float readablefw = parse_hex_to_version(fw);
    snprintf(buf, buflen, "%.2f", readablefw);
}

//  --- Waits for a fresh button press and returns which one ---
unsigned int getButton(void) {
    SceCtrlData pad;
    unsigned int old = 0;
    do {
        sceCtrlReadBufferPositive(&pad, 1);
        old = pad.Buttons;
        sceKernelDelayThread(50 * 1000);
    } while (old);
    do {
        sceCtrlReadBufferPositive(&pad, 1);
        if (pad.Buttons)
            return pad.Buttons;
        sceKernelDelayThread(50 * 1000);
    } while (1);
}

// --- Wait for user input to continue ---
void waitKey(void) {
    color(YELLOW);
    printf("\nPress any key to continue...\n");
    color(WHITE);
    getButton();
}

// --- Display System Firmware Version ---
void displaySystemFirmwareVersion(void) {
    char sysver[32];
    printFirmwareVersion(sysver, sizeof(sysver));
    color(YELLOW);
    printf("Detected firmware version: ");
    color(GREEN);
    printf("%s\n\n", sysver);
    color(WHITE);
}

// --- Confirmation dialog with optional info ---
int confirmDialog(const char *msg, const char *info) {
    pspDebugScreenClear();
    color(YELLOW);
    printf("%s\n", msg);
    color(WHITE);
    if (info && info[0]) {
        printf("%s\n", info);
    }
    printf("\n[X] Yes   [O] No\n\n");
    while (1) {
        unsigned int btn = getButton();
        if (btn & PSP_CTRL_CROSS) return 1;
        if (btn & PSP_CTRL_CIRCLE) return 0;
    }
}


// --- Repair version.txt by matching version.txt with detected firmware version using printFirmwareVersion()  ---
void repairVersionTxt(int* flashInited) {
    char sysver[32], txtbuf[BUFFER_SIZE], info[1024];
    printFirmwareVersion(sysver, sizeof(sysver));

    u32 fw_hex = sceKernelDevkitVersion();
    float fw_dec = parse_hex_to_version(fw_hex);

    int found = 0;
    for (int i = 0; i < NUM_FIRMWARES; ++i) {
        float entry_dec = atof(firmware_versions[i].name);
        if (fabsf(entry_dec - fw_dec) < 0.005f) {
            makeVersionTxt(txtbuf, sizeof(txtbuf), &firmware_versions[i]);
            found = 1;
            break;
        }
    }
    if (!found) {
        snprintf(txtbuf, sizeof(txtbuf), "// No matching version.txt template found!\n// Detected firmware: %s\n", sysver);
    }

    snprintf(info, sizeof(info),
        "\nDetected firmware version: ");
    
    pspDebugScreenClear();
    color(ORANGE); 
    printf("Repair version.txt by matching the detected firmware version.\n\n"); 
    color(WHITE);
    printf("Detected firmware version: ");
    color(GREEN);
    printf("%s\n", sysver);
    color(YELLOW);
    printf("\nRepair will write firmware ");
    color(GREEN);
    printf("%s", sysver);
    color(YELLOW); 
    printf(" version.txt.\n");
    color(LGRAY);
    printf("\n--- Preview version.txt ---\n");
    color(WHITE);
    color(WHITE);
    printf("%s\n", txtbuf);

    color(YELLOW);
    printf("\nProceed with repair?\n");
    color(WHITE);
    printf("\n[X] Yes   [O] No\n");

    unsigned int btn;
    while (1) {
        btn = getButton();
        if (btn & PSP_CTRL_CROSS) break;
        if (btn & PSP_CTRL_CIRCLE) return;
    }

    // Automatic backup 
    color(YELLOW);
    printf("\nBacking up current version.txt...\n");
    color(WHITE);
    int backup_result = copyFile(VERSION_PATH, BACKUP_PATH);
    if (backup_result == 0) {
        color(GREEN); printf("Backup successful.\n"); color(WHITE);
    } else {
        color(RED); printf("Backup failed! (file may not exist or write error)\n"); color(WHITE);
    }

    if (!*flashInited) {
        if (initFlash("flash0:", 0) == 0)
            *flashInited = 1;
        else {
            color(RED); printf("Failed to reassign flash0!\n"); color(WHITE);
            waitKey();
            return;
        }
    }
    if (writeFile(VERSION_PATH, txtbuf, strlen(txtbuf)) > 0)
        { color(GREEN); printf("Written successfully.\n"); color(WHITE); }
    else
        { color(RED); printf("Write failed!\n"); color(WHITE); }
    waitKey();
}

// --- Display current and backup version.txt ---
void displayVersionTxts() {
    char curr[BUFFER_SIZE], backup[BUFFER_SIZE];
    int cbytes = readFile(VERSION_PATH, curr);
    int bbytes = readFile(BACKUP_PATH, backup);

    color(YELLOW);
    printf("Current version.txt:\n");
    color(LGRAY);
    if (cbytes > 0) {
        curr[255] = 0;
        printf("%s\n", curr);
    } else { color(RED); printf("Not found or error.\n"); color(WHITE); }

    color(YELLOW);
    printf("\nBackup version.txt:\n");
    color(LGRAY);
    if (bbytes > 0) {
        backup[255] = 0;
        printf("%s\n", backup);
    } else { color(RED); printf("Not found or error.\n"); color(WHITE); }

    color(WHITE);
}

// --- Main menu ---
int menu() {
    const char *items[] = {
        "Switch version.txt",
        "Repair version.txt",
        "Backup current version.txt",
        "Restore backup",
        "Delete backup",
        "Exit"
    };
    int sel = 0, n = 6;
    while (1) {
        pspDebugScreenClear();
        color(ORANGE);
        printf("=== Version.txt Switch & Repair ===\n\n");
        color(WHITE);
        displaySystemFirmwareVersion();
        displayVersionTxts();
        color(ORANGE);
        printf("\n--- Main Menu ---\n");
        color(WHITE);
        for (int i = 0; i < n; ++i) {
            if (i == sel) { color(GREEN); printf("> %s\n", items[i]); color(WHITE); }
            else printf("  %s\n", items[i]);
        }
        color(YELLOW);
        printf("\nUP/DOWN: Move   X: Select   START: Exit\n");
        color(WHITE);

        color(BLUE);
        printf("\n\n- Programmed by Wyped - v1.0 - 2025 -\n");
        color(WHITE);

        unsigned int btn = getButton();
        if (btn & PSP_CTRL_UP)    { sel = (sel-1+n)%n; }
        else if (btn & PSP_CTRL_DOWN) { sel = (sel+1)%n; }
        else if (btn & PSP_CTRL_CROSS) return sel;
        else if (btn & PSP_CTRL_START) return n - 1;
    }
}

// --- Select version.txt menu ---
int selectFirmware() {
    int s = 0;
    while (1) {
        pspDebugScreenClear();
        color(ORANGE);
        printf("Select firmware series:\n\n");
        color(WHITE);
        for (int i = 0; i < NUM_SERIES; ++i) {
            if (i == s) { color(GREEN); printf("> %s\n", firmware_series[i].series_name); color(WHITE); }
            else printf("  %s\n", firmware_series[i].series_name);
        }
        color(YELLOW);
        printf("\nUP/DOWN: Move   X: Select   O: Cancel\n");
        color(WHITE);
        unsigned int btn = getButton();
        if (btn & PSP_CTRL_UP)    { s = (s-1+NUM_SERIES)%NUM_SERIES; }
        else if (btn & PSP_CTRL_DOWN) { s = (s+1)%NUM_SERIES; }
        else if (btn & PSP_CTRL_CROSS) break;
        else if (btn & PSP_CTRL_CIRCLE) return -1;
    }
    int start = firmware_series[s].start, end = firmware_series[s].end;
    int sel = start;
    while (1) {
        pspDebugScreenClear();
        color(ORANGE);
        printf("Firmware: %s\n\n", firmware_series[s].series_name);
        color(WHITE);
        for (int i = start; i <= end; ++i) {
            if (i == sel) { color(GREEN); printf("> %s\n", firmware_versions[i].name); color(WHITE); }
            else printf("  %s\n", firmware_versions[i].name);
        }
        color(YELLOW);
        printf("\nUP/DOWN: Move   X: Select   O: Cancel\n");
        color(LGRAY);
        printf("\n--- Preview version.txt ---\n");
        color(WHITE);
        char preview[512];
        makeVersionTxt(preview, sizeof(preview), &firmware_versions[sel]);
        printf("%s\n", preview);

        unsigned int btn = getButton();
        if (btn & PSP_CTRL_UP)   { if (--sel < start) sel = end; }
        else if (btn & PSP_CTRL_DOWN) { if (++sel > end) sel = start; }
        else if (btn & PSP_CTRL_CROSS) return sel;
        else if (btn & PSP_CTRL_CIRCLE) return -1;
    }
}

// --- Switch version.txt with selected version ---
void switchVersionTxt(int *flashInited) {
    int sel = selectFirmware();
    if (sel == -1) return;
    pspDebugScreenClear();
    color(GREEN); printf("Selected: %s\n", firmware_versions[sel].name); color(WHITE);
    char fwbuf[BUFFER_SIZE];
    makeVersionTxt(fwbuf, sizeof(fwbuf), &firmware_versions[sel]);
    color(LGRAY); printf("\nNew version.txt:\n"); color(WHITE); printf("%s\n", fwbuf);
    if (!confirmDialog("Backup and overwrite version.txt?", NULL)) return;
    pspDebugScreenClear();
    // Automatic backup
    color(YELLOW); printf("Backing up current version.txt...\n"); color(WHITE);
    if (copyFile(VERSION_PATH, BACKUP_PATH) == 0)
        { color(GREEN); printf("Backup successful.\n"); }
    else
        { color(RED); printf("Backup failed!\n"); }
    color(YELLOW); printf("Writing new version.txt...\n"); color(WHITE);
    if (!*flashInited) {
        if (initFlash("flash0:", 0) == 0)
            *flashInited = 1;
        else
            { color(RED); printf("Failed to reassign flash0!\n"); color(WHITE); }
    }
    if (writeFile(VERSION_PATH, fwbuf, strlen(fwbuf)) > 0)
        { color(GREEN); printf("Written successfully.\n"); }
    else
        { color(RED); printf("Write failed!\n"); }
    color(WHITE); waitKey();
}

// --- Backup version.txt from flash0 to flash1 ---
void backupVersionTxt() {
    pspDebugScreenClear();
    if (!confirmDialog("Backup current version.txt to flash1?", NULL)) return;
    color(YELLOW); printf("Backing up current version.txt...\n"); color(WHITE);
    if (copyFile(VERSION_PATH, BACKUP_PATH) == 0)
        { color(GREEN); printf("Backup successful.\n"); }
    else
        { color(RED); printf("Backup failed!\n"); }
    color(WHITE); waitKey();
}

// --- Restore version.txt backup from flash1 to flash0 ---
void restoreVersionTxtBackup(int *flashInited) {
    pspDebugScreenClear();
    if (!confirmDialog("Restore version.txt backup from flash1 to flash0?", NULL)) return;
    color(YELLOW); printf("Restoring version.txt backup...\n"); color(WHITE);
    char buf[BUFFER_SIZE];
    int len = readFile(BACKUP_PATH, buf);
    if (len > 0) {
        if (!*flashInited) {
            if (initFlash("flash0:", 0) == 0)
                *flashInited = 1;
            else
                { color(RED); printf("Failed to reassign flash0!\n"); color(WHITE); }
        }
        if (writeFile(VERSION_PATH, buf, len) > 0)
            { color(GREEN); printf("Restore successful.\n"); }
        else
            { color(RED); printf("Restore failed!\n"); }
    } else {
        color(RED); printf("No backup found!\n");
    }
    color(WHITE); waitKey();
}

// --- Delete flash1 version.txt backup ---
void deleteVersionTxtBackup() {
    pspDebugScreenClear();
    if (!confirmDialog("Delete version.txt backup in flash1?", NULL)) return;
    color(YELLOW); printf("Deleting backup...\n"); color(WHITE);
    if (deleteFile(BACKUP_PATH) == 0)
        { color(GREEN); printf("Backup deleted.\n"); }
    else
        { color(RED); printf("Delete failed!\n"); }
    color(WHITE); waitKey();
}

// --- Main function ---
int main() {
    setup_callbacks();
    pspDebugScreenInit();
    sceCtrlSetSamplingCycle(0);
    sceCtrlSetSamplingMode(PSP_CTRL_MODE_ANALOG);
    int flashInited = 0;
    while (1) {
        int action = menu();
        switch (action) {
            case 0:
                switchVersionTxt(&flashInited);
                break;
            case 1:
                repairVersionTxt(&flashInited);
                break;
            case 2:
                backupVersionTxt();
                break;
            case 3:
                restoreVersionTxtBackup(&flashInited);
                break;
            case 4:
                deleteVersionTxtBackup();
                break;
            case 5:
                goto exit;
        }
    }
exit:
    pspDebugScreenClear();
    color(BLUE); printf("Exiting...\n"); color(WHITE);
    sceKernelExitGame();
    return 0;
}