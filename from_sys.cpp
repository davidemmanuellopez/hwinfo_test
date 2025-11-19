#include <string>
#include <iostream>
#include <vector>
#include <fstream>

std::string get_serial_from_sys() {
    // Probar diferentes rutas posibles
    std::vector<std::string> paths = {
        "/sys/block/sda/device/serial",
        "/sys/block/vda/device/serial",
        "/sys/block/nvme0n1/device/serial"
    };

    for (const auto& path : paths) {
        std::ifstream file(path);
        if (file.is_open()) {
            std::string serial;
            std::getline(file, serial);
            file.close();
            if (!serial.empty()) {
                return serial;
            }
        }
    }
    return "No encontrado";
}

int main()
{
 std::cout << get_serial_from_sys() << std::endl;
}
