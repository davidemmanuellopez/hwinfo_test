#include <iostream>
#include "udev.h"
#include <string>

std::string get_disk_serial(const std::string& device = "sda") {
    struct udev *udev;
    struct udev_enumerate *enumerate;
    struct udev_list_entry *devices, *dev_list_entry;
    struct udev_device *dev;
    std::string serial = "";

    udev = udev_new();
    if (!udev) {
        return "Error: No se pudo crear contexto udev";
    }

    enumerate = udev_enumerate_new(udev);
    udev_enumerate_add_match_subsystem(enumerate, "block");
    udev_enumerate_add_match_property(enumerate, "DEVTYPE", "disk");
    udev_enumerate_scan_devices(enumerate);

    devices = udev_enumerate_get_list_entry(enumerate);
    udev_list_entry_foreach(dev_list_entry, devices) {
        const char *path = udev_list_entry_get_name(dev_list_entry);
        dev = udev_device_new_from_syspath(udev, path);

        const char *devnode = udev_device_get_devnode(dev);
        const char *dev_serial = udev_device_get_property_value(dev, "ID_SERIAL_SHORT");
        std::cout << dev_serial << std::endl;

        if (devnode && dev_serial) {
            std::string dev_str(devnode);
            if (dev_str.find(device) != std::string::npos) {
                serial = dev_serial;
                udev_device_unref(dev);
                break;
            }
        }
        udev_device_unref(dev);
    }

    udev_enumerate_unref(enumerate);
    udev_unref(udev);

    return serial;
}

int main() {
    std::string serial = get_disk_serial("sda");
    std::cout << "Serial del disco: " << serial << std::endl;
    return 0;
}
