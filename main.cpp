#include "libmem/libmem.hpp"

int main(int argc, char* argv[]) {
    if (getuid() != 0) {
        system(("sudo -S "+std::string(argv[0])).c_str());
        exit(0);
    } // Pozm has the best ideas :trole:
  
    Process proc("linux_64_client");

    auto base = proc.GetModule("linux_64_client");

    auto ammo = proc.DMAaddr(base+0x12E328, {0x390, 0x28, 0x0});
    
    std::cout << std::dec << proc.read<int>(ammo) << '\n';
    proc.write(ammo, 500);
    std::cout << std::dec << proc.read<int>(ammo) << '\n';
    return 0;
}
