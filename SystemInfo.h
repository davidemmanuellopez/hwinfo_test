
#ifndef SYSTEM_INFO
#define SYSTEM_INFO

#include <fmt/format.h>
#include <fmt/ranges.h>
#include <hwinfo/hwinfo.h>
#include <hwinfo/utils/unit.h>

#include <cassert>
#include <vector>

#include <nlohmann/json.hpp>
#include <fstream>

// for convenience
using json = nlohmann::json;

using hwinfo::unit::bytes_to_MiB;

class SystemInfo
{
public:
    SystemInfo(): cpus(hwinfo::getAllCPUs()), disks(hwinfo::getAllDisks()){};
    json get_info();

private:
    hwinfo::MainBoard main_board;
    hwinfo::OS os;
    std::vector<hwinfo::CPU> cpus;
    std::vector<hwinfo::Disk> disks;
    virtual std::string get_smbios_uuid() = 0;
};
#endif
