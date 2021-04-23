#ifndef FOXINJECTOR_HPP
#define FOXINJECTOR_HPP
#include <Windows.h>
#include <TlHelp32.h>
#include <string>
// #include <fmt/core.h>
#include "fox-process.hpp"

namespace fox {

class injector {
public:
    injector(const fox::process &process) : proc(process) {}

    void injectDll(const char *dll_path)
    {
        // Open process with read + write access
        HANDLE h_proc = OpenProcess(PROCESS_ALL_ACCESS, 0, proc.proc_id);

        if (h_proc && h_proc != INVALID_HANDLE_VALUE) {

            // Allocate memory within process (Real commited or reserver
            // memory) with read/write permissions.
            void *loc = VirtualAllocEx(
                h_proc, 0, MAX_PATH, MEM_COMMIT | MEM_RESERVE, PAGE_READWRITE);

            if (loc) {
                // Write DLL path string into process' memory
                WriteProcessMemory(h_proc, loc, dll_path, strlen(dll_path) + 1,
                                   0);

                // Create thread w/in process and call LoadLibraryA with DLL
                // memory location
                HANDLE h_thread = CreateRemoteThread(
                    h_proc, 0, 0, (LPTHREAD_START_ROUTINE)LoadLibraryA, loc, 0,
                    0);

                // Library is loaded, close thread
                if (h_thread) {
                    CloseHandle(h_thread);
                }
            }
            else {
                std::cerr << allocation_cerr(dll_path);
            }
        }
        else {
            std::cerr << handle_cerr();
        }
        if (h_proc) {
            CloseHandle(h_proc);
        }
    }

    fox::process proc;

private:
    std::string allocation_cerr(const char *dll_path)
    {
        static const std::string str =
            "\"fox/fox-injector.hpp/\": fox::injector::injectDll(): "
            "Error, could not allocate memory for DLL Path \"";

        return str + dll_path +
               "\" with process [ID:" + std::to_string(proc.proc_id) +
               " | NAME:\"" + proc.proc_name + "\"\n";
    }

    static const std::string handle_cerr()
    {
        static const std::string str =
            "\"fox/fox-injector.hpp/\": fox::injector::injectDll(): "
            "Error: Process handle is invalid.\n";
        return str;
    }
};

} // namespace fox
#endif // !FOXINJECTOR_HPP
