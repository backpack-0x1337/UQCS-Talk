#include <iostream>
#include <Windows.h>
#include <TlHelp32.h>


/**
 * Read specific type at given address
 * @tparam T
 * @param hProcess Handle to the process
 * @param address Address to red from
 * @return return the value at given location
 */
template<typename T> T RPM(HANDLE hProcess, uintptr_t address) {
    T buffer;
    ReadProcessMemory(hProcess, (BYTE*)address, &buffer, sizeof(T), NULL);
    return buffer;
}

/**
 * Write specific type value at given address
 * @tparam T
 * @param hProcess Handle to the process
 * @param address Address to red from
 * @return return the value that was written
 */
template<typename T> T WPM(HANDLE hProcess, uintptr_t address, T buffer) {
    WriteProcessMemory(hProcess, (BYTE*)address, &buffer, sizeof(T), NULL);
    return buffer;
}

/**
 * Get Process ID with the given Process name
 * @param procName Target process Name
 * @return Target Process ID
 */
DWORD GetProcId(LPCSTR procName) {
    DWORD procId = 0;
    HANDLE hSnap = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);
    if (hSnap != INVALID_HANDLE_VALUE) {
        PROCESSENTRY32 procEntry;
        procEntry.dwSize = sizeof(procEntry);

        if (Process32First(hSnap, &procEntry)) {
            do {
                if (!lstrcmpi(procEntry.szExeFile, procName)) {
                    procId = procEntry.th32ProcessID;
                    break;
                }
            } while (Process32Next(hSnap, &procEntry));
        }
    }
    CloseHandle(hSnap);
    return procId;

}

int main() {

    // Game Name
    LPCTSTR gameName = "csgo.exe";
    DWORD procID = GetProcId(gameName);
    if (!procID) {
        return 1;
    }
    std::cout << "Process ID: " << procID << std::endl;

    // Open a handle to target process
    HANDLE csgoHandle = OpenProcess(PROCESS_ALL_ACCESS, NULL, procID);
    uintptr_t flashDuringADdr = 0x6A48C160 + 0x10470; // localplayerent Addr + flash duration offset

    while (TRUE) {
        auto flashDuration = RPM<uintptr_t>(csgoHandle, flashDuringADdr);
        if (flashDuration > 0) {
            printf("Stunned please help");
            int temp = 0;
            WPM(csgoHandle, flashDuringADdr, temp);
            break;
        }
    }
    getc(stdin);
    return 0;
}