/// Process.h
// This header defines the CProcess class

/*
The CProcess class allows you to attach to a process given by name (for example "csgo.exe").
From the attached process you can grab modules, read from and write to process memory.
You can also get the module entry struct for client.dll and engine.dll, specific for CS:GO.
This header declares a global object of CProcess.
*/

/*
DOUBLE SDK | A FREE CSGO SDK MADE BY DOUBLE V FOR UNKNOWNCHEATS.ME
CREDITS AND SHOUTOUTS:
Double V
WasserEsser
TeamGamerFood
Serge
*/

#pragma once
#include "DoubleSDK.h"

namespace DoubleSDK
{

class CProcess
{
private:

	// HANDLE to the attached process
	HANDLE hProcess;

	// Process ID of the attached process
	DWORD dwProcessID;

	// Name of the attached process
	std::string ProcessName;

	// Struct for Client.dll
	MODULEENTRY32 ClientDLL;

	// Base address of Client.dll
	DWORD ClientBase;

	// Base size of Client.dll (in bytes)
	DWORD ClientSize;

	// Struct for Engine.dll
	MODULEENTRY32 EngineDLL;

	// Base address of Engine.dll
	DWORD EngineBase;

	// Base size of Engine.dll (in bytes)
	DWORD EngineSize;

public:

	// Attach to a process chosen by its name.
	// Once attached it sets the hProcess and the dwProcessID of the class.
	// Returns: True if the process is found and valid.
	bool Attach(const std::string& ProcessName)
	{
		HANDLE hPID = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, NULL);
        if (hPID == INVALID_HANDLE_VALUE) return false;
        PROCESSENTRY32 procEntry;
        procEntry.dwSize = sizeof(procEntry);
 
        const WCHAR* procNameChar;
        int nChars = MultiByteToWideChar(CP_ACP, 0, ProcessName.c_str(), -1, NULL, 0);
        procNameChar = new WCHAR[nChars];
        MultiByteToWideChar(CP_ACP, 0, ProcessName.c_str(), -1, (LPWSTR)procNameChar, nChars);
 
        do
            if (!wcscmp(procEntry.szExeFile, procNameChar))
            {
				this->dwProcessID = procEntry.th32ProcessID;
                CloseHandle(hPID);
				this->hProcess = OpenProcess(PROCESS_ALL_ACCESS, FALSE, this->dwProcessID);
				this->ProcessName = ProcessName;
                return true;
            }
        while (Process32Next(hPID, &procEntry));
 
        CloseHandle(hPID);
        return false;
	}

	// Get a module by name from the attached process (if attached)
	// Returns: Module entry struct for the module found. Base address = 0x0 if not found.
	MODULEENTRY32 GetModule(const std::string& ModuleName)
	{
		HANDLE hModule = CreateToolhelp32Snapshot(TH32CS_SNAPMODULE, dwProcessID);
        MODULEENTRY32 mEntry;
        if (hModule == INVALID_HANDLE_VALUE)
        {
            mEntry.modBaseAddr = 0x0;
            return mEntry;
        }
        mEntry.dwSize = sizeof(mEntry);
 
        const WCHAR *modNameChar;
        int nChars = MultiByteToWideChar(CP_ACP, 0, ModuleName.c_str(), -1, NULL, 0);
        modNameChar = new WCHAR[nChars];
        MultiByteToWideChar(CP_ACP, 0, ModuleName.c_str(), -1, (LPWSTR)modNameChar, nChars);
 
        do
            if (!wcscmp(mEntry.szModule, modNameChar))
            {
                CloseHandle(hModule);
                return mEntry;
            }
        while (Module32Next(hModule, &mEntry));
 
        CloseHandle(hModule);
        mEntry.modBaseAddr = 0x0;
        return mEntry;
	}

	// Init the class to read from and write to CS:GO memory specifically.
	// Returns: True if the initialization is successful.
	bool Init()
	{
		if (!Attach("csgo.exe")) return false;
		ClientDLL = GetModule("client.dll");
		EngineDLL = GetModule("engine.dll");
		if (ClientDLL.modBaseAddr == 0x0 || EngineDLL.modBaseAddr == 0x0) return false;
		ClientBase = reinterpret_cast<DWORD>(ClientDLL.modBaseAddr);
		EngineBase = reinterpret_cast<DWORD>(EngineDLL.modBaseAddr);
		ClientSize = ClientDLL.modBaseSize;
		EngineSize = EngineDLL.modBaseSize;
		return true;
	}

	// Close the HANDLE of the object.
	// The HANDLE must be closed, otherwise there is a memory leak.
	// Returns: True if the function is successful.
	bool Clear()
	{
		return (CloseHandle(hProcess)==TRUE);
	}

	// Print informations about the current process.
	// Returns: void
	void Print()
	{
		if (hProcess == INVALID_HANDLE_VALUE)
		{
			std::cout << "You didn't attach to a process yet!" << std::endl;
			return;
		}
		std::cout << std::endl;
		std::cout << "Informations about "	<< ProcessName << std::endl;
		std::cout << "> hProcess = 0x"		<< std::hex << std::uppercase << hProcess	 << std::nouppercase << std::endl;
		std::cout << "> dwProcessID = 0x"	<< std::hex << std::uppercase << dwProcessID << std::nouppercase << std::endl;
		std::cout << "> ClientBase = 0x"	<< std::hex << std::uppercase << ClientBase  << std::nouppercase << std::endl;
		std::cout << "> ClientSize = 0x"	<< std::hex << std::uppercase << ClientSize  << std::nouppercase << std::endl;
	    std::cout << "> EngineBase = 0x"	<< std::hex << std::uppercase << EngineBase  << std::nouppercase << std::endl;
		std::cout << "> EngineSize = 0x"	<< std::hex << std::uppercase << EngineSize  << std::nouppercase << std::endl;
	}

	// Read a value (of type T) from a certain area of process memory.
	// Returns: The value found.
	template <class T> T Read(DWORD dwAddress)
    {
        T value;
        ReadProcessMemory(hProcess, (LPVOID)dwAddress, &value, sizeof(T), NULL);
        return value;
    }
 
	// Read a value (of type T) from a certain area of process memory of fixed size.
	// Returns: The value found.
    template <class T> T ReadSize(DWORD dwAddress, size_t Size)
    {
        T value;
        ReadProcessMemory(hProcess, (LPVOID)dwAddress, &value, Size, NULL);
        return value;
    }
 
	// Read an array (of type T) from a certain area of process memory.
	// Returns: A pointer to the array found
    template <class T> T* ReadArray(DWORD dwAddress, size_t ArraySize)
    {
        T* arr;
        if (!ReadProcessMemory(hProcess, (LPVOID)dwAddress, arr, sizeof(T)*ArraySize, NULL)) arr = nullptr;
        return arr;
    }
 
	// Write a value (of type T) to a certain area of process memory.
	// Returns: True if the writing is successful.
    template <class T> bool Write(DWORD dwAddress, T ValueToWrite)
    {
        return WriteProcessMemory(hProcess, (LPVOID)dwAddress, &ValueToWrite, sizeof(T), NULL) == TRUE;
    }
 
	// Write a value (of type T) to a certain area of process memory of fixed size.
	// Returns: True if the writing is successful.
    template <class T> bool WriteSize(DWORD dwAddress, T ValueToWrite, size_t Size)
    {
        return WriteProcessMemory(hProcess, (LPVOID)dwAddress, &ValueToWrite, Size, NULL) == TRUE;
    }
 
	// Write an array (of type T) to a certain area of process memory of fixed size.
	// Returns: True if the writing is successful.
    template <class T> bool WriteArray(DWORD dwAddress, T* ArrayToWrite, size_t ArraySize)
    {
        return WriteProcessMemory(hProcess, (LPVOID)dwAddress, ArrayToWrite, sizeof(T)*ArraySize, NULL) == TRUE;
    }
 
	// Try to write a value (of type T) to a certain area of protected process memory.
	// Returns: True if the writing is successful.
    template <class T> bool WriteProtected(DWORD dwAddress, T ValueToWrite)
    {
        DWORD_PTR oldprotect;
        if (!VirtualProtectEx(hProcess, (LPVOID)dwAddress, sizeof(T), PAGE_EXECUTE_READWRITE, &oldprotect)) return false;
        if (!Write(dwAddress, ValueToWrite)) return false;
        if (!VirtualProtectEx(hProcess, (LPVOID)dwAddress, sizeof(T), oldprotect, NULL)) return false;
        return true;
    }
 
	// Try to write a value (of type T) to a certain area of protected process memory of fixed size.
	// Returns: True if the writing is successful.
    template <class T> bool WriteProtectedSize(DWORD dwAddress, T ValueToWrite, size_t Size)
    {
        DWORD_PTR oldprotect;
        if (!VirtualProtectEx(hProcess, (LPVOID)dwAddress, sizeof(T), PAGE_EXECUTE_READWRITE, &oldprotect)) return false;
        if (!WriteSize(dwAddress, ValueToWrite, Size)) return false;
        if (!VirtualProtectEx(hProcess, (LPVOID)dwAddress, sizeof(T), oldprotect, NULL)) return false;
        return true;
    }
 
	// Try to write an array (of type T) to a certain area of protected process memory.
	// Returns: True if the writing is successful.
    template <class T> bool WriteArrayProtected(DWORD dwAddress, T* ArrayToWrite, size_t ArraySize)
    {
        DWORD_PTR oldprotect;
        if (!VirtualProtectEx(hProcess, (LPVOID)dwAddress, sizeof(T), PAGE_EXECUTE_READWRITE, &oldprotect)) return false;
        if (!WriteArray(dwAddress, ArrayToWrite, ArraySize)) return false;
        if (!VirtualProtectEx(hProcess, (LPVOID)dwAddress, sizeof(T), oldprotect, NULL)) return false;
        return true;
    }

	// Get hProcess
	HANDLE* GetProcHandle() { return &this->hProcess; }
	// Get dwProcessID
	DWORD GetProcID() { return this->dwProcessID; }
	// Get ProcessName
	std::string GetProcessName() { return this->ProcessName; }
	// Get ClientDLL
	MODULEENTRY32 GetClient() { return this->ClientDLL; }
	// Get ClientBase
	DWORD GetClientBase() { return this->ClientBase; }
	// Get ClientSize
	DWORD GetClientSize() { return this->ClientSize; }
	// Get EngineDLL
	MODULEENTRY32 GetEngine() { return this->EngineDLL; }
	// Get EngineBase
	DWORD GetEngineBase() { return this->EngineBase; }
	// Get EngineSize
	DWORD GetEngineSize() { return this->EngineSize; }

};

}

DoubleSDK::CProcess Process;