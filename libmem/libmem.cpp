#include "libmem.hpp"

Process::Process(std::string name) {
    pid_t pid = -1;

    // Open the /proc directory
    DIR *dp = opendir("/proc");
    if (dp != NULL)
    {
        // Enumerate all entries in directory until process found
        struct dirent *dirp;
        while (pid < 0 && (dirp = readdir(dp)))
        {
            // Skip non-numeric entries
            int id = atoi(dirp->d_name);
            if (id > 0)
            {
                // Read contents of virtual /proc/{pid}/cmdline file
                std::string cmdPath = std::string("/proc/") + dirp->d_name + "/cmdline";
                std::ifstream cmdFile(cmdPath.c_str());
                std::string cmdLine;
                getline(cmdFile, cmdLine);
                if (!cmdLine.empty())
                {
                    // Keep first cmdline item which contains the program path
                    size_t pos = cmdLine.find('\0');
                    if (pos != std::string::npos)
                        cmdLine = cmdLine.substr(0, pos);
                    // Keep program name only, removing the path
                    pos = cmdLine.rfind('/');
                    if (pos != std::string::npos)
                        cmdLine = cmdLine.substr(pos + 1);
                    // Check for windows :trole:
                    if (cmdLine.find('\\') != std::string::npos) {
                        pos = cmdLine.rfind('\\');
                        if (pos != std::string::npos)
                            cmdLine = cmdLine.substr(pos+1);
                    }
                    // Compare against requested process name
                    if (name == cmdLine)
                        pid = id;
                }
            }
        }
    }

    closedir(dp);

    if (pid == -1) {
        std::cout << "[ERROR] No process found\n";
        exit(1);
    }

    this->pid = pid;
}

uintptr_t Process::DMAaddr(uintptr_t ptr, std::vector<uintptr_t> offsets) {
    uintptr_t addr = ptr;
    for (auto i : offsets) {
        addr = this->read<uintptr_t>(addr);
        addr += i;
    }
    return addr;
}

uintptr_t Process::GetModule(std::string name) {
    uintptr_t baseAddr = 0x80085;
    std::string ln;
    std::stringstream maps_file_path;
    maps_file_path << "/proc/" << this->pid << "/maps";

    std::ifstream maps_file_fs(maps_file_path.str(), std::ios::in);

    while (std::getline(maps_file_fs, ln)) {
        if (ln.find(name) == ln.npos) {
            continue;
        }
        std::string tmp;
        std::stringstream ss(ln);

        std::getline(ss, tmp, ' ');
        
        baseAddr = std::stoul(tmp.substr(0, tmp.find_first_of('-')), nullptr, 16);

        maps_file_fs.close();

        break;
    }
    return baseAddr;
}

