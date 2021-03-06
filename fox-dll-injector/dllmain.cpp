#include <windows.h>
#include <stdio.h>
#include <iostream>

BOOL APIENTRY DllMain(HINSTANCE hInst /* Library instance handle. */,
                      DWORD reason /* Reason this function is being called. */,
                      LPVOID reserved /* Not used. */)
{
    switch (reason) {
    case DLL_PROCESS_ATTACH:
        MessageBox(0, "From DLL\n", "Process Attach", MB_ICONINFORMATION);
        break;

    case DLL_PROCESS_DETACH:
        MessageBox(0, "From DLL\n", "Process Detach", MB_ICONINFORMATION);
        break;

    case DLL_THREAD_ATTACH:
        MessageBox(0, "From DLL\n", "Thread Attach", MB_ICONINFORMATION);
        break;

    case DLL_THREAD_DETACH:
        MessageBox(0, "From DLL\n", "Thread Detach", MB_ICONINFORMATION);
        break;
    }

    return TRUE;
}