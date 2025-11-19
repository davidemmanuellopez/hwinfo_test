#include "SystemInfo.h"

json SystemInfo::get_info()
{
    // Using (raw) string literals and json::parse
    json json_;

    // MainBoard section
    json_["mainboard"]["vendor"] = main_board.vendor();
    json_["mainboard"]["name"] = main_board.name();
    json_["mainboard"]["smbios_uuid"] = get_smbios_uuid();

    // OS section
    json_["OS"]["name"] = os.name();
    json_["OS"]["version"] = os.version();
    json_["OS"]["kernel"] = os.kernel();
    json_["OS"]["architecture"] = os.is32bit() ? "32 bit" : "64 bit";

    //CPU section
    unsigned int cpu_i = 0;

    for (const auto& cpu : cpus) {
        auto str_id = std::to_string(cpu_i);
        json_["CPUs"][str_id]["vendor"] = cpu.vendor();
        json_["CPUs"][str_id]["model"] = cpu.modelName();
        cpu_i++;

    }

    //Disk section
    unsigned int disk_i = 0;
    for (const auto& disk : disks) {
        auto str_id = std::to_string(disk_i);
        json_["Disks"][str_id]["vendor"] = disk.vendor();
        json_["Disks"][str_id]["model"] = disk.model();
        disk_i++;

    }

    return json_;
}


