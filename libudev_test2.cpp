#include <libudev.h>
#include <sys/stat.h>
#include <stdio.h>
#include <string.h>

int main() {
    struct udev *ud = udev_new();
    struct stat statbuf;
    if (stat("/dev/sda", &statbuf) != 0) { perror("stat"); return 1; }
    struct udev_device *dev = udev_device_new_from_devnum(ud, 'b', statbuf.st_rdev);
    const char *serial = udev_device_get_property_value(dev, "ID_SERIAL");
    printf("Serial: %s\n", serial);
    udev_device_unref(dev);
    udev_unref(ud);
    return 0;
}
