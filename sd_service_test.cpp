#include <systemd/sd-device.h>
#include <sys/stat.h>
#include <stdio.h>
#include <string.h>

int main() {
    sd_device *dev = NULL;
    struct stat statbuf;
    if (stat("/dev/sda", &statbuf) != 0) { perror("stat"); return 1; }
    if (sd_device_new_from_devnum(&dev, 'b', statbuf.st_rdev) < 0) { perror("sd_device_new"); return 1; }
    const char *serial;
    if (sd_device_get_property_value(dev, "ID_SERIAL", &serial) < 0) { perror("get_property"); sd_device_unref(dev); return 1; }
    printf("Serial: %s\n", serial);
    sd_device_unref(dev);


    sd_device *dev2 = NULL;
    const char *uuid = NULL;
    int r;

    r = sd_device_new_from_syspath(&dev2, "/sys/devices/virtual/dmi/id");
    if (r < 0) {
        fprintf(stderr, "Error al crear el dispositivo: %d\n", r);
        return 1;
    }

    r = sd_device_get_sysattr_value(dev2, "product_uuid", &uuid);
    if (r < 0) {
        fprintf(stderr, "Error al obtener el atributo: %d\n", r);
        sd_device_unref(dev);
        return 1;
    }

    printf("UUID del BIOS: %s\n", uuid);

    sd_device_unref(dev2);
    return 0;

}
