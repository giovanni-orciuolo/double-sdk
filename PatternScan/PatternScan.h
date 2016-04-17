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
		HANDLE* HandleToScan;
		std::unique_ptr<BYTE[]> DumpedRegion;
		DWORD ModuleBase;
		DWORD ModuleSize;

	public:
		
		// Inits a PatternScanner using an handle to scan and a module entry to scan
		void Init(HANDLE* HandleToScan, MODULEENTRY32 ModuleToScan)
		{
			this->HandleToScan = HandleToScan;
			this->ModuleToScan = ModuleToScan;
			DumpedRegion = nullptr;
			ModuleBase = reinterpret_cast<DWORD>(ModuleToScan.modBaseAddr);
			ModuleSize = ModuleToScan.modBaseSize;
		}

		// Dump a module, store each byte of the module into DumpedRegion
		bool Dump()
		{
			DumpedRegion = std::make_unique<BYTE[]>( ModuleSize );
			
			auto BytesRead = SIZE_T( );
		
			return ReadProcessMemory(
				this->HandleToScan,
				reinterpret_cast<LPCVOID>(this->ModuleBase),
				DumpedRegion,
				ModuleSize,
				&BytesRead
				) && BytesRead == ModuleSize ? true : false;
		}

		// Check using mask
		bool MaskCheck(int StartOff, const BYTE* Pattern, const char* Mask)
		{
			for (unsigned int i=0; i<strlen(Mask); i++)
        		{
        			if (Mask[i] == '?') continue;
 
            			if (Mask[i] == 'x' && Pattern[i] != this->DumpedRegion[StartOff + i])
                			return false;
        		}
        		return true;
		}

		// Find a pattern in the dumped module using a pattern and a mask.
		DWORD FindPattern(const BYTE* Pattern, const char* Mask, DWORD AddValue = NULL, bool SubtractBase = false)
		{
			if (DumpedRegion == nullptr) if (!this->Dump()) return NULL;

			for (DWORD i=0; i<ModuleBase + ModuleSize; i++)
        		{
        			if (this->MaskCheck(i, Pattern, Mask))
					return SubtractBase ? i + AddValue : ModuleBase + i + AddValue;
			}
        		return NULL;
		}
	};
}

DoubleSDK::CPatternScan ClientScanner;
DoubleSDK::CPatternScan EngineScanner;
