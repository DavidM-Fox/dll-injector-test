#include <iostream>
#include <Windows.h>
#include <TlHelp32.h>
#include "fox/fox-process.hpp"
#include "fox/fox-injector.hpp"

int main()
{
    fox::process firefox_process("Firefox.exe");
    fox::injector firefox_injector(firefox_process);
    firefox_injector.injectDll("dll-main.dll");
}
