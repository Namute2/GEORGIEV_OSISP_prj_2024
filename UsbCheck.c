#include <stdio.h>
#include <dirent.h>
#include <string.h>

#define USB_SYSFS_PATH "/sys/bus/usb/devices/"

void check_usb_state() {
    DIR* dir;
    struct dirent* entry;

    dir = opendir(USB_SYSFS_PATH);
    if (dir == NULL) {
        printf("Failed to open USB sysfs directory\n");
        return;
    }

    printf("USB devices found:\n");

    while ((entry = readdir(dir)) != NULL) {
        if (entry->d_type == DT_LNK) {
            FILE* file;
            char filepath[256];
            char desc[256];

            snprintf(filepath, sizeof(filepath), "%s%s", USB_SYSFS_PATH, entry->d_name);
            file = fopen(filepath, "r");
            if (file) {
                if (fgets(desc, sizeof(desc), file) != NULL) {
                    if (strstr(desc, "USB") != NULL) {
                        printf("Device: %s", desc);
                    }
                }
                fclose(file);
            }
        }
    }

    closedir(dir);
}

int main() {
    check_usb_state();
    return 0;
}