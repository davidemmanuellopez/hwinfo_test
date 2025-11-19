#ifndef WINDOWS_SYSTEM_INFO
#define WINDOWS_SYSTEM_INFO
#include "SystemInfo.hpp"

class WindowsSystemInfo: public SystemInfo
{
public:
    WindowsSystemInfo(): SystemInfo(){};
private:
    std::string get_smbios_uuid() override;
};


std::string WindowsSystemInfo::get_smbios_uuid()
{
    return std::string("Dummy");
}

using PlatformSystemInfo = WindowsSystemInfo;
#endif
