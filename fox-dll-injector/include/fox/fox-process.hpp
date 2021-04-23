#ifndef FOXPROCESS_HPP
#define FOXPROCESS_HPP
#include <Windows.h>
#include <TlHelp32.h>

namespace fox {

class process {
public:
    process(const char *proc_name) : proc_id(0), proc_name(proc_name)
    {
        // Loop until the process is found
        while (!this->proc_id) {
            this->proc_id = getProcId(proc_name);

            // Sleep 30ms
            Sleep(30);
        }
    }

    static DWORD getProcId(const char *proc_name)
    {
        DWORD proc_id = 0;
        HANDLE hsnap = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);

        if (hsnap != INVALID_HANDLE_VALUE) {
            PROCESSENTRY32 proc_entry;
            proc_entry.dwSize = sizeof(proc_entry);
            if (Process32First(hsnap, &proc_entry)) {
                do {
                    if (!_stricmp(proc_entry.szExeFile, proc_name)) {
                        proc_id = proc_entry.th32ProcessID;
                        break;
                    }

                } while (Process32Next(hsnap, &proc_entry));
            }
        }
        CloseHandle(hsnap);
        return proc_id;
    }

    DWORD proc_id;
    const char *proc_name;
};

} // namespace fox

#endif // !FOXPROCESS_HPP
