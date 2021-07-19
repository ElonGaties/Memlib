#include "main.h"

/*int main(int argc, char* argv[]) {
    if (getuid() != 0) {
        system(("sudo -S "+std::string(argv[0])).c_str());
        exit(0);
    }
    Process proc("linux_64_client");

    auto base = proc.GetModule("linux_64_client");

    auto ammo = proc.DMAaddr(base+0x12E328, {0x390, 0x28, 0x0});
    
    std::cout << std::dec << proc.read<int>(ammo) << '\n';
    proc.write(ammo, 500);
    std::cout << std::dec << proc.read<int>(ammo) << '\n';
    return 0;
}*/

int main() {
    //Process proc("RobloxPlayerBeta.exe");
    Process proc("linux_64_client");

    uintptr_t y_pos = 0x11A4CA94;

    // std::cout << "X: " << std::dec << proc.read<float>(y_pos) << '\n';
    // std::cout << "Y: " << std::dec << proc.read<float>(y_pos+0x4) << '\n';
    // std::cout << "Z: " << std::dec << proc.read<float>(y_pos+0x8) << '\n';

    return 0;
}