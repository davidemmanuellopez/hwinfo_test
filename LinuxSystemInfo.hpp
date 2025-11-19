#ifndef LINUX_SYSTEM_INFO
#define LINUX_SYSTEM_INFO
#include <systemd/sd-device.h>
#include "SystemInfo.h"

class LinuxSystemInfo : public SystemInfo
{
public:
    LinuxSystemInfo(): SystemInfo()
    {

    };
private:
    std::string get_smbios_uuid() override;

};

std::string LinuxSystemInfo::get_smbios_uuid()
{
    // NEED root!
    sd_device *dev = NULL;
    const char *uuid = NULL;
    int r;

    r = sd_device_new_from_syspath(&dev, "/sys/devices/virtual/dmi/id");
    if (r < 0) {
        fprintf(stderr, "Error al crear el dispositivo: %d\n", r);
        return std::string("not obtained");
    }

    r = sd_device_get_sysattr_value(dev, "product_uuid", &uuid);
    if (r < 0) {
        fprintf(stderr, "Error al obtener el atributo: %d\n", r);
        sd_device_unref(dev);
        return std::string("not obtained");
    }

    printf("UUID del BIOS: %s\n", uuid);
    return std::string(uuid);

    sd_device_unref(dev);
}

using PlatformSystemInfo = LinuxSystemInfo;
#endif
