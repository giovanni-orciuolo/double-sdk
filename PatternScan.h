/// PatternScan.h
// This header defines the CPatternScan class

/*
The CPatternScan class allows you to grab offsets dynamically using a pattern and a mask made out of it.
The SDK already handles the initialization and the dumping of modules, and furthermore it cares about finding
most useful offsets. You can add your own sigs though!
Credits to atom0s for the C# version of this class, translated and adapted for CS:GO and C++
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

#pragma warning(disable : 4800)


namespace DoubleSDK
{

	class CPatternScan
	{
	private:

		MODULEENTRY32 ModuleToScan;
		HANDLE HandleToScan;
		BYTE* DumpedRegion;
		DWORD ModuleBase;
		DWORD ModuleSize;

	public:

		// Inits a PatternScanner using an handle to scan and a module entry to scan
		void Init(HANDLE HandleToScan, MODULEENTRY32 ModuleToScan)
		{
			this->HandleToScan = HandleToScan;
			this->ModuleToScan = ModuleToScan;
			this->ModuleBase = reinterpret_cast<DWORD>(ModuleToScan.modBaseAddr);
			this->ModuleSize = ModuleToScan.modBaseSize;
		}

		bool Dump()
		{
			this->DumpedRegion = new BYTE[this->ModuleSize];

			bool rpmResult;

			rpmResult =
				(bool)
				ReadProcessMemory(
					this->HandleToScan,
					reinterpret_cast<LPCVOID>(this->ModuleBase),
					DumpedRegion,
					ModuleSize,
					NULL
				);

			if (!rpmResult)
			{
				Clear();
				return false;
			}

			return true;
		}

		void Clear()
		{
			this->DumpedRegion = nullptr;
		}

		bool DataCompare(const BYTE* pData, const BYTE* pMask, const char* pszMask) {
			for (; *pszMask; ++pszMask, ++pData, ++pMask) {
				if (*pszMask == 'x' && *pData != *pMask) {
					return false;
				}
			}

			return (*pszMask == NULL);
		}

		DWORD FindPattern(DWORD start, DWORD size, const char* sig, const char* mask) {
			BYTE* data = new BYTE[size];

			unsigned long bytesRead;

			if (!ReadProcessMemory(Process.GetProcHandle(), (LPVOID)start, data, size, &bytesRead)) {
				return NULL;
			}

			for (DWORD i = 0; i < size; i++) {
				if (DataCompare((const BYTE*)(data + i), (const BYTE*)sig, mask)) {
					return start + i;
				}
			}

			return NULL;
		}

		DWORD FindPatternArr(DWORD start, DWORD size, const char* mask, int count, ...) {
			char* sig = new char[count + 1];
			va_list ap;
			va_start(ap, count);
			for (int i = 0; i < count; i++) {
				char read = va_arg(ap, char);
				sig[i] = read;
			}
			va_end(ap);
			sig[count] = '\0';

			return FindPattern(start, size, sig, mask);
		}

	};

}

DoubleSDK::CPatternScan ClientScanner;
DoubleSDK::CPatternScan EngineScanner;