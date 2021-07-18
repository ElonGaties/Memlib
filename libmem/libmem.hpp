#include <stdint.h>
#include <fstream>
#include <dirent.h>
#include <iostream>
#include <errno.h>
#include <sys/types.h>
#include <sys/ptrace.h>
#include <unistd.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <sys/mman.h>
#include <sys/user.h>
#include <sys/syscall.h>
#include <sys/utsname.h>
#include <sys/io.h>
#include <sys/uio.h>
#include <dlfcn.h>
#include <link.h>
#include <fcntl.h>
#include <string>
#include <sstream>
#include <vector>
#include <cstring>
#include <iterator>
#include <chrono>
#include <thread>

class Process {
public:
    pid_t pid;
    template<typename T>
    T read(uintptr_t src) {
        auto buf = T(7331);

        iovec iodst;
        iovec iosrc;
        iodst.iov_len = sizeof(T);
        iodst.iov_base = &buf;
        iosrc.iov_len = sizeof(T);
        iosrc.iov_base = (void*)src;
        
        auto read = process_vm_readv(this->pid, &iodst, 1, &iosrc, 1, 0);
        if (read == -1) {
            std::cout << "[ERROR] Cannot read mem" << '\n';
        }

        return buf;
    }
    template<typename T>
    T write(uintptr_t src, T buf) {
        iovec iodst;
        iovec iosrc;
        iodst.iov_len = sizeof(T);
        iodst.iov_base = &buf;
        iosrc.iov_len = sizeof(T);
        iosrc.iov_base = (void*)src;

        auto write = process_vm_writev(this->pid, &iodst, 1, &iosrc, 1, 0);
        if (write == -1) {
            std::cout << "[ERROR] Cannot write mem" << '\n';
            return 1;
        }

        return 0;
    }
    uintptr_t DMAaddr(uintptr_t ptr, std::vector<uintptr_t> offsets);
    uintptr_t GetModule(std::string name);
    //uintptr_t InjectSyscall(int syscall_n, uintptr_t arg0, uintptr_t arg1, uintptr_t arg2, uintptr_t arg3, uintptr_t arg4, uintptr_t arg5);
    //void* InjectSyscall(int syscall_n, void* arg0, void* arg1, void* arg2, void* arg3, void* arg4, void* arg5);

    Process(std::string name);
};
